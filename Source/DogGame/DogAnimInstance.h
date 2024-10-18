#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DogAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DOGGAME_API UDogAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	class ADogCharacter* DogCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float Speed;

	UPROPERTY(BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	bool isJumping;

	//UPROPERTY(BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	//float bIsInputAccelerating;
};
