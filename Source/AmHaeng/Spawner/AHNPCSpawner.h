// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "AmHaeng/Dictionary/AHMathFunctions.h"
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

	//World의 Spawn Actors 위치 가져오기
	void GetSpawnActorsLocation();


	//Delegate 수신하는 함수
	UFUNCTION()
	void GetDelegateFromWidget();


	void TestSpawnNPC();

	
private:

	void NPCVehicleSpawn();

	void RandomNPCVehicleSpawn(int32 Index);

	TArray<AActor*> NPCSpawnLocationActors;
	TArray<FVector> SpawnLocations;
	TArray<FRotator> SpawnRotations;

	AHMathFunctions* MathFunctions;

};
