// game made by Anatoly Novikov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class AEverDiePlayer;

UCLASS()
class EVERDIE_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseWeapon();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void Attack();
	UFUNCTION(BlueprintImplementableEvent)
	void SpecialAttack();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Ammo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float ProjectileSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	AEverDiePlayer *OwningPlayer;


};
