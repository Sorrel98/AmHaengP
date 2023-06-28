// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AmHaeng/Prop/AHTypes.h"
#include "AmHaeng/Spawner/AHNPCSpawner.h"
#include "AmHaeng/Widget/Minimap/AHMinimapWidget.h"
#include "AHGameMode.generated.h"



DECLARE_MULTICAST_DELEGATE_OneParam(FGimmickChangeDelegate, EGimmickMode)



UCLASS()
class AMHAENG_API AAHGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AAHGameMode();

	//==========================================================//
	//PATROL
	//==========================================================//
	void InitSpawnNPC();

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

	FORCEINLINE UAHNPCSpawner* GetSpawner();

	void SetNPCNumber(int32 InNPCNumber);
	

	
	//====================================//
	//UI
	//====================================//
	//StartButton을 Viewport에 띄움
	void SpawnButtonOnViewport();
	void GimmickTextOnViewport();
	void IsTargetTextOnViewport();
	void MinimapOnViewport();

	
	//====================================//
	//Chase
	//====================================//
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PlayChaseStartWidgetAnimation();
	

	/**
	 * @brief HitActor Info From Controller
	 * @param 
	 */
	void SetHitVehicleBase(AAHNPCVehicleBase* InHitVehicleBase);
	
	
	void SetGimmickMode(EGimmickMode InGimmickMode);
	FORCEINLINE EGimmickMode GetGimmickMode(){ return NowGimmickMode; };

	//==========================================================//
	//CHASE
	//==========================================================//
	FGimmickChangeDelegate GimmickChangeDelegate;

protected:
	virtual void BeginPlay() override;


	//Widget
protected:
	//Spawn Button
	TSubclassOf<UUserWidget> StartBtnWidgetClass;
	class UAHStartBtnWidget* SpawnStartButton;

	//CPWidget
	class UAHNPCClickCPWidget* ClickCPWidget;

	//Gimmick Mode Widget
	TSubclassOf<UUserWidget> GimmickModeWidgetClass;
	class UAHGimmickModeWidget* GimmickModeWidget;

	//NPCIsTarget Widget
	TSubclassOf<UUserWidget> NPCIsTargetWidgetClass;
	class UAHNPCIsTargetWidget* NPCIsTargetWidget;

	TSubclassOf<UAHMinimapWidget> MinimapWidgetClass;
	class UAHMinimapWidget* MinimapWidget;


	
public:
	class AAHMouseActor* MouseActor;

private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = true))
	class UAHNPCSpawner* Spawner;


	//UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	//TSubclassOf<UAHNPCSpawner> SpawnerClass;

	//NPC Spawning 중인지의 여부
	uint8 bIsNPCSpawning : 1;

	EGimmickMode NowGimmickMode;

	class AAHVehiclePlayerController *PlayerController;

	class AAHNPCVehicleBase* HitVehicleBase;


	//Spawn 되어있는 NPC 갯수
	int32 NPCNumber;

	uint8 bIsChasing;
	
};
