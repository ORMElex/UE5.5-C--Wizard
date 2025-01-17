// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Engine/Canvas.h"

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();
	
	for (int c = messages.Num() - 1; c >= 0; c--)
	{
		float outputWidth, outputHeight, pad = 10.f;
		GetTextSize(messages[c].message, outputWidth, outputHeight, hudFont, 1.f);
		float msgH = outputHeight + 2.f * pad;
		float x = 0.f, y = c * msgH;
		DrawRect(FLinearColor::Black, x, y, Canvas->SizeX, msgH);
		DrawText(messages[c].message, messages[c].mesgColor, x + pad, y + pad, hudFont);
		messages[c].showTime -= GetWorld()->GetDeltaSeconds();
		if (messages[c].showTime < 0)
		{
			messages.RemoveAt(c);
		}
	}
}

void AMyHUD::DrawMessage(NPCMessages msg)
{

}

void AMyHUD::addMessage(NPCMessages msg)
{
	messages.Add(msg);
}