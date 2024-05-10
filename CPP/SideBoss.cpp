// Fill out your copyright notice in the Description page of Project Settings.


#include "SideBoss.h"

// Sets default values
ASideBoss::ASideBoss()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASideBoss::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASideBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASideBoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

