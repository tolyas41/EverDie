// game made by Anatoly Novikov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

UCLASS()
class EVERDIE_API AEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemyManager();

protected:
	virtual void BeginPlay() override;

	//UPROPERTY(EditDefaultsOnly)
	//TSubclassOf<class ABaseEnemy> SpawnEnemyType; 

public:
	virtual void Tick(float DeltaTime) override;

};
