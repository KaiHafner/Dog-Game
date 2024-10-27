#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "DogCharacter.generated.h"

UCLASS()
class DOGGAME_API ADogCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

protected:
	//Enhanced Inputs
	UPROPERTY(EditAnywhere, category = "EnhancedInput")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, category = "EnhancedInput")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, category = "EnhancedInput")
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, category = "EnhancedInput")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, category = "EnhancedInput")
	class UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* TrickAction;

protected:
	//Animations
	UPROPERTY(EditAnywhere, Category = "Animation")
	class UAnimMontage* TrickMontage;

protected:
	//Trick Cooldown
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooldown")
	float TrickCooldownTime = 3.0f; // Set your desired cooldown time

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cooldown")
	float LastTrickTime = 0.0f; // Time of last trick performed

public:
	// Sets default values for this character's properties
	ADogCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	float walkSpeed = 175.0f;
	float SprintSpeed = 350.0f;
	bool bIsJumping;

	void Move(const FInputActionValue& InputValue);
	void Look(const FInputActionValue& InputValue);
	void Jump();
	void Sprint();
	void Walk();
	void Trick();
};

