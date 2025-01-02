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

	void FindClosestScent();
	void UpdateScentDirection();
	void CreatePathToScent();

	void RecreatePath();

	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	UNiagaraSystem* TrailNiagaraEffect;

	//Config the trail 
	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	int32 NumTrailPoints = 1000;  //Max Number of points

	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	float TrailPointSpacing = 100.0f;  //Distance between trail points

	FTimerHandle PathUpdateTimerHandle;
};
