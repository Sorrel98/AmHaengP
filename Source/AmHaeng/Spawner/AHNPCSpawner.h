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
DECLARE_DELEGATE_OneParam(FOnNPCSpawnEnd, class AAHNPCVehicleBase*)
DECLARE_DELEGATE_OneParam(FSendNPCNumber, int32)

UCLASS(Blueprintable, BlueprintType)
class AMHAENG_API UAHNPCSpawner : public UObject
{
	GENERATED_BODY()

public:
	UAHNPCSpawner();
	virtual ~UAHNPCSpawner() override;
	

	//World의 Spawn Actors 위치 가져오기
	void SetSpawnActorsLocation();
	FORCEINLINE int32 GetSpawnLocationNumber(){ return SpawnLocations.Num(); }
	FORCEINLINE FVector GetSpawnLocationByIndex(int32 Index){ return SpawnLocations[Index];}

	//NPC 갯수
	void SetNPCNumber(int32 InNPCNumber);
	FORCEINLINE int32 GetNPCNumber(){return NPCNumber;}

	//실제 Spawn 함수
	void TestSpawnNPC();
	void NPCVehicleSpawn();
	void SpecificLocationNPCVehicleSpawn(int32 Index);

	FOnNPCSpawnEnd OnNPCSpawnEnd;
	FSendNPCNumber SendNPCNumber;


private:
	TArray<AActor*> NPCSpawnLocationActors;

	TArray<AActor*> GoodNPCSpawnLocationActors;
	TArray<AActor*> BadNPCSpawnLocationActors;
	TArray<FVector> SpawnLocations;
	TArray<FRotator> SpawnRotations;

	AHMathFunctions* MathFunctions;

	int32 NPCNumber;
};
