// Fill out your copyright notice in the Description page of Project Settings.


#include "AHChickenBlade.h"

#include "AmHaeng/Player/AHPlayerPawn.h"
#include "AmHaeng/Player/AHVehiclePlayerController.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"

// Sets default values
AAHChickenBlade::AAHChickenBlade()
{
	UE_LOG(LogTemp, Log, TEXT("Chicken Blade가 생성되었습니다"));
}

void AAHChickenBlade::InitChickenBlade(AAHNPCVehicleBase* ChasedNPC)
{
	
}

void AAHChickenBlade::ChickenAttackTimeline_Implementation(AAHChickenBlade* ChickenBlade)
{
}

void AAHChickenBlade::ChickenAttackTimelineFinish()
{
	UE_LOG(LogTemp, Log, TEXT("Chicken : Chicken Attack Finish"));
	if(ChickenAttackFinishDelegate.IsBound())
	{UE_LOG(LogTemp, Log, TEXT("Delegate to Pawn"));
		ChickenAttackFinishDelegate.Execute();
	}
}

void AAHChickenBlade::SetChickenRotate_Implementation(float XRotateRate, AAHChickenBlade* ChickenBlade)
{
}


// Called when the game starts or when spawned
void AAHChickenBlade::BeginPlay()
{
	Super::BeginPlay();
}

void AAHChickenBlade::ChickenAttackSound()
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
