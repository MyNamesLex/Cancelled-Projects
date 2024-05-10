// Fill out your copyright notice in the Description page of Project Settings.


#include "MainBoss.h"

// Sets default values
AMainBoss::AMainBoss()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainBoss::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainBoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

