// game made by Anatoly Novikov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EverDiePlayerController.generated.h"

class AEverDiePlayer;

UCLASS()
class EVERDIE_API AEverDiePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	AEverDiePlayerController(const FObjectInitializer& ObjectInitializer);
	void BeginPlay();
	void Tick(float DeltaTime);
	virtual void SetupInputComponent();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayerAction_MoveTo();
	UPROPERTY(BlueprintReadWrite)
	AEverDiePlayer *ControlledPlayer;

	void SomeTestAction(); //TEST
	void MoveToCursorPressed();
	void MoveToCursorReleased();

	FVector MoveToLocation;
	float MovementSpeed = 3.f;
	bool CursorPressed = false;
};
