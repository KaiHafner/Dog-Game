#include "QuestManager.h"
#include "Quest.h"

// Constructor
AQuestManager::AQuestManager()
{
    PrimaryActorTick.bCanEverTick = true; // Enable ticking
}

// Called when the game starts or when spawned
void AQuestManager::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AQuestManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Update active quests every frame (you can optimize this)
    for (UQuest* Quest : ActiveQuests)
    {
        if (Quest && Quest->QuestState == EQuestState::Active)
        {
            Quest->CheckObjectives();  // Check if the quest objectives are completed
        }
    }
}

void AQuestManager::AddQuest(UQuest* NewQuest)
{
    if (NewQuest && !ActiveQuests.Contains(NewQuest))
    {
        ActiveQuests.Add(NewQuest);
        NewQuest->ActivateQuest();
        UpdateQuestUI();
    }
}

void AQuestManager::RemoveQuest(UQuest* Quest)
{
    if (Quest && ActiveQuests.Contains(Quest))
    {
        ActiveQuests.Remove(Quest);
        UpdateQuestUI();
    }
}

void AQuestManager::UpdateQuestUI() const
{
    // Logic to update UI (this could trigger an event to update the UI widget)
}

UQuest* AQuestManager::GetActiveQuest() const
{
    for (UQuest* Quest : ActiveQuests)
    {
        if (Quest && Quest->QuestState == EQuestState::Active)
        {
            return Quest;
        }
    }
    return nullptr;
}