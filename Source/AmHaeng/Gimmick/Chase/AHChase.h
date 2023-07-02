// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmHaeng/Gimmick/BeforeChase/AHBeforeChase.h"
#include "GameFramework/Actor.h"
#include "AHChase.generated.h"

UCLASS()
class AMHAENG_API AAHChase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAHChase();
	void ChaseStart(class AAHNPCVehicleBase* InNPC);
	void NPCTeleport();
	void SetNPCState();
	void SetNPCMaxEngineTorque();
	void SetNPCCollisionAndMass();
	void Initialize(AAHNPCVehicleBase* InNPC);

private:
	class UAHNPCTeleport* TeleportClass;
	AAHNPCVehicleBase* ChasedNPC;
};
