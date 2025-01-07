#include "ScentTracking.h"
#include "ItemScent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DogCharacter/DogCharacter.h"
#include "NavigationSystem.h"
#include <Kismet/GameplayStatics.h>

UScentTracking::UScentTracking(): ClosestScent(nullptr), TrailNiagaraEffect(nullptr)
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UScentTracking::BeginPlay()
{
    Super::BeginPlay();

    TArray<AActor*> AllActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), AllActors);

    for (const AActor* Actor : AllActors)
    {
        if (UItemScent* ScentComponent = Actor->FindComponentByClass<UItemScent>())
        {
            ItemScents.Add(ScentComponent);
        }
    }
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
    TArray<AActor*> AllActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), AllActors);

    FVector PlayerLocation = GetOwner()->GetActorLocation();
    float ClosestDistance = FLT_MAX;
    ClosestScent = nullptr;

    for (const AActor* Actor : AllActors)
    {
        if (UItemScent* ScentComponent = Actor->FindComponentByClass<UItemScent>())
        {
            float Distance = FVector::Dist(PlayerLocation, ScentComponent->ScentLocation);
            if (Distance < ClosestDistance)
            {
                ClosestDistance = Distance;
                ClosestScent = ScentComponent;
            }
        }
    }

    if (ClosestScent)
    {
        CurrentDirection = ClosestScent->ScentLocation - PlayerLocation;
        CurrentDirection.Normalize();
    }
}

void UScentTracking::UpdateScentDirection() const
{
    const ADogCharacter* PlayerCharacter = Cast<ADogCharacter>(GetOwner());
    if (PlayerCharacter && ClosestScent)
    {
        CreatePathToScent();
    }
}

void UScentTracking::CreatePathToScent() const
{
    if (!ClosestScent || !TrailNiagaraEffect) //KAI DO NOT REMOVE THIS FIXES CRASHES WHEN NO SCENTED OBJECT
    {
        return; //simple fix but slammed head for it....
    }
    
    //Get the nav system
    UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
    if (!NavSys)
    {
        return;
    }

    //Get the starting and target locations
    FVector PlayerLocation = GetOwner()->GetActorLocation();
    FVector TargetLocation = ClosestScent->ScentLocation;

    //Find a path using the nav mesh
    FNavAgentProperties NavAgentProps;
    FPathFindingQuery Query(
        GetOwner(),
        *NavSys->GetDefaultNavDataInstance(),
        PlayerLocation,
        TargetLocation
    );

    FPathFindingResult PathResult = NavSys->FindPathSync(NavAgentProps, Query);

    if (!PathResult.IsSuccessful() || !PathResult.Path.IsValid()) //STOPS CRASHES WHEN UNSUCCESSFUL 
    {
        return;
    }

    TArray<FNavPathPoint> PathPoints = PathResult.Path->GetPathPoints();

    //Spawn Niagara particles along the path
    for (int32 i = 0; i < PathPoints.Num(); ++i)
    {
        constexpr float ParticleHeightOffset = 50.0f; //constexpr determined at compile time 
        FVector TrailPoint = PathPoints[i].Location;
        
        TrailPoint.Z += ParticleHeightOffset; //Particles height offset

        //Spawn niagara effect
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(
            GetWorld(),
            TrailNiagaraEffect,
            TrailPoint,
            FRotator::ZeroRotator
        );

        //spacing between particles
        if (i > 0)
        {
            FVector PreviousPoint = PathPoints[i - 1].Location;
            float Distance = FVector::Dist(PreviousPoint, TrailPoint);
            
            //Adds missing particles if spacing is too far
            if (Distance > TrailPointSpacing)
            {
                int32 NumIntermediatePoints = FMath::FloorToInt(Distance / TrailPointSpacing);
                FVector Direction = (TrailPoint - PreviousPoint).GetSafeNormal();

                for (int32 j = 1; j <= NumIntermediatePoints; ++j)
                {
                    FVector IntermediatePoint = PreviousPoint + Direction * (j * TrailPointSpacing);

                    //Apply height offset to extra points as well
                    IntermediatePoint.Z += ParticleHeightOffset;

                    UNiagaraFunctionLibrary::SpawnSystemAtLocation(
                        GetWorld(),
                        TrailNiagaraEffect,
                        IntermediatePoint,
                        FRotator::ZeroRotator
                    );
                }
            }
        }
    }
}






