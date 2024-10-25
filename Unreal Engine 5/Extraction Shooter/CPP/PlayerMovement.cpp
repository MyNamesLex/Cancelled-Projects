// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerMovement.h"

// Sets default values

FTimerHandle RifleShootTimer;
FTimerHandle OneShotTimer;
FTimerHandle NormalPistolShootTimer;
FTimerHandle ChargePistolShootTimer;
FTimerHandle LightTimer;
FTimerHandle ReloadTimer;
FTimerHandle UnarmedMeleeTimer;
FTimerHandle PlayerHealTimer;
FTimerHandle PlayerSpeedTimer;
FTimerHandle EquipTimer;
FTimerHandle SFXTimer;

APlayerMovement::APlayerMovement()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerMovement::BeginPlay()
{
	Super::BeginPlay();
	OGMagSize = PlayerMagSize;
}

// Called every frame
void APlayerMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*
	if (Dead == false && Paused == false)
	{
		if (isShootingPistol == true && PistolEquipped == false)
		{
			GetWorld()->GetTimerManager().ClearTimer(NormalPistolShootTimer);
			GetWorld()->GetTimerManager().ClearTimer(ChargePistolShootTimer);
			isShootingPistol = false;
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("isShootingPistol = true && PistolEquipped = false Bug Triggered, Cleared Timer. isShootingPistol now = false"));
		}

		if (isShootingRifle == true && RifleEquipped == false)
		{
			GetWorld()->GetTimerManager().ClearTimer(RifleShootTimer);
			isShootingRifle = false;
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("isShootingRifle = true && PistolEquipped = false Bug Triggered, Cleared Timer. isShootingRifle now = false"));
		}
	}
	*/
}

// Called to bind functionality to input
void APlayerMovement::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerMovement::Jump);
	PlayerInputComponent->BindAxis("TurnRight", this, &APlayerMovement::LookRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerMovement::LookUp);
	PlayerInputComponent->BindAxis("MoveForward", this, & APlayerMovement::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, & APlayerMovement::MoveRight);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerMovement::Shoot);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &APlayerMovement::MouseReleased);
	PlayerInputComponent->BindAction("ADS", IE_Pressed, this, &APlayerMovement::ADSFunc);
	PlayerInputComponent->BindAction("ADS", IE_Released, this, &APlayerMovement::ADSUnscope);
	PlayerInputComponent->BindAction("Enter", IE_Pressed, this, &APlayerMovement::EnterFunc);
	PlayerInputComponent->BindAction("Leave", IE_Pressed, this, &APlayerMovement::LeaveFunc);
	PlayerInputComponent->BindAction("UseHealth", IE_Pressed, this, &APlayerMovement::UseHealthPackKeybind);
	PlayerInputComponent->BindAction("UseSpeed", IE_Pressed, this, &APlayerMovement::UseSpeedPackKeybind);
}

void APlayerMovement::UseHealthPackKeybind()
{
	FindHealthPackInInventoryKeybindFunc();
}

void APlayerMovement::UseSpeedPackKeybind()
{
	FindSpeedPackInInventoryKeybindFunc();
}

void APlayerMovement::LeaveFunc()
{
	if (OverlappingLevelEnterOrExit == true)
	{
		LeaveLevel = true;
	}
}

void APlayerMovement::MoveForward(float AxisVal)
{
	AddMovementInput(GetActorForwardVector() * AxisVal);
}

void APlayerMovement::MoveRight(float AxisVal)
{
	AddMovementInput(GetActorRightVector() * AxisVal);
}

void APlayerMovement::LookUp(float val)
{
	AddControllerPitchInput(val * MouseSensitivity);
}

void APlayerMovement::LookRight(float val)
{
	AddControllerYawInput(val * MouseSensitivity);
}

// ADS //

void APlayerMovement::ADSFunc()
{
	if (isScoped == false && inInventory == false && CanFire == true && WeaponCanADS == true)
	{
		isScoped = true;
		GetCurrentWeaponName();

		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("ADS"));

		if (WeaponCanADS)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("CAN ADS"));

			if (CurrentWeaponName.Contains("A120"))
			{
				GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("A120 ADS"));
				ADS(0, -1000, true);
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("CAN NOT ADS"));
		}
	}
}

void APlayerMovement::ADSUnscope()
{
	if (isScoped == true)
	{
		isScoped = false;
		HideBPADS();
	}
}

// ENTER FUNC //

void APlayerMovement::EnterFunc()
{
	if (isInDialogue && !inTutorial)
	{
		ProceedDialogue();
		return;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("Either In Tutorial Or isInDialogue Is False"));
	}
}

// MOUSE RELEASE //

