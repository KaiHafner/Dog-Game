#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Quest.h"
#include "QuestManager.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DOGGAME_API UQuestManager : public UActorComponent
{
    GENERATED_BODY()

public:
    UQuestManager();

    // List of active quests
    UPROPERTY(BlueprintReadWrite, Category = "Quest")
    TArray<UQuest*> ActiveQuests;

    // Add a quest to the active quest list
    UFUNCTION(BlueprintCallable, Category = "Quest")
    void AddQuest(UQuest* Quest);

    // Check if a quest is complete
    UFUNCTION(BlueprintCallable, Category = "Quest")
    void CompleteQuest(FString QuestName);
};
