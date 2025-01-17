// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

struct NPCMessages
{
	FString message;
	float showTime;
	FColor mesgColor;
	NPCMessages()
	{
		showTime = 5.0f;
		mesgColor = FColor::White;
	}
	NPCMessages(FString message, float showTime = 5, FColor mesgColor = FColor::White)
	{
		this->message = message;
		this->showTime = showTime;
		this->mesgColor = mesgColor;
	}
};


UCLASS()
class LEARNCODING_API AMyHUD : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUDFont")
	UFont* hudFont;

	TArray<NPCMessages> messages;
	virtual void DrawHUD() override;
	void addMessage(NPCMessages msg);
	void DrawMessage(NPCMessages msg);
};
