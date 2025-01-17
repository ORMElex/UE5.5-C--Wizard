// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PickupItem.h"
#include "HealthComponent.h"
#include "WeaponComponent.h"
#include "Engine/DamageEvents.h"

#include "MyCharacterWizard.generated.h"

class APickupItem;

UCLASS()
class LEARNCODING_API AMyCharacterWizard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacterWizard();

private:
	void OnDeath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float Sensitivity = 5.0f;

	TMap<FString, int> Backpack;
	TMap<FString, UTexture2D*> itemsIcons;
	bool isInventoryShowing;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void AddControllerYawInput(float Value) override;

	void MoveForward(float value);
	void MoveSide(float value);

	void Jump();
	void JumpReleased();

	void Sprint();
	void SprintStop();

	void ToggleInventory();

	UFUNCTION()
	void LandedOnGround(const FHitResult& Hit);

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UWeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage", meta = (ClampMin = "0"));
	float LifeSpanTillDeath = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	FVector2D LandedVelocityRange = FVector2D(1000,1500);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	FVector2D LandedDamage = FVector2D(5, 100);

	void Pickup(APickupItem* Item);

};