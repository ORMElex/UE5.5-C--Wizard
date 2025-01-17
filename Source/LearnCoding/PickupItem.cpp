// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItem.h"
#include "MyCharacterWizard.h"

// Sets default values
APickupItem::APickupItem() : Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	itemQuantity = 0;
	itemName = "UNKNOWN ITEM";
	
	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ProxSphere"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = Mesh;
	Mesh->SetSimulatePhysics(true);

	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &APickupItem::Prox);
	ProxSphere->SetupAttachment(Mesh);
	ProxSphere->SetSphereRadius(50.f);

}

void APickupItem::Prox_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AMyCharacterWizard>(OtherActor) == nullptr)
	{
		return;
	}
	AMyCharacterWizard* MyChar = Cast<AMyCharacterWizard>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	MyChar->Pickup(this);

	//APlayerController* PController = GetWorld()->GetFirstPlayerController();

	//AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
	Destroy();

}	



