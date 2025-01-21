// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacterWizard.h"
#include "Kismet/GameplayStatics.h"
#include "Wand.h"
#include "MyCharacterWizard.h"
#include "EnemyAiController.h"
#include "BehaviorTree/BehaviorTree.h"

#include "EnemyBot.generated.h"

UCLASS()
class LEARNCODING_API AEnemyBot : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void SpawnWand();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BotProperties", meta = (ClampMin = "0"))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BotProperties")
	int32 Experience;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BotProperties")
	TSubclassOf<AWand> WandClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BotProperties")
	UBehaviorTree* BehaviorTreeAsset;

	AWand* SpawnedWand;
	AMyCharacterWizard* PlayChar;

	UFUNCTION(BlueprintNativeEvent)
	void Attack();
};
