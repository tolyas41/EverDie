// game made by Anatoly Novikov

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class EVERDIE_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
};
