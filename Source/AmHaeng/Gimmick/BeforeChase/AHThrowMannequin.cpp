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
	ThrowSpeed = 7'000'000.0f;
	if(From && To)
	{
		UCameraComponent* PlayerCamera = Cast<UCameraComponent>(To->GetRootComponent()->GetChildComponent(0)->GetChildComponent(0));
		if(PlayerCamera)
		{
			FVector ThrowDirection = PlayerCamera->GetComponentLocation() - From->GetActorLocation() + FVector{0.0f, 0.0f, 10.f};
			//DrawDebugLine(GetWorld(), From->GetActorLocation(), To->GetActorLocation(), FColor::Purple, 1.0f);
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

