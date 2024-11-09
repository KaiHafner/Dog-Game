#include "ScentTracking.h"
#include "ItemScent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DogCharacter/DogCharacter.h"

#include <Kismet/GameplayStatics.h>

UScentTracking::UScentTracking()
{
	PrimaryComponentTick.bCanEverTick = true;
	bIsTracking = false;
}


// Called when the game starts
void UScentTracking::BeginPlay()
{
	Super::BeginPlay();

    TArray<AActor*> AllActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), AllActors);

    for (AActor* Actor : AllActors)
    {
        UItemScent* ScentComponent = Actor->FindComponentByClass<UItemScent>();
        if (ScentComponent)
        {
            ItemScents.Add(ScentComponent);
        }
    }
}


void UScentTracking::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (bIsTracking)
    {
        FindClosestScent();
        UpdateScentDirection();
    }
}

void UScentTracking::StartScentTracking()
{
    bIsTracking = true;
}

void UScentTracking::StopScentTracking()
{
    bIsTracking = false;
}

void UScentTracking::FindClosestScent()
{
    FVector PlayerLocation = GetOwner()->GetActorLocation();
    float ClosestDistance = FLT_MAX;
    UItemScent* NewClosestScent = nullptr;

    for (UItemScent* ScentComponent : ItemScents)
    {
        if (ScentComponent)
        {
            float Distance = FVector::Dist(PlayerLocation, ScentComponent->ScentLocation);
            if (Distance < ClosestDistance)
            {
                ClosestDistance = Distance;
                NewClosestScent = ScentComponent;
            }
        }
    }

    ClosestScent = NewClosestScent;

    if (ClosestScent)
    {
        CurrentDirection = ClosestScent->ScentLocation - PlayerLocation;
        CurrentDirection.Normalize();
    }
}

void UScentTracking::UpdateScentDirection()
{
    ADogCharacter* PlayerCharacter = Cast<ADogCharacter>(GetOwner());
    if (PlayerCharacter && ClosestScent)
    {
        // Example of updating a UI element or visual indicator
        // You can use CurrentDirection to manipulate an arrow or UI compass
    }
}




