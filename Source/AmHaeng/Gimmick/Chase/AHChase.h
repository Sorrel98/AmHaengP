// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmHaeng/Player/Weapon/AHChickenBlade.h"
#include "AmHaeng/Prop/AHTypes.h"
#include "GameFramework/Actor.h"
#include "AHChase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FTimeOutDelegate, bool)
UCLASS()
class AMHAENG_API AAHChase : public AActor
{
	GENERATED_BODY()
	
public:
	//Delegate
	FTimeOutDelegate FTimeOutDelegate;
	
	void ChaseStart(AAHNPCVehicleBase* InNPC);
	void Initialize(AAHNPCVehicleBase* InNPC);

	//사용 안 함
	void NPCTeleport();

	//NPC Setting
	void SetNPCState();
	void SetNPCMaxEngineTorque();
	void SetNPCCollisionAndMass();

	//IMC
	void SetIMC(EGimmickMode InGimmickMode);
	
	//Timer 사용 안 함
	void StartChaseTimer();
	void EndChaseTimer();
	void ChaseTimerExpired();
	
private:
	TObjectPtr<class UAHNPCTeleport> TeleportClass;
	TObjectPtr<AAHNPCVehicleBase> ChasedNPC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TObjectPtr<UChaosVehicleMovementComponent> NowNPCChaosVehicleMovementComponent;

	//사용 안 함
	FTimerHandle ChaseTimerHandle;

	float ChaseTime = 30.f;
};
