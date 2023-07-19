// Fill out your copyright notice in the Description page of Project Settings.


#include "AHChase.h"

#include "AmHaeng/Game/AHGameMode.h"
#include "AmHaeng/Player/AHVehiclePlayerController.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"
#include "GameFramework/Actor.h"
#include "NPCTeleport/AHNPCTeleport.h"

void AAHChase::ChaseStart(AAHNPCVehicleBase* InNPC)
{
	//Chased NPC Update
	ChasedNPC = InNPC;
	//Initialize(InNPC);
	//Chicken Blade 셋팅
	AAHVehiclePlayerController::PlayerPawn->GetChickenBlade()->InitChickenBlade(InNPC);
	//NPC 상태값 셋팅
	SetNPCState();
	//IMC Chase 모드로 변경
	SetIMC(EGimmickMode::Chase);
}

void AAHChase::NPCTeleport()
{
	TeleportClass->Teleport(ChasedNPC);
}

void AAHChase::SetNPCState()
{
	//Max Engine Torque 올려주고
	//Collision 없애고 Mass 올리기 -> 부딪혀진 NPC 날아가는 지 확인
	SetNPCMaxEngineTorque();
	SetNPCCollisionAndMass();
}

void AAHChase::SetNPCMaxEngineTorque()
{
	ChasedNPC->AHSetMaxEngineTorque(400.0f);
}

void AAHChase::SetNPCCollisionAndMass()
{
}

void AAHChase::Initialize(AAHNPCVehicleBase* InNPC)
{
	TeleportClass = NewObject<UAHNPCTeleport>();
	ChasedNPC = InNPC;
	TeleportClass->Rename(TEXT("TeleportOuter"), this);
}

void AAHChase::SetIMC(EGimmickMode InGimmickMode)
{
	//UE_LOG(LogTemp, Log, TEXT("AHChase : Set IMC"));
	if(InGimmickMode == EGimmickMode::Chase)
	{
		AAHGameMode::PlayerController->SetChaseIMC();
	}
}

void AAHChase::StartChaseTimer()
{
	//Timer 측정 -> 몇초로 할까.. 일단 30초로 하자
	//30초 뒤에 End
	GetWorld()->GetTimerManager().SetTimer(ChaseTimerHandle, this, &AAHChase::ChaseTimerExpired, ChaseTime, false);
}

void AAHChase::EndChaseTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(ChaseTimerHandle);
}

void AAHChase::ChaseTimerExpired()
{
	//타이머 실행되면 코드 작성
	FTimeOutDelegate.Broadcast(false);
}

