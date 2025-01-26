// Fill out your copyright notice in the Description page of Project Settings.


#include "AIWeaponComponent.h"
#include "Wand.h"


UAIWeaponComponent::UAIWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UAIWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAIWeaponComponent::Attack(AActor* Enemy)
{
	if (!SpawnedWand) return;
	bisAttacking = true;
	SpawnedWand->Attack(Enemy);
}

void UAIWeaponComponent::AttackStop()
{
	if (!SpawnedWand) return;
	bisAttacking = false;
	//SpawnedWand->AttackStop();
}