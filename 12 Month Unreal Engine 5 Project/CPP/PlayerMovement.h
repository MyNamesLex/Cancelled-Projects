// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/Character.h"
#include "PlayerMovement.generated.h"

UCLASS()
class EXTRACTSHOOTER_API APlayerMovement : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerMovement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite)
		bool PistolEquipped = false;
	UPROPERTY(BlueprintReadWrite)
		bool JustHealed = false;
	UPROPERTY(BlueprintReadWrite)
		bool JustUsedSpeedPack = false;
	UPROPERTY(BlueprintReadWrite)
		bool RifleEquipped = false;
	UPROPERTY(BlueprintReadWrite)
		bool isScoped = false;
	UPROPERTY(BlueprintReadWrite)
		bool SingleFireOneHandEquipped = false;
	UPROPERTY(BlueprintReadWrite)
		bool SingleFireTwoHandEquipped = false;
	UPROPERTY(BlueprintReadWrite)
		bool ItemEquipped = false;
	UPROPERTY(BlueprintReadWrite)
		bool isCrouching = false;
	UPROPERTY(BlueprintReadWrite)
		bool Dead = false;
	UPROPERTY(BlueprintReadWrite)
		bool Stunned = false;
	UPROPERTY(BlueprintReadWrite)
		int PlayerDamage = 100;
	UPROPERTY(BlueprintReadWrite)
		FString PlayerWeaponType;
	UPROPERTY(BlueprintReadWrite)
		float PlayerRecoil;
	UPROPERTY(BlueprintReadWrite)
		int PlayerMagSize;
	UPROPERTY(BlueprintReadWrite)
		int PlayerRange = 30000;
	UPROPERTY(BlueprintReadWrite)
		float PlayerReloadTime = 1;
	UPROPERTY(BlueprintReadWrite)
		float PlayerFireRate;
	UPROPERTY(BlueprintReadWrite)
		float LowSpeedIncrease = 100;
	UPROPERTY(BlueprintReadWrite)
		float MediumSpeedIncrease = 150;
	UPROPERTY(BlueprintReadWrite)
		float HighSpeedIncrease = 300;
	UPROPERTY(BlueprintReadWrite)
		float SprintingSpeed = 600;
	UPROPERTY(BlueprintReadWrite)
		bool isShootingRifle;
	UPROPERTY(BlueprintReadWrite)
		bool isShootingPistol;
	UPROPERTY(BlueprintReadWrite)
		bool isMeleeing;
	UPROPERTY(BlueprintReadWrite)
		bool isInDialogue;
	UPROPERTY(BlueprintReadWrite)
		bool Paused = false;
	UPROPERTY(BlueprintReadWrite)
		bool WeaponCanADS = false;
	UPROPERTY(BlueprintReadWrite)
		float PlayerHealth = 100;
	UPROPERTY(BlueprintReadWrite)
		int PlayerCurrentInvSlot;
	UPROPERTY(BlueprintReadWrite)
		int PlayerInventorySize;
	UPROPERTY(BlueprintReadWrite)
		int AssaultRifleAmmo;
	UPROPERTY(BlueprintReadWrite)
		int SniperAmmo;
	UPROPERTY(BlueprintReadWrite)
		int ShotgunAmmo;
	UPROPERTY(BlueprintReadWrite)
		int PistolAmmo;
	UPROPERTY(BlueprintReadWrite)
		FString PlayerItemType;
	UPROPERTY(BlueprintReadWrite)
		FString PlayerSpeedBoostIntensity;
	UPROPERTY(BlueprintReadWrite)
		FString PlayerSpeedBoostDuration;
	UPROPERTY(BlueprintReadWrite)
		FString PlayerHealIntensity;
	UPROPERTY(BlueprintReadWrite)
		FString PlayerHealDuration;
	UPROPERTY(BlueprintReadWrite)
		FString CurrentWeaponName;
	UPROPERTY(BlueprintReadWrite)
		float EnableFireTime = 0;
	UFUNCTION(BlueprintImplementableEvent)
		void CheckInterface(AActor* actorHit);
	UFUNCTION(BlueprintImplementableEvent)
		void CheckInterfaceWithDamageFalloff(AActor* actorHit);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void CamShake();
	UFUNCTION(BlueprintCallable)
		void CallItemUseCPP();
	UFUNCTION(BlueprintImplementableEvent)
		void TriedToShootWhileEquipTimerActive();
	UFUNCTION(BlueprintImplementableEvent)
		void MoveWeapon();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void CallOrganiseAmmoInMag(int index);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void VisualFXShooting();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void ApplyBulletHole(FVector HitLocation, FVector HitNormal, UPrimitiveComponent* AttachToComponent);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void ResetWeaponLocation();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void CallFOVIncrease();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void CallFOVDecrease();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void RemoveCurrentItem();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void TurnOnLight();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void TurnOffLight();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SelectARandomWeapon();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void CallSetAmmoInBulletPlayerBlueprint();
	UFUNCTION(BlueprintCallable)
		void ClearTimers();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void LowerInventorySize(int ReduceByValue);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void RaiseInventorySize(int RaiseByValue);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void CallPlayerUISetHealthText(int HealthAmount);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void CallPlayerUIPopupText(const FString& PopupTextString, float OnScreenDelay);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void CallRemovePlayerUIPopupText();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void DealDamageToPlayer(float Damage);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void RemoveBulletFromAmmoBoxes(const FString& AmmoType);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void PickupItem(const FString& Item, int Damage, const FString& WeaponType, float WeaponRecoil, int MagSize, float FireRate, const FString& ItemType, const FString& SpeedBoostDuration, const FString& SpeedBoostIntensity, const FString& HealIntensity, const FString& HealDuration, bool CanADS, int RifleAmmoInt, int SniperAmmoInt, int ShotgunAmmoInt, int PistolAmmoInt);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void ADS(float TimeToADS, float Zoom, bool ScopeIn);
	UFUNCTION(BlueprintCallable)
		void EquipTime();
	UFUNCTION(BlueprintCallable)
		void Shoot();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void GetCurrentWeaponName();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SetAmmoInBulletPlayerBlueprint();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void CallBPAudioManagerSFX(const FString& AudioName, FVector Location);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void CallBPAudioManagerSFX2D(const FString& AudioName);
	UFUNCTION(BlueprintImplementableEvent, Category = Tracking)
		void CallBPAudioManagerCheckIfCurrentSFXIsPlaying(const FString& AudioName, bool& Result);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void RemoveItemByName(const FString& ItemName);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void RemoveItemByIndex(int Index);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void ProceedDialogue();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void StartDialogue();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void HideBPADS();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void UpdatePlayerAmmoOnUI();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void ThrowA10Grenade(float Force, FVector Direction);
	UFUNCTION(BlueprintCallable)
		void ReloadTimerFunc();
	UFUNCTION(BlueprintCallable)
		void UnarmedMelee();
	UFUNCTION(BlueprintCallable)
		virtual bool CheckForShootTimers();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void CallSetEquippedItemTextUI();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void CallClearEquippedItemTextUI();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void CallVFXChargeShot();
	UPROPERTY(BlueprintReadWrite)
		bool CanMelee = true;

	UPROPERTY(BlueprintReadWrite)
		bool CallBPAudioManagerCheckIfCurrentSFXIsPlayingFunctionBool = false;

	UPROPERTY(BlueprintReadWrite)
		bool inTutorial = false;

	UPROPERTY(BlueprintReadWrite)
		bool inInventory = false;

	UPROPERTY(BlueprintReadWrite)
		bool CanFire = true;

	UPROPERTY(BlueprintReadWrite)
		bool LeaveLevel = false;

	UPROPERTY(BlueprintReadWrite)
		bool OverlappingLevelEnterOrExit = false;

	UPROPERTY(BlueprintReadWrite)
		TArray<AActor*> ActorsToIgnoreRaycast;

	UPROPERTY(BlueprintReadWrite)
		TArray<UPrimitiveComponent*> ComponentsToIgnoreRaycast;

	float MeleeRange = 150.0f;

	UPROPERTY(BlueprintReadWrite)
		int OGMagSize;

	UPROPERTY(BlueprintReadWrite)
		float MouseSensitivity = 0.3;
	UPROPERTY(BlueprintReadWrite)
		float ADSMouseSensitivity = 0.15;
	UPROPERTY(BlueprintReadWrite)
		float OGMouseSensitivity = 0.3;

	UPROPERTY(BlueprintReadWrite)
		float SFXDelay = 0.1;

	void PistolShoot();
	void ChargePistolShot();
	void NormalPistolShot();
	void RifleShoot();
	void SniperShoot();
	void ShotgunShoot();
	void ThrowProjectile();
	void ResetOneShotTimer();
	void CastWithRecoil();
	void CastWithRecoilAndDamageFalloff();
	void CastNoRecoil();
	void UseHealthPackKeybind();
	void UseSpeedPackKeybind();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void FindSpeedPackInInventoryKeybindFunc();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void FindHealthPackInInventoryKeybindFunc();

	UFUNCTION(BlueprintCallable)
		void Reload();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void StartSFXAudioWithDelay(const FString& AudioName, float Delay, FVector Location);

	void CheckToPlaySFX(const FString& AudioName);
	void MouseReleased();
	void UnarmedMeleeTimerFunc();
	void ItemUse();
	void HealthFunc();
	void ApplyHealth();
	void SpeedFunc();
	void ResetSpeed();
	void EnableFire();
	void ADSFunc();
	void ADSUnscope();
	void EnterFunc();
	void LeaveFunc();

	void CastNoRecoilSpread();

	void MoveForward(float AxisVal);
	void MoveRight(float AxisVal);

	void LookRight(float val);
	void LookUp(float val);

	bool StopMultipleMeleeHits = false;

	APlayerCameraManager* PlayerCamera;
};
