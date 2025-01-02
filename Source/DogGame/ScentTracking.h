#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemScent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "ScentTracking.generated.h"

class ADogCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DOGGAME_API UScentTracking : public USceneComponent
{
	GENERATED_BODY()

public:	
	UScentTracking();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void StartScentTracking(); //Start tracking scents
	void StopScentTracking();  //Stop tracking scents

	bool bIsTracking = false; //chekck iss tracking

private:

	TArray<UItemScent*> ItemScents; //List of scents to track

	UItemScent* ClosestScent;
	FVector CurrentDirection; //Direction towards the closest scent

	void UpdateScentDirection(); //Update the direction vector
	//void SpawnTrailEffect();
	void FindClosestScent();
	void CreatePathToScent();


	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	UNiagaraSystem* TrailNiagaraEffect;

	// Configuration for the trail
	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	int32 NumTrailPoints = 20;  // Number of points along the path

	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	float TrailPointSpacing = 50.0f;  // Distance between trail points
};
