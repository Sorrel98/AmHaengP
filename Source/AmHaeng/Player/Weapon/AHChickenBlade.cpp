// Fill out your copyright notice in the Description page of Project Settings.


#include "AHChickenBlade.h"

#include "AmHaeng/Game/AHGameMode.h"
#include "AmHaeng/Player/AHVehiclePlayerController.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"

void AAHChickenBlade::BeginPlay()
{
	Super::BeginPlay();
	SetChickenMesh();
	SetChickenBladeCapsuleComponent();
}

void AAHChickenBlade::InitChickenBlade(AAHNPCVehicleBase* ChasedNPC)
{
	if(ChasedNPC)
	{
		ChaseNPC = ChasedNPC;
		PlayerPawn = AAHVehiclePlayerController::PlayerPawn;

	}
}

/*void AAHChickenBlade::ChickenAttackTimeline_Implementation(AAHChickenBlade* ChickenBlade)
{
}

void AAHChickenBlade::ChickenAttackTimelineFinish()
{
	ChickenAttackFinishDelegate.Execute();
}*/

void AAHChickenBlade::SetChickenMesh_Implementation()
{
}

void AAHChickenBlade::SetChickenBladeCapsuleComponent_Implementation()
{
}



void AAHChickenBlade::SetChickenVisible(bool Visible)
{
	//여기까지 log 찍힘
	UE_LOG(LogTemp, Log, TEXT("SetChickenVisible : %d"), Visible);
	if(Visible == false)
	{
		if(ChickenSkeletal)
		{
			ChickenSkeletal->SetVisibility(false);
		}
		if(CapsuleComponent)
		{
			CapsuleComponent->SetVisibility(false);
			CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
	else
	{
		if(ChickenSkeletal)
		{
			ChickenSkeletal->SetVisibility(true);
		}
		if(CapsuleComponent)
		{
			CapsuleComponent->SetVisibility(true);
			CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
	}
}

void AAHChickenBlade::ChickenAttackSound()
{
}

void AAHChickenBlade::MouseClickDelegate(bool IsClick)
{
	UE_LOG(LogTemp, Log, TEXT("Chicken Blade : Mouse Delegate %d"), IsClick);
}

/*void AAHChickenBlade::ChickenAttackDetect_Implementation()
{
}*/