void APlayerMovement::MouseReleased()
{
	if (Dead == false && Paused == false && inInventory == false)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("Left Mouse Released"));

		isShootingPistol = false;
		isShootingRifle = false;

		GetWorld()->GetTimerManager().ClearTimer(NormalPistolShootTimer);
		GetWorld()->GetTimerManager().ClearTimer(ChargePistolShootTimer);
		GetWorld()->GetTimerManager().ClearTimer(RifleShootTimer);

		ResetWeaponLocation();

		/*
		if (SingleFireOneHandEquipped == true && GetWorldTimerManager().IsTimerActive(OneShotTimer) == false || SingleFireTwoHandEquipped == true && GetWorldTimerManager().IsTimerActive(OneShotTimer) == false)
		{
			EnableFire();
		}
		*/
	}

	/*
	if (CurrentWeaponName.Contains("A90") && AssaultRifleAmmo != 0)
	{
		CallBPAudioManagerSFX("AssaultRifleStopShooting", GetActorLocation());
	}
	*/
}

// SHOOT FUNCTIONS //

bool APlayerMovement::CheckForShootTimers()
{
	if (GetWorldTimerManager().IsTimerActive(RifleShootTimer) == true || GetWorldTimerManager().IsTimerActive(OneShotTimer) == true ||
		GetWorldTimerManager().IsTimerActive(NormalPistolShootTimer) == true || GetWorldTimerManager().IsTimerActive(ChargePistolShootTimer) == true ||
		GetWorldTimerManager().IsTimerActive(ReloadTimer) == true || GetWorldTimerManager().IsTimerActive(UnarmedMeleeTimer) == true ||
		GetWorldTimerManager().IsTimerActive(EquipTimer) == true)
		{
			return true;
		}
	else
	{
		return false;
	}
}

void APlayerMovement::Shoot()
{
	if (Dead == false && Paused == false && GetWorldTimerManager().IsTimerActive(EquipTimer) == false)
	{
		GetCurrentWeaponName();
		if (PlayerItemType == "Weapon" && inInventory == true)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("CANT SHOOT WEAPON WHILE IN INVENTORY"));
			return;
		}
		UpdatePlayerAmmoOnUI();
		if (CanFire == true)
		{
			// PISTOL //

			if (PistolEquipped == true && GetWorldTimerManager().IsTimerActive(NormalPistolShootTimer) == false && GetWorldTimerManager().IsTimerActive(ChargePistolShootTimer) == false)
			{
				PistolShoot();
				return;
			}

			// RIFLE //

			if (RifleEquipped == true && GetWorldTimerManager().IsTimerActive(RifleShootTimer) == false)
			{
				RifleShoot();
				return;
			}

			// SINGLEFIRETWOHANDED //

			if (SingleFireTwoHandEquipped == true && GetWorldTimerManager().IsTimerActive(OneShotTimer) == false)
			{
				if (CurrentWeaponName.Contains("Sniper") == true)
				{
					SniperShoot();
					return;
				}

				if (CurrentWeaponName.Contains("Shotgun") == true)
				{
					ShotgunShoot();
					return;
				}
			}

			// ITEM //

			if (ItemEquipped == true && GetWorldTimerManager().IsTimerActive(PlayerHealTimer) == false)
			{
				ItemUse();
			}
		}
		/*
		if (RifleEquipped == false && PistolEquipped == false && ItemEquipped == false && SingleFireOneHandEquipped == false && SingleFireTwoHandEquipped == false && CanMelee && GetCharacterMovement()->IsMovingOnGround())
		{
			UnarmedMelee();
		}
		*/
	}

	if (Dead == false && Paused == false && CheckForShootTimers() == true && inInventory == false)
	{
		TriedToShootWhileEquipTimerActive();
	}
}

// ENABLE & EQUIP FUNCTIONS //

void APlayerMovement::EquipTime()
{
	CanFire = false;
	EnableFireTime = 2;
	GetWorld()->GetTimerManager().SetTimer(EquipTimer, this, &APlayerMovement::EnableFire, EnableFireTime, false);
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("CanFire false"));
}

void APlayerMovement::EnableFire()
{
	if (CurrentWeaponName.Contains("Sniper"))
	{
		CallBPAudioManagerSFX2D("SniperReload");
	}

	if (CurrentWeaponName.Contains("Shotgun"))
	{
		CallBPAudioManagerSFX2D("ShotgunReload");
	}

	CanFire = true;
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("CanFire true"));
}

// SFX //

void APlayerMovement::CheckToPlaySFX(const FString& AudioName)
{
	CallBPAudioManagerCheckIfCurrentSFXIsPlaying(AudioName, CallBPAudioManagerCheckIfCurrentSFXIsPlayingFunctionBool);

	if (CallBPAudioManagerCheckIfCurrentSFXIsPlayingFunctionBool == false)
	{
		CallBPAudioManagerSFX(AudioName, GetActorLocation());
	}
}

