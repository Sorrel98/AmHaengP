// Fill out your copyright notice in the Description page of Project Settings.


#include "AHChickenBlade.h"

#include "AmHaeng/Game/AHGameMode.h"
#include "AmHaeng/Player/AHVehiclePlayerController.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"

// Sets default values
AAHChickenBlade::AAHChickenBlade()
{
	UE_LOG(LogTemp, Log, TEXT("Chicken Blade가 생성되었습니다"));
	
}

void AAHChickenBlade::InitChickenBlade(AAHNPCVehicleBase* ChasedNPC)
{
	if(ChasedNPC)
	{
		ChaseNPC = ChasedNPC;
		PlayerPawn = AAHVehiclePlayerController::PlayerPawn;
	}
}

void AAHChickenBlade::ChickenAttackTimeline_Implementation(AAHChickenBlade* ChickenBlade)
{
}

void AAHChickenBlade::ChickenAttackTimelineFinish()
{
	if(ChickenAttackFinishDelegate.IsBound()){
		ChickenAttackFinishDelegate.Execute();
	}
}

void AAHChickenBlade::SetChickenBladeCapsuleComponent_Implementation()
{
}



void AAHChickenBlade::SetChickenVisible(bool visible)
{
	this->SetHidden(!visible);
}

void AAHChickenBlade::ChickenAttackSound()
{
}

void AAHChickenBlade::MouseClickDelegate(bool IsClick)
{
	UE_LOG(LogTemp, Log, TEXT("Chicken Blade : Mouse Delegate %d"), IsClick);
}

void AAHChickenBlade::ChickenAttackDetect_Implementation()
{
}

