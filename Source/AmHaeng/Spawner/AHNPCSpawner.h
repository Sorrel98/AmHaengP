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
	FOnNPCSpawnEnd OnNPCSpawnEnd;
	FSendNPCNumber SendNPCNumber;

	FTimerHandle SpawnTimerHandle;

	//World의 Spawn Actors 위치 가져오기
	void SetSpawnActorsLocation();
	FORCEINLINE int32 GetSpawnLocationNumber(){ return SpawnLocations.Num(); }
	FORCEINLINE int32 GetTeleportLocationNumber(){ return TeleportLocations.Num(); }
	FORCEINLINE FVector GetSpawnLocationByIndex(int32 Index){ return SpawnLocations[Index];}
	AActor* GetSpawnLocationActor(int32 Index);
	AActor* GetTeleportLocationActor(int32 Index);
	//기타
	void ShuffleArray(TArray<int32>& Array);

	//NPC 갯수
	FORCEINLINE int32 GetNPCNumber(){return NPCNumber;}
	void DecreaseGoodNPC();
	void IncreaseGoodNPC();
	void DecreaseBadNPC();
	void IncreaseBadNPC();
	void CheckNPCNumber(bool IsTarget);

	//사용 안 함
	//void TestSpawnNPC();
	
	//Bad NPC 위치를 어디로 할 것인지 랜덤 결정
	void SetTargetNPCIndex(int32 BadNPCNumber);
	//현재 Index가 Is Target인지 알려줌
	bool IsTargetNPCIndex(uint32 NPCIndex);
	//처음 NPC 한번에 Spawn
	void InitNPCSpawn(uint32 BadNPCNumber);
	void PossessController(AActor* NPCVehicleSpawnActor);

	//랜덤 위치에 spawn 할 수 있는 함수입니다
	void SpawnNewNPC(bool IsTarget);

	//특정 위치에 spawn 할 수 있는 함수입니다
	void SpecificLocationNPCVehicleSpawn(int32 Index, bool IsTarget);
	void SetNPCNumber(bool IsTarget);
	void SpecificLocationNPCVehicleSpawn(AActor* LocationActor, bool IsTarget);
	void PostSpawnNPC(bool IsTarget, AActor* NPCVehicleSpawnActor);
	void SpecificLocationNPCVehicleSpawn(FVector Location, FRotator Rotation, bool IsTarget);
	//UClass* MakeNPCBPClass();

	//Spawn Locaiton 중, RandomIndex를 만들어냅니다.
	int32 RandomSpawnIndex();
	
	//spawn Actor위에 어떤 것이 있는지 없는지 판별하는 함수
	bool IsHitActorOnSpawnActor(int32 SpawnLocationIndex);

private:
	//NPC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TSubclassOf<class AAHNPCVehicleBase> NPCClass;
	/*UPROPERTY()
	TObjectPtr<AAHNPCVehicleBase> NPC;*/
	
	//Good, Bad NPC 갯수 관리
	int32 MaxGoodNPCNumber;
	int32 MaxBadNPCNumber;
	int32 NowGoodNPCNumber;
	int32 NowBadNPCNumber;
	//NPC 마다 붙이는 Index 번호
	int32 NPCNumber = 0;
	
	//TargetNPC Management
	TArray<int32> RandomIndex;
	TArray<int32> TargetNPCIndex;
	
	//Spawn Location
	TArray<AActor*> NPCSpawnLocationActors;
	TArray<FVector> SpawnLocations;
	TArray<FRotator> SpawnRotations;
	//Teleport Location(지금은 사용 안됨)
	TArray<AActor*> NPCTeleportLocationActors;
	TArray<FVector> TeleportLocations;
	TArray<FRotator> TeleportRotations;

	//TestActors
	TArray<AActor*> GoodNPCSpawnLocationActors;
	TArray<AActor*> BadNPCSpawnLocationActors;

	//기타
	TObjectPtr<AHMathFunctions> MathFunctions;
	FActorSpawnParameters SpawnParams;
	
};
