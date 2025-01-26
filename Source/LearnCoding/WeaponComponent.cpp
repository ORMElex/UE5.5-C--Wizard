// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "Engine/World.h"
#include "Wand.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<ACharacter>(GetOwner());

	SpawnWand();
	
}


void UWeaponComponent::SpawnWand()
{
	if (!GetWorld()) return;

	if (!Character)
	{
		Character = Cast<ACharacter>(GetOwner());
	}
	if (!Character) return;

	SpawnedWand = GetWorld()->SpawnActor<AWand>(WandClass);
	if (!SpawnedWand) return;

	FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, false);
	SpawnedWand->AttachToComponent(Character->GetMesh(), AttachRules, WandSocketAttachName);
	SpawnedWand->SetOwner(GetOwner());
}


void UWeaponComponent::Attack()
{
	if (!SpawnedWand) return;
	if (bisAttacking) return;
	bisAttacking = true;
	SpawnedWand->Attack();
	UWorld* World = GetWorld();
	World->GetTimerManager().SetTimer(TimerHandle, this, &UWeaponComponent::AttackStop, SpawnedWand->TimeBtwnAttack, false);
}

void UWeaponComponent::AttackStop()
{
	UWorld* World = GetWorld();
	World->GetTimerManager().ClearTimer(TimerHandle);
	bisAttacking = false;
	//SpawnedWand->AttackStop();
}