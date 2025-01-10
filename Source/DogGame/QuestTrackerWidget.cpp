#include "QuestTrackerWidget.h"
#include "Components/TextBlock.h"
#include "Quest.h"

void UQuestTrackerWidget::UpdateUI(UQuest* ActiveQuest)
{
    if (ActiveQuest)
    {
        QuestNameText->SetText(FText::FromString(ActiveQuest->QuestName));
        QuestDescriptionText->SetText(FText::FromString(ActiveQuest->QuestDescription));

        //Update UI based on quest status
        if (ActiveQuest->Status == EQuestStatus::Completed)
        {
            QuestDescriptionText->SetText(FText::FromString(TEXT("Task Completed, Collect Another!")));
        }
        else
        {
            QuestDescriptionText->SetText(FText::FromString(ActiveQuest->QuestDescription));
        }

        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Task UI Updated"));
    }
    else
    {
        QuestNameText->SetText(FText::FromString("No Active Task"));
        QuestDescriptionText->SetText(FText::FromString(""));
    }
}