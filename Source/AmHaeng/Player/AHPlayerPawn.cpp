// Fill out your copyright notice in the Description page of Project Settings.


#include "AHPlayerPawn.h"

#include "AHVehiclePlayerController.h"
#include "AmHaeng/Game/AHGameMode.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Weapon/AHChickenBlade.h"

void AAHPlayerPawn::MouseClick()
{
	if(!IsAttacking)
	{
		IsAttacking = true;
		ChickenAttack();
	}
}

void AAHPlayerPawn::MouseClickReleased()
{
}

void AAHPlayerPawn::MouseDelegate(bool IsClick)
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
			OriginChickenRotation = ChickenBlade->GetActorRotation();
			ChickenBlade->SetChickenVisible(false);
		}
	}
	IsAttacking = false;
	
	SetMannequinDestMeshComponent();
	AAHGameMode::PlayerController->ChaseMouseClickDelegate.AddUObject(this, &AAHPlayerPawn::MouseDelegate);
}

void AAHPlayerPawn::ChickenAttack_Implementation()
{
}

void AAHPlayerPawn::SetChickenRotate(FRotator RotateRate)
{
	ChickenBlade->SetActorRotation(OriginChickenRotation + RotateRate);
}

void AAHPlayerPawn::ChickenAttackFinish()
{
	IsAttacking = false;
}

void AAHPlayerPawn::PlayerMannequinDetect()
{
	if(MannequinDetect.IsBound())
	{
		MannequinDetect.Execute();
	}
}

void AAHPlayerPawn::GetSkeletalMesh_Implementation()
{
}

USkeletalMeshComponent* AAHPlayerPawn::GetPlayerPawnSkeletalMesh()
{
	return PlayerSkeletalMeshComponent;
}

void AAHPlayerPawn::SetChickenVisible(bool Invisible)
{
	if(ChickenBlade)
	{
		ChickenBlade->SetChickenVisible(Invisible);
	}
}

void AAHPlayerPawn::SetInputEnable()
{
	AAHGameMode::PlayerController->EnableInput(AAHGameMode::PlayerController);
	this->EnableInput(AAHGameMode::PlayerController);
}

void AAHPlayerPawn::SetMannequinDestMeshComponent_Implementation()
{
}

