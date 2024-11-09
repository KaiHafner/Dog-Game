#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "DogGame/ScentTracking.h"

#include "DogCharacter.generated.h"


UCLASS()
class DOGGAME_API ADogCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	// Speed Variables
	UPROPERTY(EditAnywhere, Category = "Movement")
	float WalkSpeed = 175.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float SprintSpeed = 350.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float TrickSpeed = 0.0f;

	// Jump and Trick Flags
	bool bIsJumping = false;
	bool bIsTrick = false;
	bool bIsTracking = false;

	// Trick Timer
	FTimerHandle TrickTimerHandle;

	//Camera Components
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

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* TrackAction;

	//Animations
	UPROPERTY(EditAnywhere, Category = "Animation")
	class UAnimMontage* TrickMontage;

	//Trick Cooldown
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooldown")
	float TrickCooldownTime = 3.0f; // Set your desired cooldown time

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cooldown")
	float LastTrickTime = 0.0f; // Time of last trick performed

public:
	// Sets default values for this character's properties
	ADogCharacter();

	//Scent Tracking
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UScentTracking* ScentTracking;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	//Movement and action functions
	void Move(const FInputActionValue& InputValue);
	void Look(const FInputActionValue& InputValue);
	void Jump();
	void Sprint();
	void Walk();
	void Trick();
	void Track();

	

	//Helper Functions
	void ResetSpeed();
};

