// game made by Anatoly Novikov


#include "EverDiePlayer.h"
#include "BaseWeapon.h"

AEverDiePlayer::AEverDiePlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CurrentStamina = MaxStamina;
}

void AEverDiePlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEverDiePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEverDiePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AEverDiePlayer::GetWeaponMovementSlowing()
{
	if (EquippedWeapon)
	{
		return EquippedWeapon->MovementSlowing;
	}
	else
	{
		return 1.f;
	}

}

float AEverDiePlayer::GetSprintPower()
{
	return SprintPower;
}

void AEverDiePlayer::StaminaRestore()
{
	if (CurrentStamina < MaxStamina)
	{
		CurrentStamina += StaminaRestoreRate;
		OnStaminaChange();
	}
}

void AEverDiePlayer::StaminaDrain()
{
	if (CurrentStamina > 0)
	{
		CurrentStamina -= StaminaDrainRate;
		OnStaminaChange();
	}
}

void AEverDiePlayer::StartStaminaDrain()
{
	GetWorldTimerManager().ClearTimer(TH_StartStaminaRestore);
	//TH_StartStaminaRestore.Invalidate();
	GetWorldTimerManager().SetTimer(TH_StartStaminaDrain, this, &AEverDiePlayer::StaminaDrain, 0.05f, true);
}

void AEverDiePlayer::StartStaminaRestore()
{
	GetWorldTimerManager().ClearTimer(TH_StartStaminaDrain);
	//TH_StartStaminaDrain.Invalidate();
	GetWorldTimerManager().SetTimer(TH_StartStaminaRestore, this, &AEverDiePlayer::StaminaRestore, 0.05f, true, StaminaRestoreDelay);
}


