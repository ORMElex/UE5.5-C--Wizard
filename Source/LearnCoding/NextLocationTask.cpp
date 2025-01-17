// Fill out your copyright notice in the Description page of Project Settings.


#include "NextLocationTask.h"


UNextLocationTask::UNextLocationTask()
{
	NodeName = "Next Location";
}

EBTNodeResult::Type UNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto BotController = OwnerComp.GetAIOwner();
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();

	if (!BotController || !BlackBoard) return EBTNodeResult::Failed;

	const auto BotPawn = BotController->GetPawn();

	if (!BotPawn) return EBTNodeResult::Failed;

	auto NavSys = UNavigationSystemV1::GetCurrent(BotPawn);
	if (!NavSys) return EBTNodeResult::Failed;

	FNavLocation NavLocation;
	bool isFound = NavSys->GetRandomReachablePointInRadius(BotPawn->GetActorLocation(), RadiusToSeek, NavLocation);
	if (!isFound) return EBTNodeResult::Failed;

	BlackBoard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);

	return EBTNodeResult::Succeeded;
}