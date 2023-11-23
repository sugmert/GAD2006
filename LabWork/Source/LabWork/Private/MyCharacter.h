// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include"Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyCharacter.generated.h"

UCLASS()
class AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(VisibleAnywhere, Category = "MyChar")
	float Health;

		
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "MyChar")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyChar")
	float HealingRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyChar")
	float WalkingSpeed;
			
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyChar")
	bool Update;

		
	UFUNCTION(BlueprintCallable, Category = "MyChar")
	void SetHealth(float NewHealth);

	UFUNCTION(BlueprintPure, Category = "MyChar")
	float GetHealth();

public: 

	UFUNCTION(BlueprintImplementableEvent)
	float MpdifyDamage(float IncomingDamage)
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	
};
