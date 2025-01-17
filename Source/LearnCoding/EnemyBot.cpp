// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBot.h"


// Sets default values
AEnemyBot::AEnemyBot()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AEnemyAIController::StaticClass();

	Speed = 50;
	HitPoints = 20;
	Experience = 0;
	BaseAttackDamage = 1;
	AttackTimeout = 1.5f;
	TimeSinceLastStrike = 0.f;
	
}

// Called when the game starts or when spawned
void AEnemyBot::BeginPlay()
{
	Super::BeginPlay();

	PlayChar = Cast<AMyCharacterWizard>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
}

// Called every frame
void AEnemyBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AEnemyBot::Attack_Implementation()
{
	SpawnedWand->Attack();
}

void AEnemyBot::SpawnWand()
{
	SpawnedWand = GetWorld()->SpawnActor<AWand>(WandClass, RootComponent->GetComponentLocation(), RootComponent->GetComponentRotation());
	FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, false);
	SpawnedWand->AttachToComponent(GetMesh(), AttachRules, TEXT("WandSocket"));
}
