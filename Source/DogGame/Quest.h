#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Quest.generated.h"

UENUM(BlueprintType)enum class EQuestStatus : uint8
{
    NotStarted UMETA(DisplayName = "Not Started"),
    InProgress UMETA(DisplayName = "In Progress"),
    Completed UMETA(DisplayName = "Completed")
};

UCLASS(Blueprintable)
class DOGGAME_API UQuest : public UObject
{
    GENERATED_BODY()

public:
    UQuest();

    //name
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    FString QuestName;

    //description
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    FString QuestDescription;

    //objective type
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    FString ObjectiveType;

    //Object to collect
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    FString TargetObject;

    //status
    UPROPERTY(BlueprintReadWrite, Category = "Quest")
    EQuestStatus Status;

    //mark as complete
    UFUNCTION(BlueprintCallable, Category = "Quest")
    void CompleteQuest();
};
