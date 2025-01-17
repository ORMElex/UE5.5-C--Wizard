// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "EnemyAttackService.generated.h"

/**
 * 
 */
UCLASS()
class LEARNCODING_API UEnemyAttackService : public UBTService
{
	GENERATED_BODY()

public:
	UEnemyAttackService();

protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;
	
};
