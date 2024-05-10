// Fill out your copyright notice in the Description page of Project Settings.


#include "Claymore.h"

// Sets default values
AClaymore::AClaymore()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AClaymore::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AClaymore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AClaymore::Explosion()
{
	ParticleComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), OuterClaymoreExplosion, GetActorLocation(), GetActorRotation(), FVector(2, 2, 2), true, true);
	ParticleComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), InnerClaymoreExplosion, GetActorLocation(), GetActorRotation(), FVector(2, 2, 2), true, true);
}

