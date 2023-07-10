// Fill out your copyright notice in the Description page of Project Settings.


#include "AHPlayerPawn.h"

#include "AHVehiclePlayerController.h"
#include "AmHaeng/Game/AHGameMode.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Weapon/AHChickenBlade.h"

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

void AAHPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	if(ChickenBladeClass)
	{
		ChickenBlade = GetWorld()->SpawnActor<AAHChickenBlade>(ChickenBladeClass);
		ChickenBlade->ChickenAttackFinishDelegate.BindUObject(this, &AAHPlayerPawn::ChickenAttackFinish);
		if(ChickenBlade)
		{
			GetSkeletalMesh();
			if(const auto BladeSocket = PlayerSkeletalMeshComponent->GetSocketByName("Blade"))
			{
				BladeSocket->AttachActor(ChickenBlade, PlayerSkeletalMeshComponent);
			}
			ChickenBlade->SetChickenBladeCapsuleComponent();
			ChickenBladeCapsuleComponent = ChickenBlade->GetChickenBladeCapsuleComponent();
			ChickenBlade->SetChickenVisible(false);
		}
	}
	IsChickenRotating = false;
	
	SetMannequinDestMeshComponent();
	AAHGameMode::PlayerController->ChaseMouseClickDelegate.AddUObject(this, &AAHPlayerPawn::ChaseMouseDelegate);
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

void AAHPlayerPawn::GetSkeletalMesh_Implementation()
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

/*void AAHPlayerPawn::SetInputEnable()
{
	AAHGameMode::PlayerController->EnableInput(AAHGameMode::PlayerController);
	this->EnableInput(AAHGameMode::PlayerController);
}


void AAHPlayerPawn::SetChickenCapsuleComponent_Implementation()
{
}*/
void AAHPlayerPawn::Brake_Implementation()
{
}

void AAHPlayerPawn::SetMannequinDestMeshComponent_Implementation()
{
}

