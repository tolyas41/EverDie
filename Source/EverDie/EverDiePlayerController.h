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

	void SomeTestAction(); //TEST
	void RotateToCursorPressed();
	void RotateToCursorReleased();
	void MoveRight(float value);
	void MoveUp(float value);

	FVector RotateToLocation;
	float MovementSpeed = 3.f;
	bool CursorPressed = false;
	bool isMoving = false;

	UFUNCTION(BlueprintImplementableEvent)
	void AttackAction(AnimDirections direction);
	UFUNCTION(BlueprintImplementableEvent)
	void MovementAction(AnimDirections direction);

	void CheckAttackDirection(float angle);
	AnimDirections AttackDirection;
	AnimDirections MoveDirection;
};
