// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "EnemyBot.h"
#include "BehaviorTree/BlackboardComponent.h"

AEnemyAIController::AEnemyAIController()
{
	Bot_PC = CreateDefaultSubobject<UEnemyAIPerceptionComponent>("EnemyPerceptionController");
	SetPerceptionComponent(*Bot_PC);
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto BotCharacter = Cast<AEnemyBot>(InPawn);
	if (BotCharacter)
	{
		RunBehaviorTree(BotCharacter->BehaviorTreeAsset);
	}
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AActor* Enemy = GetFocusOnActor();
	SetFocus(Enemy);
}

AActor* AEnemyAIController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}