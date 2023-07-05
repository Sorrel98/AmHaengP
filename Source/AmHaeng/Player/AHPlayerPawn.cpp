// Fill out your copyright notice in the Description page of Project Settings.


#include "AHPlayerPawn.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Weapon/AHChickenBlade.h"

void AAHPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	if(ChickenBladeClass)
	{
		ChickenBlade = GetWorld()->SpawnActor<AAHChickenBlade>(ChickenBladeClass);
		if(ChickenBlade)
		{
			GetSkeletalMesh();
			if(const auto BladeSocket = PlayerSkeletalMeshComponent->GetSocketByName("Blade"))
			{
				BladeSocket->AttachActor(ChickenBlade, PlayerSkeletalMeshComponent);
			}
		}
	}
}

void AAHPlayerPawn::PlayerMannequinDetect()
{
	UE_LOG(LogTemp, Log, TEXT("Mannequin is Detected"));
	if(MannequinDetect.IsBound())
	{
		MannequinDetect.Execute();
	}
}

void AAHPlayerPawn::GetWeaponFromBP_Implementation()
{
}

void AAHPlayerPawn::GetSkeletalMesh_Implementation()
{
}

USkeletalMeshComponent* AAHPlayerPawn::GetPlayerPawnSkeletalMesh()
{
	return PlayerSkeletalMeshComponent;
}

USkeletalMeshComponent* AAHPlayerPawn::GetWeaponComponent()
{
	return WeaponComponent;
}

