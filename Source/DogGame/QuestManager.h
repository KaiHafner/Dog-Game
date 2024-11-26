#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestManager.generated.h"

class UQuest;

UCLASS()
class DOGGAME_API AQuestManager : public AActor
{
    GENERATED_BODY()

public:
    // Constructor
    AQuestManager();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // List of currently active quests
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Quest Manager")
    TArray<UQuest*> ActiveQuests;

    // Methods to add or remove quests
    UFUNCTION(BlueprintCallable, Category = "Quest Manager")
    void AddQuest(UQuest* NewQuest);

    UFUNCTION(BlueprintCallable, Category = "Quest Manager")
    void RemoveQuest(UQuest* Quest);

    // Update UI with current active quest
    UFUNCTION(BlueprintCallable, Category = "Quest Manager")
    void UpdateQuestUI() const;

    // Retrieve active quest
    UFUNCTION(BlueprintCallable, Category = "Quest Manager")
    UQuest* GetActiveQuest() const;
};