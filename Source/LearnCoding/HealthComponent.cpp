// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	MaxHealth = 100;
	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamage);
	}
	SetHealth(MaxHealth);
}



void UHealthComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0, MaxHealth);
	OnHealthChanged.Broadcast(Health);
}

bool UHealthComponent::isDead() const
{
	return Health <= 0.0f;
}

void UHealthComponent::OnTakeAnyDamage_Implementation(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || isDead()) return;
	SetHealth(Health - Damage);

	if (isDead()) OnDeath.Broadcast();
}