// AUTOMATIC WEAPONS //

void APlayerMovement::PistolShoot()
{
	if (isCrouching)
	{
		if (APawn::GetVelocity().X == 0 && APawn::GetVelocity().Y == 0 && APawn::GetVelocity().Z == 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("NOT MOVING AND CROUCHING, PISTOL ONLY CAN CHARGE SHOOT"));
			CallVFXChargeShot();
			GetWorld()->GetTimerManager().SetTimer(ChargePistolShootTimer, this, &APlayerMovement::ChargePistolShot, PlayerFireRate * 2, true);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("MOVING AND CROUCHING, PISTOL CAN NOT SHOOT"));
		}
	}
	else
	{

		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("NOT CROUCHING, PISTOL CAN ONLY SHOOT NORMAL SHOT"));
		NormalPistolShot();
	}
}

void APlayerMovement::ChargePistolShot()
{
	if (PlayerMagSize > 0)
	{
		PlayerMagSize--;
	}
	else if (PlayerMagSize <= 0)
	{
		CallBPAudioManagerSFX2D("OutOfAmmoSFX");
		return;
	}

	if (isCrouching == false)
	{
		GetWorld()->GetTimerManager().ClearTimer(ChargePistolShootTimer);
		GetWorld()->GetTimerManager().SetTimer(NormalPistolShootTimer, this, &APlayerMovement::NormalPistolShot, PlayerFireRate, true);
		return;
	}

	isShootingPistol = true;

	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("CHARGE PISTOL SHOT FUNC CALLED"));

	CastWithRecoil();

	CallBPAudioManagerSFX2D("ChargePistolShoot");

	RemoveBulletFromAmmoBoxes(TEXT("Pistol"));

	SetAmmoInBulletPlayerBlueprint();

	VisualFXShooting();

	GetWorld()->GetTimerManager().SetTimer(ChargePistolShootTimer, this, &APlayerMovement::ChargePistolShot, PlayerFireRate * 2, true);
}

void APlayerMovement::NormalPistolShot()
{
	if (PlayerMagSize > 0)
	{
		PlayerMagSize--;
	}
	else if (PlayerMagSize <= 0)
	{
		CallBPAudioManagerSFX2D("OutOfAmmoSFX");
		return;
	}

	if (isCrouching)
	{
		GetWorld()->GetTimerManager().ClearTimer(NormalPistolShootTimer);
		GetWorld()->GetTimerManager().SetTimer(ChargePistolShootTimer, this, &APlayerMovement::ChargePistolShot, PlayerFireRate * 2, true);
		return;
	}

	isShootingPistol = true;

	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("NORMAL PISTOL SHOT FUNC CALLED"));

	CastWithRecoil();

	CallBPAudioManagerSFX2D("PistolShoot");

	RemoveBulletFromAmmoBoxes(TEXT("Pistol"));

	SetAmmoInBulletPlayerBlueprint();

	VisualFXShooting();

	GetWorld()->GetTimerManager().SetTimer(NormalPistolShootTimer, this, &APlayerMovement::NormalPistolShot, PlayerFireRate, true);
}

void APlayerMovement::RifleShoot()
{
	if (PlayerMagSize > 0)
	{
		PlayerMagSize--;
	}
	else if (PlayerMagSize <= 0)
	{
		CallBPAudioManagerSFX2D("OutOfAmmoSFX");
		return;
	}

	isShootingRifle = true;
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("RIFLE SHOOT"));

	CastWithRecoil();

	CallBPAudioManagerSFX2D("AssaultRifleShoot");

	RemoveBulletFromAmmoBoxes(TEXT("Rifle"));

	SetAmmoInBulletPlayerBlueprint();

	VisualFXShooting();

	GetWorld()->GetTimerManager().SetTimer(RifleShootTimer, this, &APlayerMovement::RifleShoot, PlayerFireRate, true);
}

// SINGLE SHOT WEAPONS //

void APlayerMovement::SniperShoot()
{
	if (PlayerMagSize > 0)
	{
		PlayerMagSize--;
		CanFire = false;
	}
	else if (PlayerMagSize <= 0)
	{
		CallBPAudioManagerSFX2D("OutOfAmmoSFX");
		return;
	}

	isShootingRifle = true;
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("SNIPER SHOOT"));

	CastWithRecoil();

	CallBPAudioManagerSFX2D("SniperShoot");

	RemoveBulletFromAmmoBoxes(TEXT("Sniper"));

	SetAmmoInBulletPlayerBlueprint();

	VisualFXShooting();

	EnableFireTime = PlayerFireRate;

	if (isScoped)
	{
		HideBPADS();
	}

	GetWorld()->GetTimerManager().SetTimer(OneShotTimer, this, &APlayerMovement::EnableFire, EnableFireTime, false);
}

