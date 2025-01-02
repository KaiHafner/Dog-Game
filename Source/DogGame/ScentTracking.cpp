#include "ScentTracking.h"
#include "ItemScent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DogCharacter/DogCharacter.h"
#include "NiagaraFunctionLibrary.h"
#include <Kismet/GameplayStatics.h>

UScentTracking::UScentTracking()
{
	PrimaryComponentTick.bCanEverTick = true;
}

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

    if (ClosestDistance >= 1000.0f)
    {
        FString DebugMessage = FString::Printf(TEXT("Closest Scent Item Distance: %f"), ClosestDistance);
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, DebugMessage);
    }
    else if(ClosestDistance >= 500.0f)
    {
        FString DebugMessage = FString::Printf(TEXT("Closest Scent Item Distance: %f"), ClosestDistance);
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Orange, DebugMessage);
    }
    else if (ClosestDistance >= 0.0f)
    {
        FString DebugMessage = FString::Printf(TEXT("Closest Scent Item Distance: %f"), ClosestDistance);
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, DebugMessage);
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
        CreatePathToScent(); // Generate the trail path
    }
}

void UScentTracking::CreatePathToScent()
{
    if (!TrailNiagaraEffect || !ClosestScent)
    {
        return;
    }

    FVector PlayerLocation = GetOwner()->GetActorLocation();
    FVector TargetLocation = ClosestScent->ScentLocation;

    FVector PathDirection = (TargetLocation - PlayerLocation).GetSafeNormal(); // Direction vector
    float TotalDistance = FVector::Dist(PlayerLocation, TargetLocation);

    for (int32 i = 0; i < NumTrailPoints; ++i)
    {
        float DistanceAlongPath = i * TrailPointSpacing;

        // Ensure we don't exceed the total distance
        if (DistanceAlongPath > TotalDistance)
        {
            break;
        }

        // Calculate the position along the path
        FVector TrailPoint = PlayerLocation + PathDirection * DistanceAlongPath;

        // Spawn the Niagara system at the calculated position
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(
            GetWorld(),
            TrailNiagaraEffect,
            TrailPoint,
            FRotator::ZeroRotator
        );
    }
}




