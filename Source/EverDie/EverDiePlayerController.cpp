// game made by Anatoly Novikov


#include "EverDiePlayerController.h"
#include "EverDiePlayer.h"
#include "GameFramework/PlayerInput.h"

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

	//SetInputMode(FInputModeGameAndUI());
}

void AEverDiePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *ControlledPlayer->GetName())); //working debug message
	if (CursorPressed)
	{
		FHitResult CursorHit;
		GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
		MoveToLocation = CursorHit.Location - ControlledPlayer->GetActorLocation();
		MoveToLocation.Y = 0;
		//MoveToLocation.X /= MoveToLocation.Size();
		//MoveToLocation.Z /= MoveToLocation.Size();
		MoveToLocation.Normalize();

		ControlledPlayer->AddActorWorldOffset(MoveToLocation * MovementSpeed);
	}
}

void AEverDiePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("Action",
	//	EKeys::SpaceBar));
	InputComponent->BindAction("MoveTo", IE_Pressed, this, &AEverDiePlayerController::MoveToCursorPressed);
	InputComponent->BindAction("MoveTo", IE_Released, this, &AEverDiePlayerController::MoveToCursorReleased);
	//InputComponent->BindAction("MoveTo", IE_Pressed, this, &AEverDiePlayerController::SomeTestAction);
	InputComponent->BindAction("Action", IE_Pressed, this, &AEverDiePlayerController::SomeTestAction);
}


void AEverDiePlayerController::MoveToCursorPressed()
{
	CursorPressed = true;
}

void AEverDiePlayerController::MoveToCursorReleased()
{
	CursorPressed = false;
}

void AEverDiePlayerController::SomeTestAction()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *ControlledPlayer->GetName()));
}