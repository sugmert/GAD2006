// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "Avatar.generated.h"

/**
 * a
 */

UCLASS()
class AAvatar : public AMyCharacter
{
	GENERATED_BODY()
public:
	AAvatar();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyChar")
	class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyChar")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = "MyChar")
	float RunningSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyChar")
	float Stamina;
	UPROPERTY(EditAnywhere, Category = "MyChar")
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyChar")
	float StaminaGainRate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyChar")
	float StaminaDrainRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyChar")
	bool StaminaDrained;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyChar")
	bool Running;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	void MoveForward(float value);
	void MoveRight(float value);
	void RunPressed();
	void RunReleased();
	void UpdateMovementParams();

protected:
	public:
	virtual void Tick(float DeltaTime) override;
};