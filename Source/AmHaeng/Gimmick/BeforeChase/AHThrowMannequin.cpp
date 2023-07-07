// Fill out your copyright notice in the Description page of Project Settings.


#include "AHThrowMannequin.h"
#include "Components/SkeletalMeshComponent.h"

#include "AHMannequin.h"
#include "WheeledVehiclePawn.h"
#include "AmHaeng/Player/AHPlayerPawn.h"
#include "Camera/CameraComponent.h"

class AAHMannequin;
// Sets default values
AAHThrowMannequin::AAHThrowMannequin()
{
}

void AAHThrowMannequin::Throw(AActor* From, AAHPlayerPawn* To, AAHMannequin* Mannequin)
{
	ThrowSpeed = 3'000'000.0f;
	if(From && To)
	{
		UStaticMeshComponent* MannequinMeshComponent = To->GetMannequinTarget();
		if(MannequinMeshComponent)
		{
			FVector ThrowDirection = MannequinMeshComponent->GetComponentLocation() - From->GetActorLocation();
			ThrowDirection.Normalize();
			FVector Force = ThrowDirection * ThrowSpeed;
			USkeletalMeshComponent* MannequinSkeletalMeshComponent = Cast<USkeletalMeshComponent>(Mannequin->GetSkeletalMeshComponent());
			if(MannequinSkeletalMeshComponent)
			{
				MannequinSkeletalMeshComponent->AddForce(Force);
			}
		}
	}
}

