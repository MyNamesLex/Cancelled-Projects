// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerMovement.h"
#include "GameFramework/Actor.h"
#include "ChoiceImpact.generated.h"

UCLASS()
class EXTRACTSHOOTER_API AChoiceImpact : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChoiceImpact();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void ChoiceImpactFind(int Choice, FString ChoiceImpactDesc, int RowName, APlayerMovement* Player, FString PositiveSubtitleBlueprint, FString NegativeSubtitleBlueprint, FString PositiveEffectFunction, FString NegativeEffectFunction);

	UFUNCTION(BlueprintImplementableEvent)
		void RemoveItemFromInventory(int Index);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void LevelToLoad(FName LevelName);

	UPROPERTY(BlueprintReadWrite)
		FName NextLevelName;

	UPROPERTY(BlueprintReadWrite)
		FString tmp;

	UPROPERTY(BlueprintReadWrite)
		FString EventStringText;

	UPROPERTY(BlueprintReadWrite)
		FString SubtitleTextFString;

	UPROPERTY(BlueprintReadWrite)
		FString SuccessChance;

	UPROPERTY(BlueprintReadWrite)
		FString FailChance;

	UPROPERTY(BlueprintReadWrite)
		FString PositiveEventText;

	UPROPERTY(BlueprintReadWrite)
		FString NegativeEventText;

	UPROPERTY(BlueprintReadWrite)
		int SuccessChanceInt;

	UPROPERTY(BlueprintReadWrite)
		int FailChanceInt;

	UFUNCTION(BlueprintCallable)
		FString GetEventText();

	UFUNCTION(BlueprintCallable)
		FString GetSubtitleText();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SetPositiveOrNegative();

	UFUNCTION(BlueprintImplementableEvent)
		void FStringChancesToInt();

	UPROPERTY(BlueprintReadWrite)
		bool ShowPositiveEffect = false;

	UPROPERTY(BlueprintReadWrite)
		bool ShowNegativeEffect = false;

	UFUNCTION(BlueprintCallable)
		void ChoiceImpactFunc(FString EffectFunctionFString);
	UPROPERTY(BlueprintReadWrite)
		FString FunctionText;

	UPROPERTY(BlueprintReadWrite)
		FString NegativeEffectFunctionFString;

	UPROPERTY(BlueprintReadWrite)
		FString PositiveEffectFunctionFString;

	UPROPERTY(BlueprintReadWrite)
		APlayerMovement* PlayerVar;

	void SplitStrings(FString ChoiceImpactDesc, FString PositiveSubtitleBlueprint, FString NegativeSubtitleBlueprint, int Choice, FString PositiveEffectFunction, FString NegativeEffectFunction);
	void SetEventText(FString EventText);
	void SetSubtitleText(FString SubtitleText);

	void SplitString(const FString& InputString, const FString& Delimiter, TArray<FString>& OutStrings);
};
