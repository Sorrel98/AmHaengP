// Fill out your copyright notice in the Description page of Project Settings.


#include "AHNPCHPWidget.h"
#include "Components/ProgressBar.h"

void UAHNPCHPWidget::SetNPCHP(float InHP)
{
	if(InHP < KINDA_SMALL_NUMBER) return;
	UE_LOG(LogTemp, Log, TEXT("NPC HP Widget NPC Setup"));
	if(NPC_HPBar!=nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%f"), InHP/100.f);
		NPC_HPBar->SetPercent(InHP/100.f);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("NPC_HPBar is null"));
	}
}

void UAHNPCHPWidget::NativeConstruct()
{
	Super::NativeConstruct();
	NPC_HPBar->SetPercent(1);
	ensure(NPC_HPBar);
}
