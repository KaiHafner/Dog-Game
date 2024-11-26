#include "DogGame/DogCharacter/DogCharacter.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "DogGame/ScentTracking.h"


// Sets default values
ADogCharacter::ADogCharacter()
{
	ScentTracking = CreateDefaultSubobject<UScentTracking>(TEXT("ScentTrackingComponent"));
	ScentTracking->SetupAttachment(RootComponent);

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setup spring arm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;

	//Setuup camera component
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	//Character rotation settings
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

// Called when the game starts or when spawned
void ADogCharacter::BeginPlay()
{
	Super::BeginPlay();
	LastTrickTime = -TrickCooldownTime; //removes trick cooldown from beginning
	
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
		//Movement Bindings
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADogCharacter::Move);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADogCharacter::Look);
		Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ADogCharacter::Jump);
		Input->BindAction(SprintAction, ETriggerEvent::Started, this, &ADogCharacter::Sprint);
		Input->BindAction(SprintAction, ETriggerEvent::Completed, this, &ADogCharacter::Walk);
		Input->BindAction(TrickAction, ETriggerEvent::Started, this, &ADogCharacter::Trick);

		Input->BindAction(TrackAction, ETriggerEvent::Completed, this, &ADogCharacter::Track);
	}
}

void ADogCharacter::Move(const FInputActionValue& InputValue)
{
	FVector2D InputVector = InputValue.Get<FVector2D>();

	if (IsValid(Controller)) {
		//Get forward and right direction based on controller rotation
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

	if (IsValid(Controller)) {
		//Applies Yaw and Pitch
		AddControllerYawInput(InputVector.X);
		AddControllerPitchInput(InputVector.Y);
	}

}

//Jumping
void ADogCharacter::Jump()
{
	ACharacter::Jump();
}

//Sprinting
void ADogCharacter::Sprint()
{
	//Setting MaxWalkSpeed to SprintSpeed
	if (!bIsTrick) 
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}

//Walking
void ADogCharacter::Walk()
{
	if (!bIsTrick)
	{
		//Settings MaxWalkSpeed to walkSpeed
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}

void ADogCharacter::Trick()
{
	float CurrentTime = GetWorld()->GetTimeSeconds();

	// Check if the cooldown has expired
	if (CurrentTime - LastTrickTime >= TrickCooldownTime)
	{
		if (TrickMontage)
		{
			bIsTrick = true;
			PlayAnimMontage(TrickMontage);
			GetCharacterMovement()->MaxWalkSpeed = TrickSpeed;
			// Set a timer to reset speed after the trick is done
			GetWorld()->GetTimerManager().SetTimer(TrickTimerHandle, this, &ADogCharacter::ResetSpeed, TrickMontage->GetPlayLength(), false);
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

void ADogCharacter::Track()
{
	if (!bIsTracking)
	{
		bIsTracking = true;
		ScentTracking->StartScentTracking();
	}
	else if (bIsTracking)
	{
		bIsTracking = false;
		ScentTracking->StopScentTracking();
	}
}

void ADogCharacter::ResetSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	bIsTrick = false;
}