// Fill out your copyright notice in the Description page of Project Settings.


#include "ChoiceImpact.h"
#include <random>
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/GameplayStatics.h"
#include <iostream>
#include <sstream>
#include <vector>

// Sets default values
AChoiceImpact::AChoiceImpact()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AChoiceImpact::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AChoiceImpact::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChoiceImpact::ChoiceImpactFind(int Choice, FString ChoiceImpactDesc, int RowName, APlayerMovement* Player, FString PositiveSubtitleBlueprint, FString NegativeSubtitleBlueprint, FString PositiveEffectFunction, FString NegativeEffectFunction)
{
	switch (Choice)
	{
		case 1:
			SplitStrings(ChoiceImpactDesc, PositiveSubtitleBlueprint, NegativeSubtitleBlueprint, 1, PositiveEffectFunction, NegativeEffectFunction);
			break;
		case 2:
			SplitStrings(ChoiceImpactDesc, PositiveSubtitleBlueprint, NegativeSubtitleBlueprint, 2, PositiveEffectFunction, NegativeEffectFunction);
			break;
		case 3:
			SplitStrings(ChoiceImpactDesc, PositiveSubtitleBlueprint, NegativeSubtitleBlueprint, 3, PositiveEffectFunction, NegativeEffectFunction);
			break;
		case 4:
			SplitStrings(ChoiceImpactDesc, PositiveSubtitleBlueprint, NegativeSubtitleBlueprint, 4, PositiveEffectFunction, NegativeEffectFunction);
			break;
		default:
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("CHOICE INT IS NOT 1 - 4"));
			break;
	}
}

void AChoiceImpact::ChoiceImpactFunc(FString EffectFunctionFString)
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("ChoiceImpactFunc"));

	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, EffectFunctionFString);

	if (PlayerVar == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, "PLAYER VAR NULL, CHOICE IMPACT FUNC");
		AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerMovement::StaticClass());

		if (FoundActor != nullptr)
		{
			PlayerVar = Cast<APlayerMovement>(FoundActor);
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, "FOUND PLAYER VAR");
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, "TRIED TO FIND PLAYER VAR, DID NOT FIND IT");
		}
	}
	if (EffectFunctionFString == "RemoveCurrentItem")
	{
		RemoveItemFromInventory(PlayerVar->PlayerCurrentInvSlot);
	}

	if (EffectFunctionFString == "RemoveRNGItem")
	{
		int rngslot = FMath::RandRange(0, PlayerVar->PlayerInventorySize);
		RemoveItemFromInventory(rngslot);
	}

	if (EffectFunctionFString == "AddRNGHealth")
	{
		int addhealth = FMath::RandRange(0, 50);
		PlayerVar->PlayerHealth += addhealth;
	}

	if (EffectFunctionFString == "TakeDamage25")
	{
		PlayerVar->DealDamageToPlayer(25);
	}

	if (EffectFunctionFString == "TakeDamage20")
	{
		PlayerVar->DealDamageToPlayer(20);
	}

	if (EffectFunctionFString == "TakeDamage15")
	{
		PlayerVar->DealDamageToPlayer(15);
	}

	if (EffectFunctionFString == "TakeDamage10")
	{
		PlayerVar->DealDamageToPlayer(10);
	}

	if (EffectFunctionFString == "TakeDamage5")
	{
		PlayerVar->DealDamageToPlayer(5);
	}

	if (EffectFunctionFString == "PickUpItem A90 Rifle")
	{
		PlayerVar->PickupItem("A90 Rifle", 25, "Rifle", 0.005, 30, 0.1, "Weapon", "", "", "", "",false,30,0,0,0);
	}

	if (EffectFunctionFString == "PickUpItem A70 Shotgun")
	{
		PlayerVar->PickupItem("A70 Shotgun", 75, "SingleFireTwoHand", 0.1, 5, 1, "Weapon", "", "", "", "", false, 0, 5, 0, 0);
	}

	if (EffectFunctionFString == "PickUpItem A60 Pistol")
	{
		PlayerVar->PickupItem("A60 Pistol", 15, "Pistol", 0.01, 12, 0.5, "Weapon", "", "", "", "", false, 0, 0, 0, 60);
	}

	if (EffectFunctionFString == "PickUpItem A120 Sniper")
	{
		PlayerVar->PickupItem("A120 Sniper", 100, "SingleFireTwoHand", 0, 12, 2.0, "Weapon", "", "", "", "", true, 0, 12, 0, 0);
	}

	if (EffectFunctionFString == "PickUpItem A10 Grenade")
	{
		PlayerVar->PickupItem("A10 Grenade", 1000, "Item", 0, 0, 0, "Projectile", "", "", "", "", false, 0, 0, 0, 0);
	}

	if (EffectFunctionFString == "LoseEverything")
	{
		for (int i = 0; i < PlayerVar->PlayerInventorySize; i++)
		{
			RemoveItemFromInventory(i);
		}

		for (int i = 0; i < PlayerVar->PlayerInventorySize; i++)
		{
			RemoveItemFromInventory(i);
		}

		for (int i = 0; i < PlayerVar->PlayerInventorySize; i++)
		{
			RemoveItemFromInventory(i);
		}

		for (int i = 0; i < PlayerVar->PlayerInventorySize; i++)
		{
			RemoveItemFromInventory(i);
		}

		for (int i = 0; i < PlayerVar->PlayerInventorySize; i++)
		{
			RemoveItemFromInventory(i);
		}

		for (int i = 0; i < PlayerVar->PlayerInventorySize; i++)
		{
			RemoveItemFromInventory(i);
		}

		for (int i = 0; i < PlayerVar->PlayerInventorySize; i++)
		{
			RemoveItemFromInventory(i);
		}

		for (int i = 0; i < PlayerVar->PlayerInventorySize; i++)
		{
			RemoveItemFromInventory(i);
		}
	}

	// Player->PickupItem("M16 Rifle", 5, "Rifle", 5, 5, 1, "Weapon", "", "", "", "");
	// Player->PickupItem("Speed", 0, "Item", 0, 0, 0, "Speed", "Fast", "High", "", "");
	// Player->DealDamageToPlayer(100);
	//RemoveItemFromInventory(Player->PlayerCurrentInvSlot);
	//FString t = FString::FromInt(RowName);
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, t);
}

