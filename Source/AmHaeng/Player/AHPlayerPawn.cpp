// Fill out your copyright notice in the Description page of Project Settings.


#include "AHPlayerPawn.h"

#include "AHVehiclePlayerController.h"
#include "AmHaeng/Game/AHGameMode.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Weapon/AHChickenBlade.h"

uint32 AAHPlayerPawn::Reputation = 30;

void AAHPlayerPawn::MouseClick_Implementation()
{
}

void AAHPlayerPawn::MouseClickReleased()
{
}

void AAHPlayerPawn::ChaseMouseDelegate(bool IsClick)
{
	
	if(IsClick)
	{
		UE_LOG(LogTemp,Log, TEXT("[Chase] Mouse Click"));
		MouseClick();
	}
	else
	{
		MouseClickReleased();
	}
}

void AAHPlayerPawn::ChaseMouseDelegateBind()
{
	if(AAHGameMode::PlayerController)
	{
		AAHGameMode::PlayerController->ChaseMouseClickDelegate.AddUObject(this, &AAHPlayerPawn::ChaseMouseDelegate);
		UE_LOG(LogTemp, Log, TEXT("Player Controller is there? : %s"), *AAHGameMode::PlayerController->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Player Controller 없음"));
	}
	
}

void AAHPlayerPawn::SpawnChickenBlade()
{
	if(ChickenBladeClass)
	{
		ChickenBlade = GetWorld()->SpawnActor<AAHChickenBlade>(ChickenBladeClass);
		ChickenBlade->ChickenAttackFinishDelegate.BindUObject(this, &AAHPlayerPawn::ChickenAttackFinish);
		if(ChickenBlade)
		{
			SetSkeletalMesh();
			if(const auto BladeSocket = PlayerSkeletalMeshComponent->GetSocketByName("Blade"))
			{
				BladeSocket->AttachActor(ChickenBlade, PlayerSkeletalMeshComponent);
			}
			ChickenBlade->SetChickenBladeCapsuleComponent();
			ChickenBladeCapsuleComponent = ChickenBlade->GetChickenBladeCapsuleComponent();
			ChickenBlade->SetChickenVisible(false);
		}
	}
}

void AAHPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	PlayerNowSpeed = 0;
	SpawnChickenBlade();
	IsChickenRotating = false;
	
	SetMannequinDestMeshComponent();
	/*UE_LOG(LogTemp, Log, TEXT("Chase Mouse Click Delegate Start"));
	ChaseMouseDelegateBind();
	UE_LOG(LogTemp, Log, TEXT("Chase Mouse Click Delegate End"));*/
	AAHPlayerPawn::Reputation = 30;
}

void AAHPlayerPawn::SetNowSpeedFromBP_Implementation()
{
}

void AAHPlayerPawn::ChickenRotation_Implementation()
{
}

void AAHPlayerPawn::SetChickenRotate(FRotator RotateRate)
{
	ChickenBlade->SetActorRelativeRotation(RotateRate);
}

void AAHPlayerPawn::ChickenAttackFinish()
{
	IsChickenRotating = false;
}

void AAHPlayerPawn::PlayerMannequinDetect()
{
	MannequinDetect.Execute();
}

void AAHPlayerPawn::SetSkeletalMesh_Implementation()
{
}

USkeletalMeshComponent* AAHPlayerPawn::GetPlayerPawnSkeletalMesh()
{
	return PlayerSkeletalMeshComponent;
}

void AAHPlayerPawn::SetChickenVisible(bool Visible)
{
	if(ChickenBlade)
	{
		ChickenBlade->SetChickenVisible(Visible);
	}
}

void AAHPlayerPawn::RaisingReputation()
{
	Reputation+=10;
	UE_LOG(LogTemp, Log, TEXT("RaisingReputation : %d"), Reputation);
	//Delegate로 위젯에 reputation 변경 알림
	//ReputationChangeDelegate.Broadcast(Reputation);
}

void AAHPlayerPawn::DecreasingReputation()
{
	Reputation-=10;
	UE_LOG(LogTemp, Log, TEXT("DecreasingReputation : %d"), Reputation);
	//Delegate로 위젯에 reputation 변경 알림
	//ReputationChangeDelegate.Broadcast(Reputation);
}

void AAHPlayerPawn::Brake_Implementation()
{
}

void AAHPlayerPawn::SetMannequinDestMeshComponent_Implementation()
{
}