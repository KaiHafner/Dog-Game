#include "QuestGiver.h"

#include "Engine/World.h"
#include "DogCharacter/DogCharacter.h"
#include "QuestManager.h"
#include "Quest.h"
#include "GameFramework/PlayerController.h"
#include "NavigationSystem.h"

AQuestGiver::AQuestGiver()
{
    PrimaryActorTick.bCanEverTick = false;

    //Initialises the collision sphere component
    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
    CollisionSphere->SetupAttachment(RootComponent);  //Attach it to the root component
    CollisionSphere->InitSphereRadius(100.f);  //Set the size
    CollisionSphere->SetCollisionProfileName(TEXT("Trigger"));  //Set to trigger profile so it doesn't block other actors
}

void AQuestGiver::BeginPlay()
{
    Super::BeginPlay();

    //Creates Quests (not how I planned but works so sticking with it)
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
        UQuest* AssignedQuest = AvailableQuests[0]; //Assign the first quest for simplicity
        AvailableQuests.RemoveAt(0); //Remove it from available quests
        return AssignedQuest;
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("No quests available"));
    }
    return nullptr; //No quests available
}

void AQuestGiver::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, //This was taken from some random guy online, but it works now
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    ADogCharacter* PlayerCharacter = Cast<ADogCharacter>(OtherActor);
    if (PlayerCharacter)
    {
        RotateToFacePlayer(PlayerCharacter);
        
        UQuestManager* QuestManager = PlayerCharacter->FindComponentByClass<UQuestManager>();
        if (QuestManager)
        {
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "QUEST MANAGER");

            //Assign a quest to the player through the QuestManager
            UQuest* NewQuest = AssignQuest();
            if (NewQuest)
            {
                SpawnBlueprintActorRandomly();
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

//Spawns the Item around the map
void AQuestGiver::SpawnBlueprintActorRandomly()
{
    if (!ActorToSpawn)
    {
        return;
    }

    UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
    if (!NavSystem)
    {
        return;
    }

    FVector Origin(0.0f, 0.0f, 0.0f); //sets origin
    FNavLocation RandomPoint;
    
    if (NavSystem->GetRandomReachablePointInRadius(Origin, 5000.0f, RandomPoint))
    {
        //spawn item at the random spot
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        GetWorld()->SpawnActor<AActor>(ActorToSpawn, RandomPoint.Location, FRotator::ZeroRotator, SpawnParams);
    }
}

