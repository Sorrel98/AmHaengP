// Fill out your copyright notice in the Description page of Project Settings.


#include "AHInMap.h"

#include "AmHaeng/Game/AHGameMode.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"

class UBoxComponent;

void AAHInMap::NPCIsOutOfMap(AAHNPCVehicleBase* OutNPC)
{
	/*if(Spawner==nullptr)
	{
		SetSpawner();
	}
	OutNPC->Destroy();
	GetWorld()->GetTimerManager().SetTimer(FindSpawnerTimerHandle, this, &AAHInMap::SpawnNewNPC, 5.0f, true);
*/
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

void AAHInMap::SpawnNewNPC()
{
	/*if(Spawner)
	{
		Spawner->SpawnNewNPC(
	}*/
}

// Called when the game starts or when spawned
void AAHInMap::BeginPlay()
{
	Super::BeginPlay();
	SetSpawner();
}

// Called every frame
void AAHInMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