void APlayerMovement::ShotgunShoot()
{
	if (PlayerMagSize > 0)
	{
		PlayerMagSize--;
		CanFire = false;
	}
	else if (PlayerMagSize <= 0)
	{
		CallBPAudioManagerSFX2D("OutOfAmmoSFX");
		return;
	}

	isShootingRifle = true;
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("SHOTGUN SHOOT"));

	CastWithRecoilAndDamageFalloff();
	CastWithRecoilAndDamageFalloff();
	CastWithRecoilAndDamageFalloff();
	CastWithRecoilAndDamageFalloff();
	CastWithRecoilAndDamageFalloff();
	CastWithRecoilAndDamageFalloff();
	CastWithRecoilAndDamageFalloff();
	CastWithRecoilAndDamageFalloff();
	CastWithRecoilAndDamageFalloff();

	CallBPAudioManagerSFX2D("ShotgunShoot");

	RemoveBulletFromAmmoBoxes(TEXT("Shotgun"));

	SetAmmoInBulletPlayerBlueprint();

	VisualFXShooting();

	EnableFireTime = PlayerFireRate;

	GetWorld()->GetTimerManager().SetTimer(OneShotTimer, this, &APlayerMovement::EnableFire, EnableFireTime, false);
}

void APlayerMovement::CastWithRecoil()
{
	TurnOnLight();
	FHitResult* Hit = new FHitResult();
	if (UWorld* World = GetWorld())
	{
		PlayerCamera = World->GetFirstPlayerController()->PlayerCameraManager;
	}

	FVector StartCast = PlayerCamera->GetCameraLocation();
	FVector Forward = PlayerCamera->GetActorForwardVector();

	Forward.X += FMath::RandRange(-PlayerRecoil, PlayerRecoil);
	Forward.Y += FMath::RandRange(-PlayerRecoil, PlayerRecoil);

	FVector EndCast = (Forward * PlayerRange) + StartCast;
	FCollisionQueryParams* col = new FCollisionQueryParams();

	col->AddIgnoredActors(ActorsToIgnoreRaycast);
	col->AddIgnoredComponents(ComponentsToIgnoreRaycast);

	if (GetWorld()->LineTraceSingleByChannel(*Hit, StartCast, EndCast, ECC_Visibility, *col))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("SHOT"));
		//DrawDebugLine(GetWorld(), StartCast, EndCast, FColor(255, 0, 0), true);

		if (Hit->GetActor() != NULL)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Hit Something"));

			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, GetNameSafe(Hit->GetActor()));

			CheckInterface(Hit->GetActor());
		}
	}

	ApplyBulletHole(Hit->Location, Hit->ImpactNormal, Hit->GetComponent());

	CamShake();
	MoveWeapon();
	GetWorld()->GetTimerManager().SetTimer(LightTimer, this, &APlayerMovement::TurnOffLight, 0.2f, false);
}

void APlayerMovement::CastWithRecoilAndDamageFalloff()
{
	TurnOnLight();
	FHitResult* Hit = new FHitResult();
	if (UWorld* World = GetWorld())
	{
		PlayerCamera = World->GetFirstPlayerController()->PlayerCameraManager;
	}

	FVector StartCast = PlayerCamera->GetCameraLocation();
	FVector Forward = PlayerCamera->GetActorForwardVector();

	Forward.X += FMath::RandRange(-PlayerRecoil, PlayerRecoil);
	Forward.Y += FMath::RandRange(-PlayerRecoil, PlayerRecoil);

	FVector EndCast = (Forward * PlayerRange) + StartCast;
	FCollisionQueryParams* col = new FCollisionQueryParams();

	col->AddIgnoredActors(ActorsToIgnoreRaycast);

	if (GetWorld()->LineTraceSingleByChannel(*Hit, StartCast, EndCast, ECC_Visibility, *col))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("SHOT"));
		//DrawDebugLine(GetWorld(), StartCast, EndCast, FColor(255, 0, 0), true);

		if (Hit->GetActor() != NULL && Hit->GetActor()->GetName().Contains("AI"))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Hit Something"));

			CheckInterfaceWithDamageFalloff(Hit->GetActor());
		}
	}

	ApplyBulletHole(Hit->Location, Hit->ImpactNormal, Hit->GetComponent());

	CamShake();
	MoveWeapon();
	GetWorld()->GetTimerManager().SetTimer(LightTimer, this, &APlayerMovement::TurnOffLight, 0.2f, false);
}

