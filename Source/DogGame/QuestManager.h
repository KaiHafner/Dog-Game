#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Quest.h"
#include "QuestTrackerWidget.h"
#include "QuestManager.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DOGGAME_API UQuestManager : public UActorComponent
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

public:
    UQuestManager();

    //List of active quests
    UPROPERTY(BlueprintReadWrite, Category = "Quest")
    TArray<UQuest*> ActiveQuests;

    //Ad a quest to the active quest list
    UFUNCTION(BlueprintCallable, Category = "Quest")
    void AddQuest(UQuest* Quest);

    //Check if a quest is complete
    UFUNCTION(BlueprintCallable, Category = "Quest")
    void CompleteQuest(FString QuestName);


    UPROPERTY(BlueprintReadWrite, Category = "UI")
    UQuestTrackerWidget* QuestTrackerWidget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UQuestTrackerWidget> QuestTrackerWidgetClass;
};
