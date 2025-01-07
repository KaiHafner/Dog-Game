#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Quest.h"
#include "Components/SphereComponent.h"
#include "QuestGiver.generated.h"

UCLASS()
class DOGGAME_API AQuestGiver : public AActor
{
    GENERATED_BODY()

public:
    AQuestGiver();

    //quests that the quest giver can assign
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    TArray<UQuest*> AvailableQuests;

    //assign a quest 
    UFUNCTION(BlueprintCallable, Category = "Quest")
    UQuest* AssignQuest();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    USphereComponent* CollisionSphere;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    TSubclassOf<AActor> ActorToSpawn;
    void SpawnBlueprintActorRandomly();
    
protected:
    virtual void BeginPlay() override;
    void RotateToFacePlayer(AActor* PlayerActor);
    
private:
    //Handle when Another actor overlaps with the sphere
    UFUNCTION()
    void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
        class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);
};