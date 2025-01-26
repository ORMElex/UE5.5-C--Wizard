// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponComponent.h"
#include "AIWeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class LEARNCODING_API UAIWeaponComponent : public UWeaponComponent
{
	GENERATED_BODY()

public:
	UAIWeaponComponent();

	void Attack(AActor* Enemy);
	void AttackStop();
	
protected:
	virtual void BeginPlay() override;
};
