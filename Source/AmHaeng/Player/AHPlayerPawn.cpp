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
		UE_LOG(LogTemp,Log, TEXT("MouseClick"));
		MouseClick();
	}
	else
	{
		UE_LOG(LogTemp,Log, TEXT("MouseClick Released"));
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
		}
	}
	IsAttacking = false;
	

	AAHGameMode::PlayerController->ChaseMouseClickDelegate.AddUObject(this, &AAHPlayerPawn::MouseDelegate);
}

void AAHPlayerPawn::ChickenAttack_Implementation()
{
}

void AAHPlayerPawn::SetChickenRotate(FRotator RotateRate)
{
	UE_LOG(LogTemp, Log, TEXT("[SetChickenRotate] %s"), *RotateRate.ToString());
	ChickenBlade->SetActorRotation(OriginChickenRotation + RotateRate);
}

void AAHPlayerPawn::ChickenAttackFinish()
{
	UE_LOG(LogTemp, Log, TEXT("PlayerPawn : Chicken Attack Finish"));
	IsAttacking = false;
}

void AAHPlayerPawn::PlayerMannequinDetect()
{
	UE_LOG(LogTemp, Log, TEXT("Mannequin is Detected"));
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

UStaticMeshComponent* AAHPlayerPawn::GetMannequinDestMeshComponent()
{
	TArray<UActorComponent*> Components = this->GetComponentsByTag(UStaticMeshComponent::StaticClass(), FName(TEXT("MannequinDest")));
	UStaticMeshComponent* MannequinDestMeshComponent = nullptr;
	if(!Components.IsEmpty())
	{
		MannequinDestMeshComponent = Cast<UStaticMeshComponent>(Components[0]);
	}
	return MannequinDestMeshComponent;
}


