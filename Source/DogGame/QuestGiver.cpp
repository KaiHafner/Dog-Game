#include "QuestGiver.h"
#include "Engine/World.h"
#include "DogCharacter/DogCharacter.h"
#include "QuestManager.h"
#include "Quest.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

AQuestGiver::AQuestGiver()
{
    PrimaryActorTick.bCanEverTick = false;

    //Initialize the collision sphere component
    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
    CollisionSphere->SetupAttachment(RootComponent);  //Attach it to the root component
    CollisionSphere->InitSphereRadius(100.f);  //Set the size
    CollisionSphere->SetCollisionProfileName(TEXT("Trigger"));  //Set to trigger profile so it doesn't block other actors
}

void AQuestGiver::BeginPlay()
{
    Super::BeginPlay();

    //Creates Quests
    UQuest* Quest1 = NewObject<UQuest>();
    Quest1->QuestName = "Find the Cube";
    Quest1->QuestDescription = "The player needs to find and return the lost cube.";

    UQuest* Quest2 = NewObject<UQuest>();
    Quest2->QuestName = "Find the Bone";
    Quest2->QuestDescription = "The player needs to find and return the lost bone.";

    UQuest* Quest3 = NewObject<UQuest>();
    Quest3->QuestName = "Find the Dinosaur toy";
    Quest3->QuestDescription = "The player needs to find and return the Dinosaur toy";

    AvailableQuests.Add(Quest1);
    AvailableQuests.Add(Quest2);
    AvailableQuests.Add(Quest3);

    //Bind the overlap event to the function
    CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AQuestGiver::OnOverlapBegin);
}

UQuest* AQuestGiver::AssignQuest()
{
    if (AvailableQuests.Num() > 0)
    {
        UQuest* AssignedQuest = AvailableQuests[0]; //Assign the first quest for simplicityy
        AvailableQuests.RemoveAt(0); //Remove it from available quests
        return AssignedQuest;
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("No quests available"));
    }
    return nullptr; //No quests available
}

void AQuestGiver::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    ADogCharacter* PlayerCharacter = Cast<ADogCharacter>(OtherActor);
    if (PlayerCharacter)
    {
        //Rotates player
        RotateToFacePlayer(PlayerCharacter);

        //Get the QuestManager component from the player
        UQuestManager* QuestManager = PlayerCharacter->FindComponentByClass<UQuestManager>();
        if (QuestManager)
        {
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "QUEST MANAGER");
            //Assign a quest to the player through the QuestManager
            UQuest* NewQuest = AssignQuest();
            if (NewQuest)
            {
                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "QUEST ADDED");
                QuestManager->AddQuest(NewQuest); 
            }
        }
    }
}

//Handles Rotation
void AQuestGiver::RotateToFacePlayer(AActor* PlayerActor)
{
    FVector Direction = PlayerActor->GetActorLocation() - GetActorLocation();
    Direction.Z = 0;
    FRotator TargetRotation = Direction.Rotation();
    SetActorRotation(TargetRotation);
}