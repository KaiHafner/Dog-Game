#include "DogAnimInstance.h"
#include "DogCharacter/DogCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UDogAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	DogCharacter = Cast<ADogCharacter>(TryGetPawnOwner());
}

//Every frame
void UDogAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (DogCharacter == nullptr) return;

	FVector Velocity = DogCharacter->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	isJumping = DogCharacter->GetCharacterMovement()->IsFalling();
}
