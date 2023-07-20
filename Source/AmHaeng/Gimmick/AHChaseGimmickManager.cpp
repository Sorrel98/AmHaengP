// Fill out your copyright notice in the Description page of Project Settings.


#include "AHChaseGimmickManager.h"

#include "AmHaeng/HUD/AHHUD.h"
#include "AmHaeng/Player/AHVehiclePlayerController.h"
#include "AmHaeng/Widget/Minimap/AHMinimapWidget.h"
#include "BeforeChase/AHBeforeChase.h"
#include "Chase/AHChase.h"

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
	UE_LOG(LogTemp, Log, TEXT("1"));
	PlayerController = PC;
	UE_LOG(LogTemp, Log, TEXT("2"));
	
	BeforeChase = NewObject<AAHBeforeChase>(this, BeforeChaseClass);
	UE_LOG(LogTemp, Log, TEXT("3"));
	BeforeChase->Rename(TEXT("BeforeChase"), this);
	UE_LOG(LogTemp, Log, TEXT("4"));
	BeforeChase->StartChaseDelegate.BindUObject(this, &AAHChaseGimmickManager::ChaseStart);
	UE_LOG(LogTemp, Log, TEXT("5"));
	BeforeChase->SettingChaseStartWidget();
	UE_LOG(LogTemp, Log, TEXT("6"));
	Chase = NewObject<AAHChase>();
	UE_LOG(LogTemp, Log, TEXT("7"));
	Chase->Rename(TEXT("Chase"), this);
	UE_LOG(LogTemp, Log, TEXT("8"));

}