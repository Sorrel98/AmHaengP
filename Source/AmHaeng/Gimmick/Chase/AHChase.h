// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmHaeng/Gimmick/BeforeChase/AHBeforeChase.h"
#include "AmHaeng/Player/Weapon/AHChickenBlade.h"
#include "AmHaeng/Prop/AHTypes.h"
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
	//void SetWeaponClass();
	void SetIMC(EGimmickMode InGimmickMode);
	
	void ChasedNPCDestroy();

	//Timer
	void StartChaseTimer();
	void EndChaseTimer();
	void ChaseTimerExpired();

private:
	class UAHNPCTeleport* TeleportClass;
	AAHNPCVehicleBase* ChasedNPC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	class UChaosVehicleMovementComponent* NowNPCChaosVehicleMovementComponent;

	FTimerHandle ChaseTimerHandle;

	TObjectPtr<AAHChickenBlade> ChickenBlade;
	TSubclassOf<AAHChickenBlade> ChickenClass;
	TArray<UActorComponent*> ChickenBladeComponentArray;
};
