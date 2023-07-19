// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmHaeng/Gimmick/BeforeChase/AHBeforeChase.h"
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
	// Sets default values for this actor's properties
	AAHChase();
	void ChaseStart(AAHNPCVehicleBase* InNPC);
	void NPCTeleport();
	void SetNPCState();
	void SetNPCMaxEngineTorque();
	void SetNPCCollisionAndMass();
	void Initialize(AAHNPCVehicleBase* InNPC);
	//void SetWeaponClass();
	void SetIMC(EGimmickMode InGimmickMode);
	
	//void ChasedNPCDestroy();

	//Timer
	void StartChaseTimer();
	void EndChaseTimer();
	void ChaseTimerExpired();


	//Delegate
	FTimeOutDelegate FTimeOutDelegate;
private:
	TObjectPtr<class UAHNPCTeleport> TeleportClass;
	TObjectPtr<AAHNPCVehicleBase> ChasedNPC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TObjectPtr<UChaosVehicleMovementComponent> NowNPCChaosVehicleMovementComponent;

	FTimerHandle ChaseTimerHandle;

	float ChaseTime = 30.f;

};
