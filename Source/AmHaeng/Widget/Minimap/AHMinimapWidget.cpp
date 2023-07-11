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
		if(NPCCursorMap.Num())
		{
			UAHNPCMinimapCursor** TempCursor = NPCCursorMap.Find(InTarget);
			if(TempCursor!=nullptr)
			{
				UAHNPCMinimapCursor* AHCursor = *TempCursor;
				if(AHCursor)
				{
					AHCursor->SetNPCCursorRed();
				}
			}
		}
	}
}

void UAHMinimapWidget::CheckAndDestroyIcon()
{
	/*UE_LOG(LogTemp, Log, TEXT("[start] GarbagaCollector NPCCursorMap num : %d"), NPCCursorMap.Num());
	for(auto it : NPCCursorMap)
	{
		if(!it.Value->GetIsVisible()) //NPC Vehicle이 살아있지 않다면
		{
		UE_LOG(LogTemp, Log, TEXT("NPC는 현재 없는 상태이므로 icon remove 합니다."));
		it.Value->RemoveFromParent();
		NPCCursorMap.Remove(it.Key);
		}
	}
	UE_LOG(LogTemp, Log, TEXT("[End] GarbagaCollector NPCCursorMap num : %d"), NPCCursorMap.Num());
	*/
	
}


