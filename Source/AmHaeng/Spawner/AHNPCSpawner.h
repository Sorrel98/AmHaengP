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
	virtual ~UAHNPCSpawner() override;
	

	//World의 Spawn Actors 위치 가져오기
	void GetSpawnActorsLocation();

	//Delegate 수신하는 함수
	UFUNCTION()
	//void GetDelegateFromWidget();


	//실제 Spawn 함수
	void TestSpawnNPC();

	void NPCVehicleSpawn();

	void RandomNPCVehicleSpawn(int32 Index);


private:
	TArray<AActor*> NPCSpawnLocationActors;

	TArray<AActor*> GoodNPCSpawnLocationActors;
	TArray<AActor*> BadNPCSpawnLocationActors;
	TArray<FVector> SpawnLocations;
	TArray<FRotator> SpawnRotations;

	AHMathFunctions* MathFunctions;
};