void APlayerMovement::CastNoRecoil()
{
	FHitResult* Hit = new FHitResult();
	if (UWorld* World = GetWorld())
	{
		PlayerCamera = World->GetFirstPlayerController()->PlayerCameraManager;
	}

	FVector StartCast = PlayerCamera->GetCameraLocation();
	FVector Forward = PlayerCamera->GetActorForwardVector();

	FVector EndCast = (Forward * MeleeRange) + StartCast;
	FCollisionQueryParams* col = new FCollisionQueryParams();

	if (GetWorld()->LineTraceSingleByChannel(*Hit, StartCast, EndCast, ECC_Visibility, *col))
	{
		DrawDebugLine(GetWorld(), StartCast, EndCast, FColor(255, 0, 0), true);

		if (Hit->GetActor() != NULL && Hit->GetActor()->GetName().Contains("AI"))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Hit Something"));

			CheckInterface(Hit->GetActor());
		}
	}

	ApplyBulletHole(Hit->Location, Hit->ImpactNormal, Hit->GetComponent());
}

void APlayerMovement::CastNoRecoilSpread()
{
	FHitResult* Hit = new FHitResult();
	if (UWorld* World = GetWorld())
	{
		PlayerCamera = World->GetFirstPlayerController()->PlayerCameraManager;
	}

	FVector StartCast = PlayerCamera->GetCameraLocation();
	FVector Forward = PlayerCamera->GetActorForwardVector();

	Forward.X += 1;
	Forward.Y += 1;

	FVector EndCast = (Forward * MeleeRange) + StartCast;
	FCollisionQueryParams* col = new FCollisionQueryParams();

	if (GetWorld()->LineTraceSingleByChannel(*Hit, StartCast, EndCast, ECC_Visibility, *col) && StopMultipleMeleeHits == false)
	{
		DrawDebugLine(GetWorld(), StartCast, EndCast, FColor(255, 0, 0), true);

		if (Hit->GetActor() != NULL && Hit->GetActor()->GetName().Contains("AI"))
		{
			//StopMultipleMeleeHits = true;
			//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Hit Something"));

			CheckInterface(Hit->GetActor());
		}
	}

	ApplyBulletHole(Hit->Location, Hit->ImpactNormal, Hit->GetComponent());

	///////////

	FHitResult* Hit2 = new FHitResult();
	if (UWorld* World = GetWorld())
	{
		PlayerCamera = World->GetFirstPlayerController()->PlayerCameraManager;
	}

	FVector StartCast2 = PlayerCamera->GetCameraLocation();
	FVector Forward2 = PlayerCamera->GetActorForwardVector();

	Forward2.X -= 1;
	Forward2.Y -= 1;

	FVector EndCast2 = (Forward2 * MeleeRange) + StartCast2;
	FCollisionQueryParams* col2 = new FCollisionQueryParams();

	if (GetWorld()->LineTraceSingleByChannel(*Hit2, StartCast2, EndCast2, ECC_Visibility, *col2) && StopMultipleMeleeHits == false)
	{
		DrawDebugLine(GetWorld(), StartCast2, EndCast2, FColor(255, 0, 0), true);

		if (Hit2->GetActor() != NULL && Hit2->GetActor()->GetName().Contains("AI"))
		{
			//StopMultipleMeleeHits = true;
			//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Hit Something"));

			CheckInterface(Hit2->GetActor());
		}
	}

	ApplyBulletHole(Hit->Location, Hit->ImpactNormal, Hit->GetComponent());

	///////////////

	FHitResult* Hit3 = new FHitResult();
	if (UWorld* World = GetWorld())
	{
		PlayerCamera = World->GetFirstPlayerController()->PlayerCameraManager;
	}

	FVector StartCast3 = PlayerCamera->GetCameraLocation();
	FVector Forward3 = PlayerCamera->GetActorForwardVector();

	FVector EndCast3 = (Forward3 * MeleeRange) + StartCast3;
	FCollisionQueryParams* col3 = new FCollisionQueryParams();

	if (GetWorld()->LineTraceSingleByChannel(*Hit3, StartCast3, EndCast3, ECC_Visibility, *col3) && StopMultipleMeleeHits == false)
	{
		DrawDebugLine(GetWorld(), StartCast3, EndCast3, FColor(255, 0, 0), true);

		if (Hit3->GetActor() != NULL && Hit3->GetActor()->GetName().Contains("AI"))
		{
			//StopMultipleMeleeHits = true;
			//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Hit Something"));

			CheckInterface(Hit3->GetActor());
		}
	}

	ApplyBulletHole(Hit->Location, Hit->ImpactNormal, Hit->GetComponent());

	///////////////

	FHitResult* Hit4 = new FHitResult();
	if (UWorld* World = GetWorld())
	{
		PlayerCamera = World->GetFirstPlayerController()->PlayerCameraManager;
	}

	FVector StartCast4 = PlayerCamera->GetCameraLocation();
	FVector Forward4 = PlayerCamera->GetActorForwardVector();

	Forward4.Z -= 1;

	FVector EndCast4 = (Forward4 * MeleeRange) + StartCast4;
	FCollisionQueryParams* col4 = new FCollisionQueryParams();

	if (GetWorld()->LineTraceSingleByChannel(*Hit4, StartCast4, EndCast4, ECC_Visibility, *col4) && StopMultipleMeleeHits == false)
	{
		DrawDebugLine(GetWorld(), StartCast4, EndCast4, FColor(255, 0, 0), true);

		if (Hit4->GetActor() != NULL && Hit4->GetActor()->GetName().Contains("AI"))
		{
			//StopMultipleMeleeHits = true;
			//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Hit Something"));

			CheckInterface(Hit4->GetActor());
		}
	}

	ApplyBulletHole(Hit->Location, Hit->ImpactNormal, Hit->GetComponent());

	///////////////

	FHitResult* Hit5 = new FHitResult();
	if (UWorld* World = GetWorld())
	{
		PlayerCamera = World->GetFirstPlayerController()->PlayerCameraManager;
	}

	FVector StartCast5 = PlayerCamera->GetCameraLocation();
	FVector Forward5 = PlayerCamera->GetActorForwardVector();

	Forward5.Z += 1;

	FVector EndCast5 = (Forward5 * MeleeRange) + StartCast5;
	FCollisionQueryParams* col5 = new FCollisionQueryParams();

	if (GetWorld()->LineTraceSingleByChannel(*Hit5, StartCast5, EndCast5, ECC_Visibility, *col5) && StopMultipleMeleeHits == false)
	{
		DrawDebugLine(GetWorld(), StartCast5, EndCast5, FColor(255, 0, 0), true);

		if (Hit5->GetActor() != NULL)
		{
			//StopMultipleMeleeHits = true;
			//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Hit Something"));

			CheckInterface(Hit5->GetActor());
		}
	}

	ApplyBulletHole(Hit->Location, Hit->ImpactNormal, Hit->GetComponent());
}