void AChoiceImpact::SplitStrings(FString ChoiceImpactDesc, FString PositiveSubtitleBlueprint, FString NegativeSubtitleBlueprint, int Choice, FString PositiveEffectFunction, FString NegativeEffectFunction)
{
	FString PercentageChance, RightSTR;

	bool Split = ChoiceImpactDesc.Split(">>", &PercentageChance, &RightSTR, ESearchCase::CaseSensitive, ESearchDir::FromStart);

	tmp = PercentageChance;

	bool Split2 = tmp.Split("/", &SuccessChance, &FailChance, ESearchCase::CaseSensitive, ESearchDir::FromStart);

	FStringChancesToInt();

	tmp = RightSTR;

	bool Split3 = tmp.Split(">>", &PositiveEventText, &NegativeEventText, ESearchCase::CaseSensitive, ESearchDir::FromStart);

	FString PRightString;
	FString PC1;
	FString PC2;
	FString PC3;
	FString PC4;

	FString NRightString;
	FString NC1;
	FString NC2;
	FString NC3;
	FString NC4;

	bool PSplit;
	bool NSplit;
	bool PSplit2;
	bool NSplit2;
	bool PSplit3;
	bool NSplit3;
	bool PSplit4;
	bool NSplit4;

	switch (Choice)
	{
		case 1:
			PSplit = PositiveSubtitleBlueprint.Split(">>", &PC1, &PRightString, ESearchCase::CaseSensitive, ESearchDir::FromStart);
			NSplit = NegativeSubtitleBlueprint.Split(">>", &NC1, &NRightString, ESearchCase::CaseSensitive, ESearchDir::FromStart);

			if (ShowPositiveEffect == true)
			{
				SetEventText(PositiveEventText);
				SetSubtitleText(PC1);
			}

			if (ShowNegativeEffect == true)
			{
				SetEventText(NegativeEventText);
				SetSubtitleText(NC1);
			}

			break;
		case 2:
			PSplit = PositiveSubtitleBlueprint.Split(">>", &PC1, &PRightString, ESearchCase::CaseSensitive, ESearchDir::FromStart);
			NSplit = NegativeSubtitleBlueprint.Split(">>", &NC1, &NRightString, ESearchCase::CaseSensitive, ESearchDir::FromStart);
			PSplit2 = PRightString.Split(">>", &PRightString, &PC2, ESearchCase::CaseSensitive, ESearchDir::FromStart);
			NSplit2 = NRightString.Split(">>", &NRightString, &NC2, ESearchCase::CaseSensitive, ESearchDir::FromStart);

			if (ShowPositiveEffect == true)
			{
				SetEventText(PositiveEventText);
				SetSubtitleText(PRightString);
			}

			if (ShowNegativeEffect == true)
			{
				SetEventText(NegativeEventText);
				SetSubtitleText(NRightString);
			}
			break;
		case 3:
			PSplit = PositiveSubtitleBlueprint.Split(">>", &PC1, &PRightString, ESearchCase::CaseSensitive, ESearchDir::FromStart);
			NSplit = NegativeSubtitleBlueprint.Split(">>", &NC1, &NRightString, ESearchCase::CaseSensitive, ESearchDir::FromStart);
			PSplit2 = PRightString.Split(">>", &PRightString, &PC2, ESearchCase::CaseSensitive, ESearchDir::FromStart);
			NSplit2 = NRightString.Split(">>", &NRightString, &NC2, ESearchCase::CaseSensitive, ESearchDir::FromStart);
			PSplit3 = PC2.Split(">>", &PRightString, &PC3, ESearchCase::CaseSensitive, ESearchDir::FromStart);
			NSplit3 = NC2.Split(">>", &NRightString, &NC3, ESearchCase::CaseSensitive, ESearchDir::FromStart);

			if (ShowPositiveEffect == true)
			{
				SetEventText(PositiveEventText);
				SetSubtitleText(PRightString);
			}

			if (ShowNegativeEffect == true)
			{
				SetEventText(NegativeEventText);
				SetSubtitleText(NRightString);
			}
			break;
		case 4:
			PSplit = PositiveSubtitleBlueprint.Split(">>", &PC1, &PRightString, ESearchCase::CaseSensitive, ESearchDir::FromStart);
			NSplit = NegativeSubtitleBlueprint.Split(">>", &NC1, &NRightString, ESearchCase::CaseSensitive, ESearchDir::FromStart);
			PSplit2 = PRightString.Split(">>", &PRightString, &PC2, ESearchCase::CaseSensitive, ESearchDir::FromStart);
			NSplit2 = NRightString.Split(">>", &NRightString, &NC2, ESearchCase::CaseSensitive, ESearchDir::FromStart);
			PSplit3 = PC2.Split(">>", &PRightString, &PC3, ESearchCase::CaseSensitive, ESearchDir::FromStart);
			NSplit3 = NC2.Split(">>", &NRightString, &NC3, ESearchCase::CaseSensitive, ESearchDir::FromStart);
			PSplit4 = PC3.Split(">>", &PRightString, &PC4, ESearchCase::CaseSensitive, ESearchDir::FromStart);
			NSplit4 = NC3.Split(">>", &NRightString, &NC4, ESearchCase::CaseSensitive, ESearchDir::FromStart);

			if (ShowPositiveEffect == true)
			{
				SetEventText(PositiveEventText);
				SetSubtitleText(PC3);
			}

			if (ShowNegativeEffect == true)
			{
				SetEventText(NegativeEventText);
				SetSubtitleText(NC3);
			}
			break;
	}

	if (ShowPositiveEffect == true)
	{
		// Delimiter
		FString Delimiter = ">>";

		// Array to store split strings
		TArray<FString> SplitStrings;

		// Split the input string
		SplitString(PositiveEffectFunction, Delimiter, SplitStrings);

		switch (Choice)
		{
			case 1:
				PositiveEffectFunctionFString = SplitStrings[0];
				break;
			case 2:
				PositiveEffectFunctionFString = SplitStrings[1];
				break;
			case 3:
				PositiveEffectFunctionFString = SplitStrings[2];
				break;
			case 4:
				PositiveEffectFunctionFString = SplitStrings[3];
				break;
		}

		ChoiceImpactFunc(PositiveEffectFunctionFString);
	}

	if (ShowNegativeEffect == true)
	{
		// Delimiter
		FString Delimiter = ">>";

		// Array to store split strings
		TArray<FString> SplitStrings;

		// Split the input string
		SplitString(NegativeEffectFunction, Delimiter, SplitStrings);

		switch (Choice)
		{
			case 1:
				NegativeEffectFunctionFString = SplitStrings[0];
				break;
			case 2:
				NegativeEffectFunctionFString = SplitStrings[1];
				break;
			case 3:
				NegativeEffectFunctionFString = SplitStrings[2];
				break;
			case 4:
				NegativeEffectFunctionFString = SplitStrings[3];
				break;
		}

		ChoiceImpactFunc(NegativeEffectFunctionFString);
	}
}

void AChoiceImpact::SplitString(const FString& InputString, const FString& Delimiter, TArray<FString>& OutStrings)
{
	InputString.ParseIntoArray(OutStrings, *Delimiter, true);
}

void AChoiceImpact::SetEventText(FString EventText)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("SetEventText CPP"));
	EventStringText = EventText;
}

FString AChoiceImpact::GetEventText()
{
	return EventStringText;
}

void AChoiceImpact::SetSubtitleText(FString SubtitleText)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("SetSubtitleText CPP"));
	SubtitleTextFString = SubtitleText;
}

FString AChoiceImpact::GetSubtitleText()
{
	return SubtitleTextFString;
}