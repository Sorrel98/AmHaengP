// Fill out your copyright notice in the Description page of Project Settings.


#include "AHNPCClickCPWidget.h"
#include "AmHaeng/Player/AHVehiclePlayerController.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"

void UAHNPCClickCPWidget::AHNPCClickCPWidget()
{
	
	//Percent = 0.3f;
}

void UAHNPCClickCPWidget::SetPercent_Implementation(const float InPercentage)
{
}

void UAHNPCClickCPWidget::SetVisibility(ESlateVisibility InVisibility)
{
	Super::SetVisibility(InVisibility);
}

void UAHNPCClickCPWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//ensure(CircularProgressBar);
}
