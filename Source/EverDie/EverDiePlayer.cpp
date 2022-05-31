// game made by Anatoly Novikov


#include "EverDiePlayer.h"
#include "BaseWeapon.h"

AEverDiePlayer::AEverDiePlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	
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


