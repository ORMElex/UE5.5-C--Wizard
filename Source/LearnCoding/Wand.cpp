#include "Wand.h"
#include "DrawDebugHelpers.h"

// Sets default values
AWand::AWand()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	WandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WandMesh"));
	SetRootComponent(WandMesh);

}

// Called when the game starts or when spawned
void AWand::BeginPlay()
{
	Super::BeginPlay();

}

void AWand::Attack_Implementation()
{
	if (!GetWorld()) return;

	const ACharacter* Char = Cast<ACharacter>(GetOwner());
	if (!Char) return;

	const AController* Controller = Char->GetController<APlayerController>();
	if (!Controller) return;

	const FTransform socktrfm = WandMesh->GetSocketTransform(MuzzleSocketName);
	const FVector startloc = socktrfm.GetLocation();
	
	FVector ViewLoc;
	FRotator ViewRot;
	if (Char->IsPlayerControlled())
	{
		Controller->GetPlayerViewPoint(ViewLoc, ViewRot);
	}
	else
	{
		ViewLoc = startloc;
		ViewRot = WandMesh->GetSocketRotation(MuzzleSocketName);
	}
	const FVector forw = ViewRot.Vector().GetSafeNormal();
	const FVector endloc = ViewLoc + forw * range;

	FVector spellDirection = (endloc - startloc).GetSafeNormal();
	DrawDebugLine(GetWorld(), startloc, endloc, FColor::Red, false, 3.f, 0, 3.f);

	const FTransform SpawnTransform(socktrfm.GetRotation().Rotator(), startloc);

	ASpell* spell = GetWorld()->SpawnActor<ASpell>(SpellType, SpawnTransform);
	
	if (spell)
	{
		spell->SetSpellDirection(spellDirection);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Couldn't create actor of ASpell");
	}
}



