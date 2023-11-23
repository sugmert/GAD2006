// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyCharacter::AMyCharacter() :
	MaxHealth(0.0f),
	Health(0.0f),
	HealingRate(10.0f),
	WalkingSpeed(400.0f)
	

{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyCharacter::OnConstruction(const FTransform& Transform)
{
	Health = MaxHealth;
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Health = FMath::Min(MaxHealth, Health + HealingRate * DeltaTime);

	
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMyCharacter::SetHealth(float NewHealth)
{
	Health = NewHealth;
}

float AMyCharacter::GetHealth()
{
	return Health;
}



