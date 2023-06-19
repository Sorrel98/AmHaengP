// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AmHaeng/Prop/AHTypes.h"
#include "AHGameMode.generated.h"



DECLARE_MULTICAST_DELEGATE_OneParam(FGimmickChangeDelegate, EGimmickMode)

UCLASS()
class AMHAENG_API AAHGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AAHGameMode();

	//NPCSpawing여부를 Setting 함
	UFUNCTION()
	void SetNPCSpawningState(uint8 NowState);

	//StartButton을 Viewport에 띄움
	void SpawnButtonOnViewport();

	void GimmickTextOnViewport();

	//Gamemode의 Delegate들 Binding
	void BindingDelegates();

	//Mouse Actor를 World에 스폰함
	void MouseActorSpawn();

	//CPloading이 성공적으로 마친 것을 받아옴
	void CPLoadingFinished();

	void SetGimmickMode(EGimmickMode InGimmickMode);
	FORCEINLINE EGimmickMode GetGimmickMode(){ return NowGimmickMode; };

	FGimmickChangeDelegate GimmickChangeDelegate;

protected:
	virtual void BeginPlay() override;


	//Widget
protected:
	TSubclassOf<class UUserWidget> StartBtnWidgetClass;
	class UAHStartBtnWidget* SpawnStartButton;

	class UAHNPCClickCPWidget* ClickCPWidget;

	TSubclassOf<class UUserWidget> GimmickModeWidgetClass;
	class UAHGimmickModeWidget* GimmickModeWidget;

public:
	class AAHMouseActor* MouseActor;

private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = true))
	class UAHNPCSpawner* Spawner;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TSubclassOf<UAHNPCSpawner> SpawnerClass;

	//NPC Spawning 중인지의 여부
	uint8 bIsNPCSpawning : 1;

	EGimmickMode NowGimmickMode;
};
