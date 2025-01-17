// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"

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

	SpawnWand();
	
}


void UWeaponComponent::SpawnWand()
{
	if (!GetWorld()) return;

	ACharacter* Character = Cast<ACharacter>(GetOwner());
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
	bisAttacking = true;
	SpawnedWand->Attack();
}

void UWeaponComponent::AttackStop()
{
	if (!SpawnedWand) return;
	bisAttacking = false;
	//SpawnedWand->AttackStop();
}