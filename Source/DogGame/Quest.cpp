#include "Quest.h"

UQuest::UQuest()
{
    QuestName = "Default Quest";
    QuestDescription = "Default Description";
    ObjectiveType = "Collect";
    TargetObject = "Default Object";
    Status = EQuestStatus::NotStarted;
}

void UQuest::CompleteQuest()
{
    Status = EQuestStatus::Completed;
}
