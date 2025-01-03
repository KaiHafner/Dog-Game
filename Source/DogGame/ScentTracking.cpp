#include "ScentTracking.h"
#include "ItemScent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DogCharacter/DogCharacter.h"
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

    //Creates a timer, that repeats every 5 seconds calling to recreate the path
    GetWorld()->GetTimerManager().SetTimer(PathUpdateTimerHandle, this, &UScentTracking::RecreatePath, 5.0f, true);
}

void UScentTracking::StopScentTracking()
{
    bIsTracking = false;

    //Clear the timer if it's active
    GetWorld()->GetTimerManager().ClearTimer(PathUpdateTimerHandle);
}

void UScentTracking::StartScentTracking()
{
    bIsTracking = true;

    //timer set if not going already
    if (!GetWorld()->GetTimerManager().IsTimerActive(PathUpdateTimerHandle))
    {
        GetWorld()->GetTimerManager().SetTimer(PathUpdateTimerHandle, this, &UScentTracking::RecreatePath, 5.0f, true);
    }
}

void UScentTracking::RecreatePath()
{
    FindClosestScent();
    UpdateScentDirection();
    CreatePathToScent();
}

void UScentTracking::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if (bIsTracking)
    {
        FindClosestScent();
    }
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

    //if (ClosestDistance >= 1000.0f)
//{
//    FString DebugMessage = FString::Printf(TEXT("Closest Scent Item Distance: %f"), ClosestDistance);
//    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, DebugMessage);
//}
//else if(ClosestDistance >= 500.0f)
//{
//    FString DebugMessage = FString::Printf(TEXT("Closest Scent Item Distance: %f"), ClosestDistance);
//    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Orange, DebugMessage);
//}
//else if (ClosestDistance >= 0.0f)
//{
//    FString DebugMessage = FString::Printf(TEXT("Closest Scent Item Distance: %f"), ClosestDistance);
//    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, DebugMessage);
//}
}

void UScentTracking::UpdateScentDirection()
{
    ADogCharacter* PlayerCharacter = Cast<ADogCharacter>(GetOwner());
    if (PlayerCharacter && ClosestScent)
    {
        CreatePathToScent();
    }
}

void UScentTracking::CreatePathToScent()
{
    FVector PlayerLocation = GetOwner()->GetActorLocation();
    FVector TargetLocation = ClosestScent->ScentLocation;

    //Direction vector between the player and the target location
    FVector PathDirection = (TargetLocation - PlayerLocation).GetSafeNormal();

    //Calculate the total distance between player and the target
    float TotalDistance = FVector::Dist(PlayerLocation, TargetLocation);

    // Ensure we are always generating trail points, even for shorter distances
    if (TotalDistance < 100.0f)
    {
        TotalDistance = 100.0f;
    }

    // Increase the number of trail points to cover the distance more effectively
    for (int32 i = 0; i < NumTrailPoints; ++i)
    {
        //calcuilate each point along path distance
        float DistanceAlongPath = i * TrailPointSpacing;

        //Caps it at the right distance
        if (DistanceAlongPath > TotalDistance)
        {
            break;
        }

        //calculate the position along the path
        FVector TrailPoint = PlayerLocation + PathDirection * DistanceAlongPath;

        //Spawns niagara in spots
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(
            GetWorld(),
            TrailNiagaraEffect,
            TrailPoint,
            FRotator::ZeroRotator
        );
    }
}






