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
	AAHVehiclePlayerController::PlayerPawn->GetWeaponFromBP();
	ChickenBladeSkeletalMeshComponent = AAHVehiclePlayerController::PlayerPawn->GetWeaponComponent();
	if(ChickenBladeSkeletalMeshComponent)
	{
		ChickenBladeSetVisible(true);
	}
	AAHGameMode::PlayerController->ChaseMouseClickDelegate.AddUObject(this, &AAHChickenBlade::MouseDelegate);
}

void AAHChickenBlade::GetChickenComponent_Implementation()
{
}

void AAHChickenBlade::ChickenBladeDown_Implementation()
{
}

/*void AAHChickenBlade::ChickenBladeUp()
{
	UE_LOG(LogTemp, Log, TEXT("Up"));
}*/

// Called when the game starts or when spawned
void AAHChickenBlade::BeginPlay()
{
	Super::BeginPlay();
}

void AAHChickenBlade::ChickenAttackSound()
{
}

void AAHChickenBlade::ChickenBladeSetVisible(bool InVisible)
{
	if(ChickenBladeSkeletalMeshComponent)
	{
		ChickenBladeSkeletalMeshComponent->SetVisibility(InVisible);
	}
}

void AAHChickenBlade::MouseDelegate(bool IsClick)
{
	if(IsClick)
	{
		MouseClick();
	}
	else
	{
		MouseClickReleased();
	}
}

void AAHChickenBlade::MouseClick()
{
}

void AAHChickenBlade::MouseClickReleased()
{
	//아직은 사용하지 않을 예정.
	//그냥 Mouse Click 하면 내려갔다 올라오는 걸로
}


