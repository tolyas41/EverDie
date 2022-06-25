// game made by Anatoly Novikov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EverDiePlayerController.generated.h"

class AEverDiePlayer;

UENUM()
enum AnimDirections
{
	Left	UMETA(DisplayName = "Left"),
	Up		UMETA(DisplayName = "Up"),
	Right	UMETA(DisplayName = "Right"),
	Down	UMETA(DisplayName = "Down"),
	None	UMETA(DisplayName = "None")
};


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

	void RotateToCursorPressed();
	void RotateToCursorReleased();
	void MoveRight(float value);
	void MoveUp(float value);
	void SprintModeOn();
	void SprintModeOff();


	FVector RotateToLocation;
	float MovementSpeed = 3.f;
	float MovementSpeedModifier = 1.f;
	float SprintModifier = 1.f;
	bool CursorPressed = false;
	bool isMovingRightLeft = false;
	bool isMovingUpDown = false;
	FTimerHandle TH_SlowMovementOnAttack;

	void AttackSlowRestore();
	UFUNCTION(BlueprintImplementableEvent)
	void AttackAction(AnimDirections direction);
	UFUNCTION(BlueprintImplementableEvent)
	void MovementAnimation(AnimDirections direction);
	UFUNCTION(BlueprintImplementableEvent)
	void IdleAnimation();

	void CheckAttackDirection(float angle);
	AnimDirections AttackDirection;
	AnimDirections MoveDirection;
};
