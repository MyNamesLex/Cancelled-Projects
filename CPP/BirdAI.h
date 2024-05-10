#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BirdAI.generated.h"

UCLASS()
class EXTRACTSHOOTER_API ABirdAI : public AActor
{
    GENERATED_BODY()

public:
    ABirdAI();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        bool bIsFlyingAnimation; // Animation state
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        bool Move = true;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        float FlightSpeedMax = 500.0f; // Adjust as needed

private:
    FVector InitialLocation;
    FVector TargetLocation;

    float MaxFlightDistance = 8000;
    float FlightSpeedMin = 300.0f; // Adjust as needed

    float MinFlightAltitude = 100.0f;
    float MaxFlightAltitude = 500.0f;

    void FlyToRandomLocation();
};