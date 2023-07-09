// Fill out your copyright notice in the Description page of Project Settings.


#include "AHChickenBlade.h"

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

void AAHChickenBlade::SetChickenRotate_Implementation(float XRotateRate, AAHChickenBlade* ChickenBlade)
{
}


void AAHChickenBlade::SetChickenVisible(bool visible)
{
	if(!visible)
	{
		this->SetHidden(true);
	}
	else
	{
		this->SetHidden(false);
	}
}

void AAHChickenBlade::ChickenAttackSound()
{
}

void AAHChickenBlade::ChickenAttackDetect_Implementation()
{
	
}

/*void AAHChickenBlade::MouseClick()
{
	UE_LOG(LogTemp, Log, TEXT("[Chicken] MouseClick Function"));
	ChickenBladeDown();
}

void AAHChickenBlade::MouseClickReleased()
{
	//아직은 사용하지 않을 예정.
	//그냥 Mouse Click 하면 내려갔다 올라오는 걸로
}*/
