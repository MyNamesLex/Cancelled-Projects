// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "Dialogue.generated.h"

UCLASS()
class EXTRACTSHOOTER_API ADialogue : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADialogue();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString> Dialogue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString> Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ACameraActor*> CutsceneCamera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName NextSceneName;
};
