#include "QuestObjective.h"

void UQuestObjective::MarkAsComplete()
{
    bIsCompleted = true;
    // Notify parent quest if needed
}

bool UQuestObjective::IsObjectiveComplete() const
{
    return bIsCompleted;
}