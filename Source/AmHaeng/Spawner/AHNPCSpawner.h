// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "AHNPCSpawner.generated.h"


/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class AMHAENG_API UAHNPCSpawner : public UObject
{
	GENERATED_BODY()
public:
	UAHNPCSpawner();
	~UAHNPCSpawner();

	//Spawn될 위치 정하기
	void SetSpawningRandomLocations();

	//Delegate 수신하는 함수
	UFUNCTION()
	void GetDelegateFromWidget();



protected:
	//virtual void BeginPlay() override;
private:
	TArray<FVector> SpawnLocations;
	TArray<FRotator> SpawnRotations;

	void NPCVehicleSpawn();

};
