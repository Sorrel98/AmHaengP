// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AmHaeng/Widget/AHStartBtnWidget.h"
#include "AHGameMode.generated.h"


/**
 * 
 */
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
	void StartButtonOnViewport();

	//Widget���� broadcast �� delegate�� binding �ϴ� �Լ�
	void BindingWithWidgetDelegate();
	
	//virtual void HandleMatchIsWaitingToStart() override;

	

protected:
	virtual void BeginPlay() override;

	TSubclassOf<UUserWidget> WidgetClass;
	UAHStartBtnWidget* SpawnStartButton;

private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = true))
	class UAHNPCSpawner* Spawner;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TSubclassOf<UAHNPCSpawner> SpawnerClass;


	
	//NPC Spawning 중인지의 여부
	uint8 bIsNPCSpawning : 1;
};
