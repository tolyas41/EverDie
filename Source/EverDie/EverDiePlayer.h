// game made by Anatoly Novikov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EverDiePlayer.generated.h"

UCLASS()
class EVERDIE_API AEverDiePlayer : public APawn
{
	GENERATED_BODY()

public:
	AEverDiePlayer();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintPower = 1.3f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxStamina = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StaminaDrainRate = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StaminaRestoreRate = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StaminaRestoreDelay = 1.5f;
	UPROPERTY(BlueprintReadWrite)
	float CurrentStamina;

	FTimerHandle TH_StartStaminaRestore;
	void StaminaRestore();
	FTimerHandle TH_StartStaminaDrain;
	void StaminaDrain();
	UFUNCTION(BlueprintImplementableEvent)
	void OnStaminaChange();

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	class ABaseWeapon* EquippedWeapon;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	float GetWeaponMovementSlowing();
	float GetSprintPower();
	void StartStaminaDrain();
	void StartStaminaRestore();
};
