// Fill out your copyright notice in the Description page of Project Settings.


#include "AHNPCSpawner.h"
#include "Engine/Blueprint.h"
#include "AmHaeng/Player/AHVehiclePlayerController.h"
#include "AmHaeng/Game/AHGameMode.h"

UAHNPCSpawner::UAHNPCSpawner()
{
	SetSpawningRandomLocations();
}


void UAHNPCSpawner::SetSpawningRandomLocations()
{
	SpawnLocations.Emplace(FVector(11650.0f, 3560.0f, 0.0f));
	SpawnLocations.Emplace(FVector(-9030.0f, -770.0f, 0.0f));
	SpawnLocations.Emplace(FVector(2293.372449f, 10120.637944f, 0.0f));
	SpawnLocations.Emplace(FVector(421.089786f, -1400.890789f, 0.0f));
	SpawnLocations.Emplace(FVector(-6150.0f, 5310.0f, 0.0f));
	SpawnLocations.Emplace(FVector(4030.0f, 5600.0f, 0.0f));

	SpawnRotations.Emplace(FRotator(0.0f, 90.0f, 0.0f));
	SpawnRotations.Emplace(FRotator(0.0f, 90.0f, 0.0f));
	SpawnRotations.Emplace(FRotator(0.0f, 90.0f, 0.0f));
	SpawnRotations.Emplace(FRotator(0.0f, 0.0f, 0.0f));
	SpawnRotations.Emplace(FRotator(0.0f, -30.0f, 0.0f));
	SpawnRotations.Emplace(FRotator(0.0f, 0.0f, 0.0f));
}


void UAHNPCSpawner::GetDelegateFromWidget()
{
	NPCVehicleSpawn();
}


void UAHNPCSpawner::NPCVehicleSpawn()
{
	if (GetOuter()==nullptr)
	{
		return;
	}
	FSoftObjectPath NPCBPRef(TEXT("/Game/VehicleNPC/OffroadCar_Pawn.OffroadCar_Pawn"));
	UBlueprint* NPCBPObj = Cast<UBlueprint>(NPCBPRef.TryLoad());
	if (NPCBPObj == nullptr) return;
	
	UClass* NPCBPClass = NPCBPObj->GeneratedClass;
	if (NPCBPClass == nullptr) return;
	
	UWorld* World = GetWorld();
	if (World == nullptr) return;
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (int32 ix = 0; ix < SpawnLocations.Num(); ++ix)
	{
		AActor* NPCVehicleSpawnActor = World->SpawnActor<AActor>(NPCBPClass, SpawnLocations[ix], SpawnRotations[ix], SpawnParams);
		if (NPCVehicleSpawnActor)
		{
			AAHVehiclePlayerController* SpawnedNPCController = GetWorld()->SpawnActor<AAHVehiclePlayerController>();
			if (SpawnedNPCController)
			{
				SpawnedNPCController->Possess(Cast<APawn>(NPCVehicleSpawnActor));
			}
		}
	}
}


UAHNPCSpawner::~UAHNPCSpawner()
{
}
