#include "ItemActor.h"
#include "ItemScent.h"
#include "Quest.h"
#include "DogCharacter/DogCharacter.h"
#include "QuestManager.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

AItemActor::AItemActor()
{
    PrimaryActorTick.bCanEverTick = false;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
    //Create & attach ItemScentComponent
    ItemScent = CreateDefaultSubobject<UItemScent>(TEXT("ItemScentComponent"));
    ItemScent->SetupAttachment(RootComponent);
	
	//Initialises collision component
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->InitSphereRadius(100.0f);
	CollisionComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	//Bind overlap event
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AItemActor::OnOverlapBegin);
}

void AItemActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	ADogCharacter* PlayerCharacter = Cast<ADogCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		UQuestManager* QuestManager = PlayerCharacter->FindComponentByClass<UQuestManager>();
		if (QuestManager)
		{
			//complete the active quest
			if (QuestManager->ActiveQuests.Num() > 0)
			{
				UQuest* CurrentQuest = QuestManager->ActiveQuests[0]; // Assuming single active quest for simplicity
				if (CurrentQuest)
				{
					QuestManager->CompleteQuest(CurrentQuest->QuestName);
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Quest Completed: ") + CurrentQuest->QuestName);
					QuestManager->UpdateQuestUI(CurrentQuest);
				}
			}
		}
		// Destroy the item actor after quest completion
		Destroy();
	}
}

void AItemActor::BeginPlay()
{
	Super::BeginPlay();

    if (ItemScent)
    {
        ItemScent->ScentStrength = 1.5f;
    }
	
}

void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

