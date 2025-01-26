// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"

#include "WeaponComponent.generated.h"

class AWand;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEARNCODING_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool bisAttacking = false;

	ACharacter* Character;

	void SpawnWand();

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AWand> WandClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName WandSocketAttachName = "WandSocket";

	UPROPERTY()
	AWand* SpawnedWand = nullptr;

	UFUNCTION(BlueprintCallable)
	bool isAttacking() const { return bisAttacking; }

	virtual void Attack();
	virtual void AttackStop();
		
private:
	FTimerHandle TimerHandle;
};
