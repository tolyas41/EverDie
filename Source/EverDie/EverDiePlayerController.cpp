// game made by Anatoly Novikov


#include "EverDiePlayerController.h"
#include "EverDiePlayer.h"
#include "GameFramework/PlayerInput.h"

//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *RotateToLocation.ToString()));

AEverDiePlayerController::AEverDiePlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	PrimaryActorTick.bCanEverTick = true;
}

void AEverDiePlayerController::BeginPlay()
{
	Super::BeginPlay();
	ControlledPlayer = Cast<AEverDiePlayer>(GetPawn());
	if (ControlledPlayer)
	{
		ControlledPlayer->OnStaminaNull.AddUFunction(this, FName("ResetSprintModifier"));
	}
}

void AEverDiePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CursorPressed)
	{
		FHitResult CursorHit;
		GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
		RotateToLocation = CursorHit.Location - ControlledPlayer->GetActorLocation();
		RotateToLocation.Normalize();

		float angle = FMath::Atan2(RotateToLocation.X, RotateToLocation.Z);
		CheckAttackDirection(angle);
		AttackDirection = AnimDirections::None;

		if (MovementSpeedModifier == 1.f)
		{
			MovementSpeedModifier = ControlledPlayer->GetWeaponMovementSlowing();
			GetWorldTimerManager().SetTimer(TH_SlowMovementOnAttack, this, &AEverDiePlayerController::AttackSlowRestore, 1.0f);
		}
	}
	if (isMovingRightLeft || isMovingUpDown)
	{
		MovementAnimation(MoveDirection);
	}
	if (!isMovingRightLeft && !isMovingUpDown)
	{
		IdleAnimation();
	}
}

void AEverDiePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Attack", IE_Pressed, this, &AEverDiePlayerController::RotateToCursorPressed);
	InputComponent->BindAction("Attack", IE_Released, this, &AEverDiePlayerController::RotateToCursorReleased);
	InputComponent->BindAction("Sprint", IE_Pressed, this, &AEverDiePlayerController::SprintModeOn);
	InputComponent->BindAction("Sprint", IE_Released, this, &AEverDiePlayerController::SprintModeOff);
	InputComponent->BindAxis("MoveRight", this, &AEverDiePlayerController::MoveRight);
	InputComponent->BindAxis("MoveUp", this, &AEverDiePlayerController::MoveUp);
}


void AEverDiePlayerController::RotateToCursorPressed()
{
	CursorPressed = true;
}

void AEverDiePlayerController::RotateToCursorReleased()
{
	CursorPressed = false;
}

void AEverDiePlayerController::MoveRight(float value)
{
	if (value != 0)
	{
		MoveDirection = (value > 0) ? AnimDirections::Right : AnimDirections::Left;
		ControlledPlayer->AddActorWorldOffset(FVector(1.f, 0.f, 0.f) * value * MovementSpeed * MovementSpeedModifier * SprintModifier);
		isMovingRightLeft = true;
	}
	else isMovingRightLeft = false;
}

void AEverDiePlayerController::MoveUp(float value)
{
	if (value != 0)
	{
		MoveDirection = (value > 0) ? AnimDirections::Up : AnimDirections::Down;
		ControlledPlayer->AddActorWorldOffset(FVector(0.f, 0.f, 1.f) * value * MovementSpeed * MovementSpeedModifier * SprintModifier);
		isMovingUpDown = true;
	}
	else isMovingUpDown = false;
}

void AEverDiePlayerController::SprintModeOn()
{
	SprintModifier = ControlledPlayer->GetSprintPower();
	ControlledPlayer->StartStaminaDrain();
}

void AEverDiePlayerController::SprintModeOff()
{
	ResetSprintModifier();
	ControlledPlayer->StartStaminaRestore();
}

void AEverDiePlayerController::ResetSprintModifier()
{
	SprintModifier = 1.f;

}

void AEverDiePlayerController::CheckAttackDirection(float angle)
{
	if (angle > -0.8f && angle < 0.8f)
	{
		if (AttackDirection != AnimDirections::Up)
		{
			AttackDirection = AnimDirections::Up;
		}
	}
	if (angle > 0.8f && angle < 2.4f)
	{
		if (AttackDirection != AnimDirections::Right)
		{
			AttackDirection = AnimDirections::Right;
		}
	}
	if (angle > 2.4f || angle < -2.4f)
	{
		if (AttackDirection != AnimDirections::Down)
		{
			AttackDirection = AnimDirections::Down;
		}
	}
	if (angle > -2.4 && angle < -0.8f)
	{
		if (AttackDirection != AnimDirections::Left)
		{
			AttackDirection = AnimDirections::Left;
		}
	}
	AttackAction(AttackDirection);
}

void AEverDiePlayerController::AttackSlowRestore()
{
	MovementSpeedModifier = 1.f;
}
