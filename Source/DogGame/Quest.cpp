#include "Quest.h"
#include "QuestObjective.h"

void UQuest::ActivateQuest()
{
    QuestState = EQuestState::Active;
    // Additional logic to start tracking the quest
}

void UQuest::CompleteQuest()
{
    if (IsQuestComplete())
    {
        QuestState = EQuestState::Completed;
        // Notify the player or update UI
    }
}

bool UQuest::IsQuestComplete() const
{
    for (const UQuestObjective* Objective : Objectives)
    {
        if (!Objective || !Objective->IsObjectiveComplete())
        {
            return false;
        }
    }
    return true;
}

void UQuest::CheckObjectives()
{
    if (IsQuestComplete())
    {
        CompleteQuest();
    }
}