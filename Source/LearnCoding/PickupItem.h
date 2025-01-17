// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PickupItem.generated.h"

UCLASS()
class LEARNCODING_API APickupItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupItem();


public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item_property)
	UTexture2D* itemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item_property)
	FString itemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item_property)
	int itemQuantity;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Item)
	USphereComponent* ProxSphere;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Item)
	UStaticMeshComponent* Mesh;

	UFUNCTION(BlueprintNativeEvent, Category = Collision)
	void Prox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