// UNARMED FUNCTIONS //

void APlayerMovement::UnarmedMeleeTimerFunc()
{
	CanFire = true;
	CanMelee = true;
	isMeleeing = false;
	StopMultipleMeleeHits = false;
	GetWorld()->GetTimerManager().ClearTimer(UnarmedMeleeTimer);
}

void APlayerMovement::UnarmedMelee()
{
	PlayerDamage = 100;

	CanFire = false;
	CanMelee = false;
	isMeleeing = true;
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("UNARMED MELEE"));

	CastNoRecoilSpread();

	EnableFireTime = 0.5f;

	GetWorld()->GetTimerManager().SetTimer(UnarmedMeleeTimer, this, &APlayerMovement::UnarmedMeleeTimerFunc, EnableFireTime, false);
}

// RELOAD FUNCTIONS //

void APlayerMovement::ReloadTimerFunc()
{
	GetCurrentWeaponName();

	if (CurrentWeaponName.Contains("Shotgun"))
	{
		if (ShotgunAmmo == 0)
		{
			return;
		}
	}

	if (CurrentWeaponName.Contains("Pistol"))
	{
		if (PistolAmmo == 0)
		{
			return;
		}
	}

	if (CurrentWeaponName.Contains("Sniper"))
	{
		if (SniperAmmo == 0)
		{
			return;
		}
	}

	if (CurrentWeaponName.Contains("Rifle"))
	{
		if (AssaultRifleAmmo == 0)
		{
			return;
		}
	}

	if (GetWorldTimerManager().IsTimerActive(ReloadTimer) == false && Dead == false && Paused == false && CurrentWeaponName.Contains("Ammo") == false && CurrentWeaponName != "")
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("ReloadTimerFunc"));

		CanFire = false;
		isShootingRifle = false;
		isShootingPistol = false;
		ResetWeaponLocation();
		GetWorld()->GetTimerManager().ClearTimer(ChargePistolShootTimer);
		GetWorld()->GetTimerManager().ClearTimer(NormalPistolShootTimer);
		GetWorld()->GetTimerManager().ClearTimer(RifleShootTimer);

		EnableFireTime = PlayerReloadTime;

		GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &APlayerMovement::Reload, EnableFireTime, false);
	}
}

