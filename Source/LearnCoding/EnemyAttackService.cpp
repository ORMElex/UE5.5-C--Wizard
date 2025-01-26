// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAttackService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIWeaponComponent.h"

UEnemyAttackService::UEnemyAttackService()
{
	NodeName = "Fire";
}


void UEnemyAttackService::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	const auto BotController = OwnerComp.GetAIOwner();
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();

	const auto HasAim = BlackBoard && BlackBoard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

	if (BotController)
	{
		const auto WeaponComp = BotController->GetPawn()->FindComponentByClass<UAIWeaponComponent>();
		if (WeaponComp && HasAim)
		{
				const auto Enemy = Cast<AActor>(BlackBoard->GetValueAsObject(EnemyActorKey.SelectedKeyName));
				WeaponComp->Attack(Enemy);
		}
		else if (WeaponComp)
		{
			WeaponComp->AttackStop();
		}
	}
	

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}