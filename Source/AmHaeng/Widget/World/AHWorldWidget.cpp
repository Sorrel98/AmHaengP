// Fill out your copyright notice in the Description page of Project Settings.


#include "AHWorldWidget.h"

#include "AmHaeng/Player/AHVehiclePlayerController.h"

void UAHWorldWidget::BindWorldWidgetDelegate()
{
	
}

void UAHWorldWidget::SetReputation(uint32 InReputation)
{
	UE_LOG(LogTemp, Warning, TEXT("[WorldWidget] SetReputation : %d"), InReputation);
	Reputation->SetText(FText::FromString(FString::FromInt(InReputation)));
	this->InvalidateLayoutAndVolatility();
}

void UAHWorldWidget::SetWorldTime(uint32 InWorldTime)
{
	WorldTime->SetText(FText::FromString(FString::FromInt(InWorldTime)));
	this->InvalidateLayoutAndVolatility();
}
