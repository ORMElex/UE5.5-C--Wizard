
#include "Spell.h"
#include "MyCharacterWizard.h"

// Sets default values
ASpell::ASpell()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Damage = 50.f;
	LifeSpan = 3.0f;
	SpellSpeed = 50.f;


	//ProxCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ProxCapsule"));
	//ProxCapsule->SetCapsuleRadius(10.f);
	//ProxCapsule->SetCapsuleHalfHeight(40.f);
	//ProxCapsule->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	////ProxCapsule->SetGenerateOverlapEvents(true);
	//ProxCapsule->OnComponentBeginOverlap.AddDynamic(this, &ASpell::Prox);
	//SetRootComponent(ProxCapsule);


	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spell"));
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Mesh->SetGenerateOverlapEvents(true);
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ASpell::Prox);
	Mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ASpell::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(LifeSpan);
}

void ASpell::Tick(float DeltaTime)
{
	AddActorWorldOffset(spellDirection*SpellSpeed);
}

void ASpell::Prox_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		//OtherActor->TakeDamage();
		UGameplayStatics::ApplyDamage(OtherActor, Damage, NULL, this, nullptr);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Hit");
		Destroy();
	}
}


