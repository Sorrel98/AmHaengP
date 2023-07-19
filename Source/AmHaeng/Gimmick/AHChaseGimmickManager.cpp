// Fill out your copyright notice in the Description page of Project Settings.


#include "AHChaseGimmickManager.h"

#include "AfterChase/AHAfterChase.h"
#include "AmHaeng/HUD/AHHUD.h"
#include "AmHaeng/Player/AHVehiclePlayerController.h"
#include "BeforeChase/AHBeforeChase.h"
#include "Chase/AHChase.h"

// Sets default values
AAHChaseGimmickManager::AAHChaseGimmickManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AAHChaseGimmickManager::StartChaseGimmick(AAHNPCVehicleBase* NPCVehicle)
{
	//처음으로 Chase 기믹 시작할 때마다 불림
	ChasedNPC = NPCVehicle;
	BeforeChase->BeforeChaseProcess(PlayerController, NPCVehicle);
	BeforeChase->PlayChaseStartAnim();
}

void AAHChaseGimmickManager::ChaseStart()
{
	//아래 기믹은 AHChase 클래스에게 일임
	Chase->ChaseStart(ChasedNPC);
	MinimapWidget->SetNPCCursorRed(ChasedNPC);
}

void AAHChaseGimmickManager::Initialize(AAHVehiclePlayerController* PC)
{
	UE_LOG(LogTemp, Log, TEXT("AAHChaseGimmickManager::Initialize"));
	//GimmickManager 객체 셋팅(chase X)
	MinimapWidget = Cast<AAHHUD>(PC->GetHUD())->GetMinimap();
	PlayerController = PC;
	BeforeChase = NewObject<AAHBeforeChase>(this, BeforeChaseClass);
	BeforeChase->Rename(TEXT("BeforeChase"), this);
	Chase = NewObject<AAHChase>();
	Chase->Rename(TEXT("Chase"), this);
	BeforeChase->StartChaseDelegate.BindUObject(this, &AAHChaseGimmickManager::ChaseStart);
	BeforeChase->SettingChaseStartWidget();
}

/*void AAHChaseGimmickManager::DestroyChaseClasses()
{
	BeforeChase->Destroy();
	Chase->Destroy();
}*/