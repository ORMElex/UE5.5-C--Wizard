// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"
#include "MyCharacterWizard.h"
#include "MyHUD.h"

// Sets default values
ANPC::ANPC()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ProxSphere"));
	ProxSphere->SetupAttachment(RootComponent);
	ProxSphere->SetSphereRadius(32.f);
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &ANPC::Prox);
	NPCMessage = "Hi, I'm NPC";
}

void ANPC::Prox_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AMyCharacterWizard>(OtherActor) == nullptr)
	{
		return;
	}
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	if (PController)
	{
		AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
		hud->addMessage(NPCMessages(NPCMessage, 5.f, FColor::Yellow));
	}
}

