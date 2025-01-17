// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "AIController.h"
#include "HealthComponent.h"
#include "Perception/AISense_Sight.h"

#include "EnemyAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class LEARNCODING_API UEnemyAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
	
public:
	AActor* GetClosestEnemyInView();
};
