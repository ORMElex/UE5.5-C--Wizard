// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "NPC.generated.h"


UCLASS()
class LEARNCODING_API ANPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collission)
		USphereComponent* ProxSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPCMessage)
		FString NPCMessage;

	UFUNCTION(BlueprintNativeEvent, Category = Collission)
	void Prox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);


};
