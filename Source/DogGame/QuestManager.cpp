#include "QuestManager.h"

UQuestManager::UQuestManager()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UQuestManager::AddQuest(UQuest* Quest)
{
    if (Quest)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Adding Quest: ") + Quest->QuestName);
        ActiveQuests.Add(Quest);
        Quest->Status = EQuestStatus::InProgress;
    }
    else 
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("NewQuest is nullptr"));
    }
}

void UQuestManager::CompleteQuest(FString QuestName)
{
    for (UQuest* Quest : ActiveQuests)
    {
        if (Quest && Quest->QuestName == QuestName && Quest->Status == EQuestStatus::InProgress)
        {
            Quest->CompleteQuest();
            break;
        }
    }
}