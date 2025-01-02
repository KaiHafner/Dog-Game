#include "ItemActor.h"
#include "ItemScent.h" 
#include "Quest.h"


AItemActor::AItemActor()
{
    PrimaryActorTick.bCanEverTick = false;

    // Create and attach the ItemScentComponent
    ItemScent = CreateDefaultSubobject<UItemScent>(TEXT("ItemScentComponent"));
    ItemScent->SetupAttachment(RootComponent);

}

void AItemActor::BeginPlay()
{
	Super::BeginPlay();

    if (ItemScent)
    {
        ItemScent->ScentStrength = 1.5f;
    }
	
}

void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

