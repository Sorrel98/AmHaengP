// Fill out your copyright notice in the Description page of Project Settings.


#include "AHChaseGimmickManager.h"

#include "AmHaeng/Player/AHVehiclePlayerController.h"
#include "BeforeChase/AHBeforeChase.h"
#include "Chase/AHChase.h"

// Sets default values
AAHChaseGimmickManager::AAHChaseGimmickManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

}

void AAHChaseGimmickManager::StartChaseGimmick(AAHVehiclePlayerController* PC, AAHNPCVehicleBase* NPCVehicle)
{
	//처음으로 Chase Gimmick Manager가 불리는 부분(Begin Play)
	Initialize();
	ChasedNPC = NPCVehicle;
	BeforeChase->BeforeChaseProcess(PC, NPCVehicle);
	
}

void AAHChaseGimmickManager::ChaseStart()
{
	//아래 기믹은 AHChase 클래스에게 일임
	Chase->ChaseStart(ChasedNPC);
}

void AAHChaseGimmickManager::Initialize()
{
	BeforeChase = NewObject<AAHBeforeChase>();
	BeforeChase->Rename(TEXT("BeforeChaseOuter"), this);
	Chase = NewObject<AAHChase>();
	Chase->Rename(TEXT("ChaseOuter"), this);
	BeforeChase->StartChaseDelegate.BindUObject(this, &AAHChaseGimmickManager::ChaseStart);
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if(PC)
	{
		AHPC = Cast<AAHVehiclePlayerController>(PC);
	}
}


