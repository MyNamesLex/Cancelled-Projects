// Fill out your copyright notice in the Description page of Project Settings.


#include "CutsceneControl.h"

// Sets default values
ACutsceneControl::ACutsceneControl()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACutsceneControl::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACutsceneControl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

