// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WriteSaveFile.generated.h"

UCLASS()
class EXTRACTSHOOTER_API AWriteSaveFile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWriteSaveFile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void WriteSaveDataToFile();

	void ReadSaveDataFile();

	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool ReadSaveDataFileBool();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool Read = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool Write = false;
};
