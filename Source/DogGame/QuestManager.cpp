#include "QuestManager.h"
#include "QuestTrackerWidget.h"

UQuestManager::UQuestManager()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UQuestManager::BeginPlay() 
{
    if (QuestTrackerWidgetClass) 
    {
        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            QuestTrackerWidget = CreateWidget<UQuestTrackerWidget>(PlayerController, QuestTrackerWidgetClass);
            if (QuestTrackerWidget)
            {
                QuestTrackerWidget->AddToViewport();
            }
        }
    }
}

void UQuestManager::AddQuest(UQuest* Quest)
{
    if (Quest)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Adding Quest: ") + Quest->QuestName);
        ActiveQuests.Add(Quest);
        Quest->Status = EQuestStatus::InProgress;

        if (QuestTrackerWidget)
        {
            QuestTrackerWidget->UpdateUI(Quest);
        }
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