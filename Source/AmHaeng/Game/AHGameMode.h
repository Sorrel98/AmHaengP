// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AmHaeng/Prop/AHTypes.h"
#include "AHGameMode.generated.h"


class AAHChaseGimmickManager;
DECLARE_MULTICAST_DELEGATE_OneParam(FGimmickChangeDelegate, EGimmickMode)
DECLARE_DELEGATE_OneParam(FWorldTimeOutDelegate, uint32)
UCLASS()
class AMHAENG_API AAHGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AAHGameMode();

	//Static
	static EGimmickMode NowGimmickMode;
	static class AAHVehiclePlayerController* PlayerController;
	static class AAHSpline* SplineActor;

	
	//==========================================================//
	//PATROL
	//==========================================================//
	void InitSpawnNPC();
	void MakeSpline();

	//Gamemode의 Delegate들 Binding
	void BindingDelegates();
	
	//CPloading이 성공적으로 마친 것을 받아옴
	void CPLoadingFinished();

	TObjectPtr<class AAHMouseActor> MouseActor;


	//==========================================================//
	//Spawn
	//==========================================================//
	void SetAllNPCNumber();
	void SetBadNPCNumber();

	//NPCSpawing여부를 Setting 함
	UFUNCTION()
	void SetNPCSpawningState(uint8 NowState);
	void SetNPCNumber(int32 InNPCNumber);

	//Mouse Actor를 World에 스폰함
	void MouseActorSpawn();
	class UAHNPCSpawner* GetSpawner();
	
	
	//==========================================================//
	//Chase
	//==========================================================//
	void SetHitVehicleBase(class AAHNPCVehicleBase* InHitVehicleBase);
	
	void SetGimmickMode(EGimmickMode InGimmickMode);
	FORCEINLINE const EGimmickMode GetGimmickMode();

	void FinishChase(bool IsChaseSuccess);

	void IsPlayerSpeedZero();
	

	//==========================================================//
	//Mannequin
	//==========================================================//
	FGimmickChangeDelegate GimmickChangeDelegate;

	AAHSpline* GetSpline(){return SplineActor; }
	
	UFUNCTION(BlueprintCallable)
	AAHNPCVehicleBase* GetChasedNPC(){ return ChasedNPC; };

	
	//==========================================================//
	//World
	//==========================================================//
	FTimerHandle WorldTimer;
	FWorldTimeOutDelegate WorldTimeOutDelegate;
	
	void SetWorldTimer();
	void WorldTimerTickTok();
	void OpenLobbyLevel();
	
	FString LobbyLevelName = "Lobby";
	int32 PastSecond = 120;


	//==========================================================//
	//Sound
	//==========================================================//
	UFUNCTION(BlueprintNativeEvent)
	void CorrectSound();

	UFUNCTION(BlueprintNativeEvent)
	void InCorrectSound();

	
	//==========================================================//
	//Timer
	//==========================================================//
	FTimerHandle PlayerSpeedZeroTimer;

	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = true))
	TObjectPtr<UAHNPCSpawner> Spawner;

	//NPC Spawning 중인지의 여부
	uint8 bIsNPCSpawning : 1;

	//Spawn 되어있는 NPC 갯수
	int32 SpawnedNPCNumber;

	//클릭 중인 NPC
	TObjectPtr<AAHNPCVehicleBase> HitVehicleBase;
	//Chase 시작된 NPC
	TObjectPtr<AAHNPCVehicleBase> ChasedNPC;
	
	//Chase
	UPROPERTY(EditAnywhere)
	TSubclassOf<AAHChaseGimmickManager> ChaseGimmickManagerClass;
	TObjectPtr<AAHChaseGimmickManager> ChaseGimmickManager;

	//Reputation
	int32 InitReputationValue = 30;

	//초기 badnpcnumber setting
	int32 BadNPCNumber;
	int32 InitAllNPCNumber;
	
	//HUD
	TObjectPtr<class AAHHUD> AHHUD;
};
