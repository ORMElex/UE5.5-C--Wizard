// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIPerceptionComponent.h"


#include "EnemyAIController.generated.h"


/**
 * 
 */
UCLASS()
class LEARNCODING_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();

protected:
	void OnPossess(APawn* InPawn) override;

	void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UEnemyAIPerceptionComponent* Bot_PC;
};
