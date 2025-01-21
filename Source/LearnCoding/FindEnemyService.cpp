// Fill out your copyright notice in the Description page of Project Settings.


#include "FindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "EnemyAIPerceptionComponent.h"


UFindEnemyService::UFindEnemyService()
{
	NodeName = "Find Enemy";
}

void UFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		const auto AiController = OwnerComp.GetAIOwner();
		const auto PercepComp = AiController->FindComponentByClass<UEnemyAIPerceptionComponent>();
		if (PercepComp)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PercepComp->GetClosestEnemyInView());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}