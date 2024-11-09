#include "ItemActor.h"
#include "ItemScent.h" 


AItemActor::AItemActor()
{
    PrimaryActorTick.bCanEverTick = false;

    // Create and attach the ItemScentComponent
    ItemScent = CreateDefaultSubobject<UItemScent>(TEXT("ItemScentComponent"));
}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();

    if (ItemScent)
    {
        ItemScent->ScentStrength = 1.5f; // Example: set a custom scent strength
    }
	
}

// Called every frame
void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

