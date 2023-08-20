// Fill out your copyright notice in the Description page of Project Settings.


#include "AHInMap.h"

#include "AmHaeng/Game/AHGameMode.h"
#include "AmHaeng/Spawner/AHNPCSpawner.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"

class UBoxComponent;

void AAHInMap::NPCIsOutOfMap(AAHNPCVehicleBase* OutNPC)
{
	/*if(OutNPC->GetIsChased())
	{
		UE_LOG(LogTemp, Log, TEXT("Out of Map이지만 chased npc라 무시합니다"));
		return;
	}
	if(Spawner==nullptr)
	{
		SetSpawner();
	}
	//Spawner->SpawnNewNPC(OutNPC->GetIsTargetNPC());
	OutNPC->Destroy();*/
}

void AAHInMap::SetSpawner()
{
	AGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode();
	if(GameModeBase)
	{
		AAHGameMode* AHGameMode = Cast<AAHGameMode>(GameModeBase);
		if(AHGameMode)
		{
			Spawner = AHGameMode->GetSpawner();
		}
	}
}


// Called when the game starts or when spawned
void AAHInMap::BeginPlay()
{
	Super::BeginPlay();
	SetSpawner();
}

