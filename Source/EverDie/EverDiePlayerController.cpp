// game made by Anatoly Novikov


#include "EverDiePlayerController.h"
#include "EverDiePlayer.h"
#include "GameFramework/PlayerInput.h"

//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *MoveToLocation.ToString()));

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
}

void AEverDiePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CursorPressed)
	{
		FHitResult CursorHit;
		GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
		MoveToLocation = CursorHit.Location - ControlledPlayer->GetActorLocation();
		MoveToLocation.Y = 0;
		MoveToLocation.Normalize();

		ControlledPlayer->AddActorWorldOffset(MoveToLocation * MovementSpeed);
		float angle = FMath::Atan2(MoveToLocation.X, MoveToLocation.Z);
		CheckCharDirection(angle);
		CharDirection = CharDirections::None;
	}
}

void AEverDiePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("MoveTo", IE_Pressed, this, &AEverDiePlayerController::MoveToCursorPressed);
	InputComponent->BindAction("MoveTo", IE_Released, this, &AEverDiePlayerController::MoveToCursorReleased);
	InputComponent->BindAction("Action", IE_Pressed, this, &AEverDiePlayerController::SomeTestAction);
}


void AEverDiePlayerController::MoveToCursorPressed()
{
	CursorPressed = true;
}

void AEverDiePlayerController::MoveToCursorReleased()
{
	CursorPressed = false;
	SwitchIdleAnim();
}

void AEverDiePlayerController::CheckCharDirection(float angle)
{
	if (angle > -0.8f && angle < 0.8f)
	{
		if (CharDirection != CharDirections::Up)
		{
			CharDirection = CharDirections::Up;
			SwitchMovementAnim(CharDirection);
		}
	}
	if (angle > 0.8f && angle < 2.4f)
	{
		if (CharDirection != CharDirections::Right)
		{
			CharDirection = CharDirections::Right;
			SwitchMovementAnim(CharDirection);
		}
	}
	if (angle > 2.4f || angle < -2.4f)
	{
		if (CharDirection != CharDirections::Down)
		{
			CharDirection = CharDirections::Down;
			SwitchMovementAnim(CharDirection);
		}
	}
	if (angle > -2.4 && angle < -0.8f)
	{
		if (CharDirection != CharDirections::Left)
		{
			CharDirection = CharDirections::Left;
			SwitchMovementAnim(CharDirection);
		}
	}

}

void AEverDiePlayerController::SomeTestAction()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *ControlledPlayer->GetName()));
}