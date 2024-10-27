#include "DogGame/DogCharacter/DogCharacter.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ADogCharacter::ADogCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

// Called when the game starts or when spawned
void ADogCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADogCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADogCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Add input mapping context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
		//Gets local player subsystem
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			//Add input context
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		//WASD actions binded
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADogCharacter::Move);
		//CAMERA actions binded
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADogCharacter::Look);
		//Jump action binded
		Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ADogCharacter::Jump);
		//SPRINTING actions binded
		Input->BindAction(SprintAction, ETriggerEvent::Started, this, &ADogCharacter::Sprint);
		Input->BindAction(SprintAction, ETriggerEvent::Completed, this, &ADogCharacter::Walk);

		Input->BindAction(TrickAction, ETriggerEvent::Started, this, &ADogCharacter::Trick);
	}
}

void ADogCharacter::Move(const FInputActionValue& InputValue)
{
	FVector2D InputVector = InputValue.Get<FVector2D>();

	if (IsValid(Controller)) {
		//Get Forward Direction
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator yawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

		//Add Movement Input
		AddMovementInput(ForwardDirection, InputVector.Y);
		AddMovementInput(RightDirection, InputVector.X);
	}
}

void ADogCharacter::Look(const FInputActionValue& InputValue)
{
	//Gets X, Y
	FVector2D InputVector = InputValue.Get<FVector2D>();

	//Applies Yaw and Pitch
	if (IsValid(Controller)) {
		AddControllerYawInput(InputVector.X);
		AddControllerPitchInput(InputVector.Y);
	}

}

void ADogCharacter::Jump()
{
	ACharacter::Jump();
}

//Sprinting
void ADogCharacter::Sprint()
{
	//Setting MaxWalkSpeed to SprintSpeed
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

//Walking
void ADogCharacter::Walk()
{
	//Settings MaxWalkSpeed to walkSpeed
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
}

void ADogCharacter::Trick()
{
	float CurrentTime = GetWorld()->GetTimeSeconds();

	// Check if the cooldown has expired
	if (CurrentTime - LastTrickTime >= TrickCooldownTime)
	{
		if (TrickMontage)
		{
			// Play the montage on the dog's mesh
			PlayAnimMontage(TrickMontage);
		}

		// Update the last trick time
		LastTrickTime = CurrentTime;
	}
	else
	{
		//Outputs cooldown
		float TimeLeft = TrickCooldownTime - (CurrentTime - LastTrickTime);
		FString CooldownMessage = FString::Printf(TEXT("Trick on cooldown! Time left: %.1f seconds"), TimeLeft);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, CooldownMessage);
	}
}




