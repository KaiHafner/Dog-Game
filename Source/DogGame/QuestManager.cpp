#include "QuestManager.h"
#include "QuestTrackerWidget.h"

UQuestManager::UQuestManager(): QuestTrackerWidget(nullptr)
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UQuestManager::BeginPlay() 
{
    if (QuestTrackerWidgetClass) 
    {
        //check for player controller
        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            QuestTrackerWidget = CreateWidget<UQuestTrackerWidget>(PlayerController, QuestTrackerWidgetClass);
            if (QuestTrackerWidget)
            {
                //creates quest widget
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
            
            if (QuestTrackerWidget)
            {
                QuestTrackerWidget->UpdateUI(Quest);
            }
            
            break;
        }
    }
}

void UQuestManager::UpdateQuestUI(UQuest* Quest)
{
    if (QuestTrackerWidget)
    {
        QuestTrackerWidget->UpdateUI(Quest);
    }
}