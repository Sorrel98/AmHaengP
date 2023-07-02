// Fill out your copyright notice in the Description page of Project Settings.


#include "AHChase.h"

#include "NPCTeleport/AHNPCTeleport.h"

// Sets default values
AAHChase::AAHChase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
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

