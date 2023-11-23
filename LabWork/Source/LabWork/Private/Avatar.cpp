// Fill out your copyright notice in the Description page of Project Settings.


#include "Avatar.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AAvatar::AAvatar() :
	RunningSpeed(800.0f),
	Stamina(100.f),
	
	MaxStamina(100.0f),
	
	StaminaGainRate(20.0f),
	StaminaDrainRate(40.0f),
	StaminaDrained(false),
	Running(false)


{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritYaw = true;
	Camera->bUsePawnControlRotation = false;
	bUseControllerRotationYaw = false;

}

void AAvatar::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetCharacterMovement()->MovementMode == MOVE_Walking)
	{
		if (!StaminaDrained && Running)
		{
			if (!GetCharacterMovement()->Velocity.IsNearlyZero(0.01f))
			{
				Stamina = FMath::Max(0.0f, Stamina - StaminaDrainRate * DeltaTime);
				if (Stamina == 0.0f)
				{
					StaminaDrained = true;
					UpdateMovementParams();
				}
			}

		}
		else {
			Stamina = FMath::Min(MaxStamina, Stamina + StaminaGainRate * DeltaTime);
			if (Stamina >= MaxStamina)
			{
				StaminaDrained = false;
				UpdateMovementParams();
			}
		}
	}
	GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Blue,
		FString::Printf(TEXT("%f"), Stamina));

}

	void AAvatar::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
	{
		Super::SetupPlayerInputComponent(PlayerInputComponent);

		PlayerInputComponent->BindAxis("Turn", this, &AAvatar::AddControllerYawInput);
		PlayerInputComponent->BindAxis("LookUp", this, &AAvatar::AddControllerPitchInput);

		PlayerInputComponent->BindAxis("MoveForward", this, &AAvatar::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &AAvatar::MoveRight);
		PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AAvatar::RunPressed);
		PlayerInputComponent->BindAction("Run", IE_Released, this, &AAvatar::RunReleased);
	}

	void AAvatar::MoveForward(float Amount)
	{
		FRotator ControlRotation = GetControlRotation();
		FVector ForwardDirection = FRotationMatrix(FRotator(0.0f, ControlRotation.Yaw, 0.0f)).GetUnitAxis(EAxis::X);

		AddMovementInput(ForwardDirection, Amount);
	}

	void AAvatar::MoveRight(float Amount)
	{
		FRotator ControlRotation = GetControlRotation();
		FVector RightDirection = FRotationMatrix(FRotator(0.0f, ControlRotation.Yaw, 0.0f)).GetUnitAxis(EAxis::Y);

		AddMovementInput(RightDirection, Amount);
	}

	void AAvatar::RunPressed()
	{
		Running = true;
		UpdateMovementParams();
	}

	void AAvatar::RunReleased()
	{
		Running = false;
		UpdateMovementParams();
	}

	void AAvatar::UpdateMovementParams()
	{
		if (!StaminaDrained && Running)
		{
			GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
		}

		else
			GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
	}



