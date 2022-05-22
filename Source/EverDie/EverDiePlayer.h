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

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
