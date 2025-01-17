#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spell.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"

#include "Wand.generated.h"

UCLASS()
class LEARNCODING_API AWand : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWand();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Collision")
	UStaticMeshComponent* WandMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TSubclassOf<ASpell> SpellType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attack")
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attack", meta = (ClampMin = "0"))
	float range = 1500;

	UFUNCTION(BlueprintNativeEvent, Category = "Attack")
	void Attack();

	

	

};

