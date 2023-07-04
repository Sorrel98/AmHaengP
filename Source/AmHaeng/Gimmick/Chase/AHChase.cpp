// Fill out your copyright notice in the Description page of Project Settings.


#include "AHChase.h"

#include "AmHaeng/Game/AHGameMode.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"
#include "NPCTeleport/AHNPCTeleport.h"

// Sets default values
AAHChase::AAHChase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	
}

void AAHChase::ChaseStart(AAHNPCVehicleBase* InNPC)
{
	Initialize(InNPC);
	//Teleport하고
	NPCTeleport();
	//NPC 상태값 셋팅
	SetNPCState();
	
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
	StartChaseTimer();
}

void AAHChase::StartChaseTimer()
{
	//Timer 측정 -> 몇초로 할까.. 일단 30초로 하자
	//30초 뒤에 End
	GetWorld()->GetTimerManager().SetTimer(ChaseTimerHandle, this, &AAHChase::ChaseTimerExpired, 20.f, false);
}

void AAHChase::EndChaseTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(ChaseTimerHandle);
}

void AAHChase::ChaseTimerExpired()
{
	//타이머 실행되면 코드 작성
	UE_LOG(LogTemp, Log, TEXT("Chase 제한 시간이 끝났습니다."));
	Cast<AAHGameMode>(GetWorld()->GetAuthGameMode())->SetGimmickMode(EGimmickMode::Patrol);
	ChasedNPCDestroy();
}

void AAHChase::ChasedNPCDestroy()
{
	if(ChasedNPC)
	{
		ChasedNPC->Destroy();
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Chased NPC Is Null"));
	}
}

