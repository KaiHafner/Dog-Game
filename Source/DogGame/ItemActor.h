#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemScent.h"
#include "Components/SphereComponent.h"
#include "ItemActor.generated.h"

UCLASS()
class DOGGAME_API AItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UItemScent* ItemScent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	USphereComponent* CollisionComponent;
	
private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
	
};
