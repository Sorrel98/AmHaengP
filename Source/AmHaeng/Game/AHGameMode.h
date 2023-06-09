// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmHaeng/Gimmick/BeforeChase/AHSpline.h"
#include "GameFramework/GameMode.h"
#include "AmHaeng/Prop/AHTypes.h"
#include "AmHaeng/Spawner/AHNPCSpawner.h"
#include "AmHaeng/Widget/Minimap/AHMinimapWidget.h"
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
	void PlayPause(bool IsPause);

	//Static
	static EGimmickMode NowGimmickMode;
	static class AAHVehiclePlayerController* PlayerController;
	static AAHSpline* SplineActor;

	//==========================================================//
	//PATROL
	//==========================================================//
	void InitSpawnNPC();
	void MakeSpline();

	//Gamemode의 Delegate들 Binding
	void BindingDelegates();
	
	//CPloading이 성공적으로 마친 것을 받아옴
	void CPLoadingFinished();


	//====================================//
	//Spawn
	//====================================//

	//NPCSpawing여부를 Setting 함
	UFUNCTION()
	void SetNPCSpawningState(uint8 NowState);

	//Mouse Actor를 World에 스폰함
	void MouseActorSpawn();

	UAHNPCSpawner* GetSpawner();

	void SetNPCNumber(int32 InNPCNumber);
	

	
	//====================================//
	//UI
	//====================================//
	//StartButton을 Viewport에 띄움
	void WorldWidgetOnViewport();
	//void GimmickTextOnViewport();
	void IsTargetTextOnViewport();
	void MinimapOnViewport();

	
	//====================================//
	//Chase
	//====================================//
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PlayChaseStartWidgetAnimation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PlayCrashGlassAnimation();
	
	void SetHitVehicleBase(AAHNPCVehicleBase* InHitVehicleBase);
	
	void SetGimmickMode(EGimmickMode InGimmickMode);
	FORCEINLINE const EGimmickMode GetGimmickMode();

	void FinishChase(bool IsChaseSuccess);
	

	//==========================================================//
	//Mannequin
	//==========================================================//
	FGimmickChangeDelegate GimmickChangeDelegate;

	class AAHSpline* GetSpline(){return SplineActor; }


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
	uint32 PastSecond = 10;
	
	

protected:
	virtual void BeginPlay() override;
	
	//WorldWidget
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UAHWorldWidget> WorldWidgetClass;
	UAHWorldWidget* WorldWidget;

	//CPWidget
	/*UPROPERTY(EditAnywhere)
	class UAHNPCClickCPWidget* ClickCPWidget;*/

	//Gimmick Mode Widget
	/*UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> GimmickModeWidgetClass;
	class UAHGimmickModeWidget* GimmickModeWidget;*/

	//NPCIsTarget Widget
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> NPCIsTargetWidgetClass;
	class UAHNPCIsTargetWidget* NPCIsTargetWidget;

	//Minimap Widget
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAHMinimapWidget> MinimapWidgetClass;
	UAHMinimapWidget* MinimapWidget;

public:
	class AAHMouseActor* MouseActor;

protected:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = true))
	class UAHNPCSpawner* Spawner;

	//NPC Spawning 중인지의 여부
	uint8 bIsNPCSpawning : 1;
	
	AAHNPCVehicleBase* HitVehicleBase;
	AAHNPCVehicleBase* ChasedNPC;

	//Spawn 되어있는 NPC 갯수
	int32 NPCNumber;
	
	//Chase
	UPROPERTY(EditAnywhere)
	TSubclassOf<AAHChaseGimmickManager> ChaseGimmickManagerClass;
	AAHChaseGimmickManager* ChaseGimmickManager;

	uint32 InitReputationValue = 30;
};