void APlayerMovement::Reload()
{
	// Get the current weapon name
	GetCurrentWeaponName();

	// If no weapon is equipped, return
	if (CurrentWeaponName.IsEmpty())
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("No weapon equipped!"));
		return;
	}

	// Determine which weapon is being reloaded
	if (CurrentWeaponName.Contains("Shotgun"))
	{
		// Reload shotgun
		CallBPAudioManagerSFX2D("ShotgunReload");

		if (ShotgunAmmo > 0)
		{
			int16 AmmoToAdd = FMath::Min(OGMagSize - PlayerMagSize, ShotgunAmmo);
			PlayerMagSize += AmmoToAdd;
			ShotgunAmmo -= AmmoToAdd;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("No shotgun ammo!"));
		}
	}
	else if (CurrentWeaponName.Contains("Pistol"))
	{
		// Reload pistol
		CallBPAudioManagerSFX2D("PistolReload");

		if (PistolAmmo > 0)
		{
			int16 AmmoToAdd = FMath::Min(OGMagSize - PlayerMagSize, PistolAmmo);
			PlayerMagSize += AmmoToAdd;
			PistolAmmo -= AmmoToAdd;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("No pistol ammo!"));
		}
	}
	else if (CurrentWeaponName.Contains("Rifle"))
	{
		// Reload assault rifle
		CallBPAudioManagerSFX2D("AssaultRifleReload");

		if (AssaultRifleAmmo > 0)
		{
			int16 AmmoToAdd = FMath::Min(OGMagSize - PlayerMagSize, AssaultRifleAmmo);
			PlayerMagSize += AmmoToAdd;
			AssaultRifleAmmo -= AmmoToAdd;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("No assault rifle ammo!"));
		}
	}
	else if (CurrentWeaponName.Contains("Sniper"))
	{
		// Reload sniper rifle

		isScoped = false;
		HideBPADS();

		CallBPAudioManagerSFX2D("SniperReload");

		if (SniperAmmo > 0)
		{
			int16 AmmoToAdd = FMath::Min(OGMagSize - PlayerMagSize, SniperAmmo);
			PlayerMagSize += AmmoToAdd;
			SniperAmmo -= AmmoToAdd;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("No sniper ammo!"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("Unknown weapon type!"));
		return;
	}

	// Update UI and set can fire
	CallSetAmmoInBulletPlayerBlueprint();
	UpdatePlayerAmmoOnUI();
	CanFire = true;
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Reloaded!"));
}


// ITEM USE FUNCTIONS //

void APlayerMovement::CallItemUseCPP()
{
	ItemUse();
}

void APlayerMovement::ItemUse()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Item Use Func"));

	LowerInventorySize(1);
	CallOrganiseAmmoInMag(PlayerCurrentInvSlot);

	if (PlayerItemType == "Health")
	{
		HealthFunc();
		return;
	}

	if (PlayerItemType == "Speed")
	{
		SpeedFunc();
		return;
	}

	if (PlayerItemType == "Projectile")
	{
		ThrowProjectile();
		return;
	}
}

void APlayerMovement::ThrowProjectile()
{

	if (UWorld* World = GetWorld())
	{
		PlayerCamera = World->GetFirstPlayerController()->PlayerCameraManager;
	}

	FVector Direction = PlayerCamera->GetActorForwardVector();
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("THROW PROJECTILE"));
	RemoveCurrentItem();

	if (CurrentWeaponName.Contains("A10"))
	{
		ThrowA10Grenade(200000, Direction);
	}

	SelectARandomWeapon();
}

void APlayerMovement::HealthFunc()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Health Func"));

	if (PlayerHealDuration == "Slow")
	{
		JustHealed = true;
		CanFire = false;
		EnableFireTime = 5.0f;
		GetWorld()->GetTimerManager().SetTimer(PlayerHealTimer, this, &APlayerMovement::ApplyHealth, EnableFireTime, false);
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("PlayerHealDuration Slow"));
	}

	if (PlayerHealDuration == "Medium")
	{
		JustHealed = true;
		CanFire = false;
		EnableFireTime = 3.5f;
		GetWorld()->GetTimerManager().SetTimer(PlayerHealTimer, this, &APlayerMovement::ApplyHealth, EnableFireTime, false);
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("PlayerHealDuration Medium"));
	}

	if (PlayerHealDuration == "Fast")
	{
		JustHealed = true;
		CanFire = false;
		EnableFireTime = 1.0f;
		GetWorld()->GetTimerManager().SetTimer(PlayerHealTimer, this, &APlayerMovement::ApplyHealth, EnableFireTime, false);
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("PlayerHealDuration Fast"));
	}

	if (PlayerHealDuration == "Instant")
	{
		JustHealed = true;
		ApplyHealth();
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("PlayerHealDuration Instant"));
	}
}

