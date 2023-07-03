// Fill out your copyright notice in the Description page of Project Settings.


#include "AHMinimapWidget.h"

#include "AmHaeng/Game/AHGameMode.h"
#include "Containers/Map.h"
#include "AmHaeng/Widget/Minimap/AHNPCMinimapCursor.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"

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

void UAHMinimapWidget::SetNPCCursorRed(AAHNPCVehicleBase* InTarget)
{
	if(InTarget)
	{
		//Map에서 Intarget 찾아서 Cursor에게 Tint 변경 요청
		UE_LOG(LogTemp, Log, TEXT("npc is in map"));
		if(NPCCursorMap.Num()) // 왜 NPCCursorMap 자체에 접근이 안되는 걸까요
		{
			UE_LOG(LogTemp, Warning, TEXT("NPCCursorMap is %d"), NPCCursorMap.Num());
			UAHNPCMinimapCursor** TempCursor = NPCCursorMap.Find(InTarget);
			if(TempCursor!=nullptr)
			{
				UAHNPCMinimapCursor* AHCursor = *TempCursor;
				AHCursor->SetNPCCursorRed();
			}
		}
	}
}


