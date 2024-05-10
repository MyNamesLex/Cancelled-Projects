#include "BirdAI.h"
#include <Kismet/KismetMathLibrary.h>

ABirdAI::ABirdAI()
{
    PrimaryActorTick.bCanEverTick = true;

    FlyToRandomLocation();
}
void ABirdAI::BeginPlay()
{
    Super::BeginPlay();
    InitialLocation = GetActorLocation();
    FlyToRandomLocation();
}

void ABirdAI::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (Move == true)
    {
        FVector CurrentLocation = GetActorLocation();
        FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
        float Distance = FVector::Dist(CurrentLocation, TargetLocation);

        FRotator ForwardRotation = Direction.Rotation();

        SetActorRotation(ForwardRotation);

        if (Distance > 5.0f)
        {
            float MoveDistance = FMath::Min(DeltaTime * FMath::RandRange(FlightSpeedMin, FlightSpeedMax), Distance);

            FVector NewLocation = CurrentLocation + Direction * MoveDistance;
            SetActorLocation(NewLocation);
        }
        else
        {
            FlyToRandomLocation();
        }
    }
}

void ABirdAI::FlyToRandomLocation()
{
    TargetLocation = InitialLocation + FVector(FMath::FRandRange(-MaxFlightDistance, MaxFlightDistance), FMath::FRandRange(-MaxFlightDistance, MaxFlightDistance), FMath::FRandRange(MinFlightAltitude, MaxFlightAltitude));
}