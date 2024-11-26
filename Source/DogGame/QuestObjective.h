#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestObjective.generated.h"


class UQuest;

UCLASS(Blueprintable)
class DOGGAME_API UQuestObjective : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Objective")
    FString ObjectiveDescription;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Objective")
    bool bIsCompleted;

    // Methods
    UFUNCTION(BlueprintCallable, Category = "Objective")
    void MarkAsComplete();

    UFUNCTION(BlueprintCallable, Category = "Objective")
    bool IsObjectiveComplete() const;
};

