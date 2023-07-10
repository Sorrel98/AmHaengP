// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmHaeng/Game/AHGameMode.h"
#include "GameFramework/Actor.h"
#include "AHChaseGimmickManager.generated.h"

UCLASS()
class AMHAENG_API AAHChaseGimmickManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAHChaseGimmickManager();

	void StartChaseGimmick(class AAHVehiclePlayerController* PC, class AAHNPCVehicleBase* NPCVehicle, class UAHMinimapWidget* Minimap);

	void ChaseStart();

	void Initialize();


protected:
	
private:
	class AAHBeforeChase* BeforeChase;

	class AAHChase* Chase;

	class AAHAfterChase* AfterChase;
	
	AAHNPCVehicleBase* ChasedNPC;

	UAHMinimapWidget* MinimapWidget;
};
