#include "QuestTrackerWidget.h"
#include "Components/TextBlock.h"
#include "Quest.h"

void UQuestTrackerWidget::UpdateUI(UQuest* ActiveQuest)
{
    if (ActiveQuest)
    {
        QuestNameText->SetText(FText::FromString(ActiveQuest->QuestName));
        QuestDescriptionText->SetText(FText::FromString(ActiveQuest->QuestDescription));
    }
    else
    {
        QuestNameText->SetText(FText::FromString("No Active Quest"));
        QuestDescriptionText->SetText(FText::FromString(""));
    }
}