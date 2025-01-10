#pragma once

#include "CoreMinimal.h"
#include "ItemScent.h"
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

	bool bIsTracking = false; //check is tracking


private:
	TArray<UItemScent*> ItemScents; //List of scents to track
	UItemScent* ClosestScent;
	
	FVector CurrentDirection; //Direction towards the closest scent

	void FindClosestScent();
	void UpdateScentDirection() const;
	void CreatePathToScent() const;

	void RecreatePath();

	UPROPERTY(EditDefaultsOnly, Category = "Trail")
	UNiagaraSystem* TrailNiagaraEffect;

	//Config the trail 
	UPROPERTY(EditDefaultsOnly, Category = "Trail")
	int32 NumTrailPoints = 1000;  //Max Number of points

	UPROPERTY(EditDefaultsOnly, Category = "Trail")
	float TrailPointSpacing = 100.0f;  //Distance between trail points

	FTimerHandle PathUpdateTimerHandle;
};
