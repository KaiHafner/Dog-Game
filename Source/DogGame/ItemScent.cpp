#include "ItemScent.h"

UItemScent::UItemScent()
{
	PrimaryComponentTick.bCanEverTick = false;
	ScentLocation = FVector::ZeroVector;
	ScentStrength = 1.0f;
}

void UItemScent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* Owner = GetOwner())
	{
		ScentLocation = Owner->GetActorLocation();
	}
}

void UItemScent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

