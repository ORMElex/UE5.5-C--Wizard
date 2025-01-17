// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIPerceptionComponent.h"

AActor* UEnemyAIPerceptionComponent::GetClosestEnemyInView()
{
	TArray<AActor*> SeenActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), SeenActors);
	if (SeenActors.Num() == 0) return nullptr;

	const auto BotController = Cast<AAIController>(GetOwner());
	if (!BotController) return nullptr;

	const APawn* Pawn = BotController->GetPawn();
	if (!Pawn) return nullptr;

	float ClosestDistance = MAX_FLT;
	AActor* ClosestPawn = nullptr;

	for (auto SeenActor : SeenActors)
	{
		UHealthComponent* ActorHealthComponent = SeenActor->FindComponentByClass<UHealthComponent>();
		if (ActorHealthComponent && !ActorHealthComponent->isDead())
		{
			auto DistanceToEnemy = (SeenActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (ClosestDistance > DistanceToEnemy)
			{
				ClosestDistance = DistanceToEnemy;
				ClosestPawn = SeenActor;
			}
		}
	}
	return ClosestPawn;
}