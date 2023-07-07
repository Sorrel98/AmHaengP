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
