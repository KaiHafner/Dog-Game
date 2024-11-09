#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemScent.h"
#include "ScentTracking.generated.h"

class ADogCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DOGGAME_API UScentTracking : public UActorComponent
{
	GENERATED_BODY()

public:	
	UScentTracking();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void StartScentTracking(); // Start tracking scents
	void StopScentTracking();  // Stop tracking scents

	

private:
	bool bIsTracking;         // Is the player actively tracking scents?

	TArray<UItemScent*> ItemScents;  // List of scents to track

	UItemScent* ClosestScent;
	FVector CurrentDirection;  // Direction towards the closest scent

	void UpdateScentDirection();  // Update the direction vector
	void FindClosestScent();      // Find the closest scent source	
};
