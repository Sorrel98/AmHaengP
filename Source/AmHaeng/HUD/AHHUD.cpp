// Fill out your copyright notice in the Description page of Project Settings.


#include "AHHUD.h"

#include "AmHaeng/Player/AHPlayerPawn.h"
#include "AmHaeng/Widget/Gimmick/AHNPCIsTargetWidget.h"
#include "AmHaeng/Widget/Minimap/AHMinimapWidget.h"
#include "AmHaeng/Widget/World/AHWorldWidget.h"
#include "Blueprint/UserWidget.h"

void AAHHUD::DrawHUD()
{
	Super::DrawHUD();
	
}

void AAHHUD::HUDOnViewport(int32 InReputationValue, int32 InPastSecond)
{
	InitReputationValue = InReputationValue;
	PastSecond = InPastSecond;
	DrawWorldWidget();
	DrawIsTargetWidget();
	DrawMinimap();
}

void AAHHUD::DrawWorldWidget()
{
	if (WorldWidgetClass)
	{
		WorldWidget = Cast<UAHWorldWidget>(CreateWidget(GetWorld(), WorldWidgetClass));
		if (IsValid(WorldWidget))
		{
			WorldWidget->AddToViewport();
			AAHPlayerPawn::Reputation = InitReputationValue;
			WorldWidget->SetReputation(InitReputationValue);
			WorldWidget->SetWorldTime(PastSecond);
			WorldWidget->InvalidateLayoutAndVolatility();
		}
	}
}

void AAHHUD::DrawIsTargetWidget()
{
	if (IsValid(NPCIsTargetWidgetClass))
	{
		NPCIsTargetWidget = Cast<UAHNPCIsTargetWidget>(CreateWidget(GetWorld(), NPCIsTargetWidgetClass));
		if (IsValid(NPCIsTargetWidget))
		{
			NPCIsTargetWidget->AddToViewport();
			NPCIsTargetWidget->AllTextInvisible();
		}
	}
}

void AAHHUD::DrawMinimap()
{
	if (IsValid(MinimapWidgetClass))
	{
		MinimapWidget = Cast<UAHMinimapWidget>(CreateWidget(GetWorld(), MinimapWidgetClass));
		if (IsValid(MinimapWidget))
		{
			MinimapWidget->AddToViewport();
		}
	}
}

void AAHHUD::BeginPlay()
{
	Super::BeginPlay();
}
