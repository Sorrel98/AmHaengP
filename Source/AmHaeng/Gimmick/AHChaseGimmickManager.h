// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AHChaseGimmickManager.generated.h"

UCLASS()
class AMHAENG_API AAHChaseGimmickManager : public AActor
{
	GENERATED_BODY()
	
public:
	void StartChaseGimmick(class AAHNPCVehicleBase* NPCVehicle);
	void ChaseStart();
	void Initialize(class AAHVehiclePlayerController* PC);

	//Get
	class AAHChase* GetChase(){return Chase;}
	class AAHBeforeChase* GetBeforeChase(){return BeforeChase;};

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AAHBeforeChase> BeforeChaseClass;
	UPROPERTY(EditAnywhere)
	TObjectPtr<AAHBeforeChase> BeforeChase;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<AAHChase> Chase;
	UPROPERTY(EditAnywhere)
	TObjectPtr<AAHNPCVehicleBase> ChasedNPC;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAHMinimapWidget> MinimapWidget;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<AAHVehiclePlayerController> PlayerController;

	uint32 ChaseCount = 0;
};