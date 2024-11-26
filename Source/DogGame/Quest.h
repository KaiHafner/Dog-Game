#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Quest.generated.h"

// UENUM declaration MUST be OUTSIDE the #ifndef block
UENUM(BlueprintType)
enum class EQuestState : uint8
{
    Inactive UMETA(DisplayName = "Inactive"),
    Active UMETA(DisplayName = "Active"),
    Completed UMETA(DisplayName = "Completed")
};

// Forward declaration of objectives
class UQuestObjective;

UCLASS(Blueprintable)
class DOGGAME_API UQuest : public UObject
{
    GENERATED_BODY()

public:
    //Quest properties
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Quest")
    FString QuestName;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Quest")
    FString QuestDescription;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Quest")
    EQuestState QuestState;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Quest")
    TArray<UQuestObjective*> Objectives;

    // Methods
    UFUNCTION(BlueprintCallable, Category = "Quest")
    void ActivateQuest();
    UFUNCTION(BlueprintCallable, Category = "Quest")
    void CompleteQuest();
    UFUNCTION(BlueprintCallable, Category = "Quest")
    bool IsQuestComplete() const;
    void CheckObjectives();
};
