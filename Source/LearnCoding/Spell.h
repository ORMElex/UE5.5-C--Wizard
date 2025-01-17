#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Spell.generated.h"

UCLASS()
class LEARNCODING_API ASpell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpell();

private:
	FVector spellDirection;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpellProperties")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpellProperties")
	float LifeSpan;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpellProperties")
	float SpellSpeed;

	/*UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Collision")
	UCapsuleComponent* ProxCapsule;*/
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Collison")
	UStaticMeshComponent* Mesh;


	UFUNCTION(BlueprintNativeEvent, Category = Collision)
	void Prox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetSpellDirection(FVector& Direction) { this->spellDirection = Direction; }

};

