// Fill out your copyright notice in the Description page of Project Settings.


#include "AHMinimapWidget.h"

#include "ShaderPrintParameters.h"
#include "AmHaeng/Game/AHGameMode.h"
#include "AmHaeng/Widget/AHNPCMinimapCursor.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"
#include "Components/Overlay.h"

void UAHMinimapWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UAHMinimapWidget::MinimapSettingEnd()
{
	AAHGameMode* GameMode = GetWorld()->GetAuthGameMode<AAHGameMode>();
	if(GameMode)
	{
		Spawner = GameMode->GetSpawner();
		if(Spawner)
		{
			Spawner->OnNPCSpawnEnd.BindUObject(this, &UAHMinimapWidget::CallAddNPCIcon);
		}
		else
		{
			UE_LOG(LogTemp,Warning, TEXT("spawner가 없습니다"));
		}
		
	}
}

void UAHMinimapWidget::AddNPCIcon_Implementation(AAHNPCVehicleBase* InNPCVehicleBase)
{
}

void UAHMinimapWidget::CallAddNPCIcon(AAHNPCVehicleBase* InNPCVehicleBase)
{
	this->AddNPCIcon(InNPCVehicleBase);
}