void APlayerMovement::ApplyHealth()
{
	CanFire = true;

	JustHealed = false;

	if (PlayerHealIntensity == "Low")
	{
		if (PlayerHealth > 100)
		{
			PlayerHealth = 100;
			CallPlayerUIPopupText("Health Is Already Full", 5.0f);
		}
		else
		{
			PlayerHealth += 20;
			if (PlayerHealth > 100)
			{
				PlayerHealth = 100;
			}
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("PlayerHealIntensity Low"));
		}
	}

	if (PlayerHealIntensity == "Medium")
	{
		if (PlayerHealth > 100)
		{
			PlayerHealth = 100;
			CallPlayerUIPopupText("Health Is Already Full", 5.0f);
		}
		else
		{
			PlayerHealth += 40;
			if (PlayerHealth > 100)
			{
				PlayerHealth = 100;
			}

			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("PlayerHealIntensity Medium"));
		}
	}

	if (PlayerHealIntensity == "High")
	{
		if (PlayerHealth > 100)
		{
			PlayerHealth = 100;
			CallPlayerUIPopupText("Health Is Already Full", 5.0f);
		}
		else
		{
			PlayerHealth += 60;
			if (PlayerHealth > 100)
			{
				PlayerHealth = 100;
			}
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("PlayerHealIntensity High"));
		}
	}

	if (PlayerHealIntensity == "FullHeal")
	{
		if (PlayerHealth >= 100)
		{
			CallPlayerUIPopupText("Health Is Already Full", 5.0f);
		}
		else
		{
			PlayerHealth = 100;

			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("PlayerHealIntensity FullHeal"));
		}
	}

	CallPlayerUISetHealthText(PlayerHealth);

	RemoveCurrentItem();

	CallClearEquippedItemTextUI();

	SelectARandomWeapon();
}

void APlayerMovement::SpeedFunc()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Speed Func"));
	if (PlayerSpeedBoostIntensity == "Low")
	{
		JustUsedSpeedPack = true;
		GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;
		GetCharacterMovement()->MaxWalkSpeed += LowSpeedIncrease;
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("PlayerSpeedBoostIntensity Low"));
	}

	if (PlayerSpeedBoostIntensity == "Medium")
	{
		JustUsedSpeedPack = true;
		GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;
		GetCharacterMovement()->MaxWalkSpeed += MediumSpeedIncrease;
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("PlayerSpeedBoostIntensity Medium"));
	}

	if (PlayerSpeedBoostIntensity == "High")
	{
		JustUsedSpeedPack = true;
		GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;
		GetCharacterMovement()->MaxWalkSpeed += HighSpeedIncrease;
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("PlayerSpeedBoostIntensity High"));
	}

	if (PlayerSpeedBoostDuration == "Slow")
	{
		JustUsedSpeedPack = true;
		CanFire = false;
		EnableFireTime = 5.0f;
		GetWorld()->GetTimerManager().SetTimer(PlayerSpeedTimer, this, &APlayerMovement::ResetSpeed, EnableFireTime, false);
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("PlayerSpeedBoostDuration Slow"));
	}

	if (PlayerSpeedBoostDuration == "Medium")
	{
		JustUsedSpeedPack = true;
		CanFire = false;
		EnableFireTime = 3.5f;
		GetWorld()->GetTimerManager().SetTimer(PlayerSpeedTimer, this, &APlayerMovement::ResetSpeed, EnableFireTime, false);
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("PlayerSpeedBoostDuration Medium"));
	}

	if (PlayerSpeedBoostDuration == "Fast")
	{
		JustUsedSpeedPack = true;
		CanFire = false;
		EnableFireTime = 1.0f;
		GetWorld()->GetTimerManager().SetTimer(PlayerSpeedTimer, this, &APlayerMovement::ResetSpeed, EnableFireTime, false);
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("PlayerSpeedBoostDuration Fast"));
	}

	CallFOVIncrease();

	RemoveCurrentItem();

	CallClearEquippedItemTextUI();
}

void APlayerMovement::ResetSpeed()
{
	JustUsedSpeedPack = false;
	CanFire = true;
	GetCharacterMovement()->MaxWalkSpeed = 300;
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("ResetSpeed"));

	CallFOVDecrease();
	SelectARandomWeapon();
}

// CLEAR TIMERS //

void APlayerMovement::ClearTimers()
{
	// AVOID REPEATING MELEE ANIMATIONS //
	if (isMeleeing)
	{
		CanFire = true;
		CanMelee = true;
		isMeleeing = false;
	}
	////
	GetWorld()->GetTimerManager().ClearTimer(RifleShootTimer);
	GetWorld()->GetTimerManager().ClearTimer(OneShotTimer);
	GetWorld()->GetTimerManager().ClearTimer(NormalPistolShootTimer);
	GetWorld()->GetTimerManager().ClearTimer(ChargePistolShootTimer);
	GetWorld()->GetTimerManager().ClearTimer(LightTimer);
	GetWorld()->GetTimerManager().ClearTimer(ReloadTimer);
	GetWorld()->GetTimerManager().ClearTimer(UnarmedMeleeTimer);
	GetWorld()->GetTimerManager().ClearTimer(PlayerHealTimer);
	GetWorld()->GetTimerManager().ClearTimer(PlayerSpeedTimer);
	//GetWorld()->GetTimerManager().ClearTimer(EquipTimer);
}