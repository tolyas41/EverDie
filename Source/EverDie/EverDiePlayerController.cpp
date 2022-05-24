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
}

void AEverDiePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CursorPressed)
	{
		FHitResult CursorHit;
		GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
		RotateToLocation = CursorHit.Location - ControlledPlayer->GetActorLocation();
		//RotateToLocation.Y = 0;
		RotateToLocation.Normalize();

		//ControlledPlayer->AddActorWorldOffset(RotateToLocation * MovementSpeed);
		float angle = FMath::Atan2(RotateToLocation.X, RotateToLocation.Z);
		CheckCharDirection(angle);
		CharDirection = CharDirections::None;
	}
}

void AEverDiePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Attack", IE_Pressed, this, &AEverDiePlayerController::RotateToCursorPressed);
	InputComponent->BindAction("Attack", IE_Released, this, &AEverDiePlayerController::RotateToCursorReleased);
	InputComponent->BindAxis("MoveRight", this, &AEverDiePlayerController::MoveRight);
	InputComponent->BindAxis("MoveDown", this, &AEverDiePlayerController::MoveDown);
	InputComponent->BindAction("Action", IE_Pressed, this, &AEverDiePlayerController::SomeTestAction);
}


void AEverDiePlayerController::RotateToCursorPressed()
{
	CursorPressed = true;
}

void AEverDiePlayerController::RotateToCursorReleased()
{
	CursorPressed = false;
	SwitchIdleAnim();
}

void AEverDiePlayerController::MoveRight(float value)
{
	ControlledPlayer->AddActorWorldOffset(FVector(1.f, 0.f, 0.f) * value * MovementSpeed);
}

void AEverDiePlayerController::MoveDown(float value)
{
	ControlledPlayer->AddActorWorldOffset(FVector(0.f, 0.f, 1.f) * value * MovementSpeed);
}

void AEverDiePlayerController::CheckCharDirection(float angle)
{
	if (angle > -0.8f && angle < 0.8f)
	{
		if (CharDirection != CharDirections::Up)
		{
			CharDirection = CharDirections::Up;
			AttackAction(CharDirection);
		}
	}
	if (angle > 0.8f && angle < 2.4f)
	{
		if (CharDirection != CharDirections::Right)
		{
			CharDirection = CharDirections::Right;
			AttackAction(CharDirection);
		}
	}
	if (angle > 2.4f || angle < -2.4f)
	{
		if (CharDirection != CharDirections::Down)
		{
			CharDirection = CharDirections::Down;
			AttackAction(CharDirection);
		}
	}
	if (angle > -2.4 && angle < -0.8f)
	{
		if (CharDirection != CharDirections::Left)
		{
			CharDirection = CharDirections::Left;
			AttackAction(CharDirection);
		}
	}

}

void AEverDiePlayerController::SomeTestAction()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *ControlledPlayer->GetName()));
}