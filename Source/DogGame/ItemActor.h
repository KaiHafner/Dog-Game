#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemScent.h"
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
};
