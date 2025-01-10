#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemScent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DOGGAME_API UItemScent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UItemScent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scent")
	FVector ScentLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scent")
	float ScentStrength;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
