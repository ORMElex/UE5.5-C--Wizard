// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "EnemyBot.h"

AEnemyAIController::AEnemyAIController()
{
	Bot_PC = CreateDefaultSubobject<UEnemyAIPerceptionComponent>("EnemyPerceptionController");
	SetPerceptionComponent(*Bot_PC);
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto EnemyCharacter = Cast<AEnemyBot>(InPawn);
	if (EnemyCharacter)
	{
		RunBehaviorTree(EnemyCharacter->BehaviorTreeAsset);
	}
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AActor* Enemy = Bot_PC->GetClosestEnemyInView();
	SetFocus(Enemy);
}