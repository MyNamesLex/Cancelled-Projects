// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "GameFramework/Actor.h"
#include "Claymore.generated.h"

class UNiagaraSystem;

UCLASS()
class EXTRACTSHOOTER_API AClaymore : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AClaymore();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void Explosion();

	UPROPERTY(BlueprintReadWrite)
		UNiagaraSystem* OuterClaymoreExplosion;

	UPROPERTY(BlueprintReadWrite)
		UNiagaraSystem* InnerClaymoreExplosion;

	UPROPERTY(BlueprintReadWrite)
		UNiagaraComponent* ParticleComponent;

	UPROPERTY(BlueprintReadWrite)
		bool Triggered = false;

	UPROPERTY(BlueprintReadWrite)
		UMaterialInterface* GroundMat;
};
