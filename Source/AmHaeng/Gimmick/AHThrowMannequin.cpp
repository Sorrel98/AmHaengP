// Fill out your copyright notice in the Description page of Project Settings.


#include "AHThrowMannequin.h"
#include "Components/SkeletalMeshComponent.h"

#include "AHMannequin.h"
#include "WheeledVehiclePawn.h"
#include "Camera/CameraComponent.h"

class AAHMannequin;
// Sets default values
AAHThrowMannequin::AAHThrowMannequin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	
}

void AAHThrowMannequin::Throw(AActor* From, AActor* To, AAHMannequin* Mannequin)
{
	ThrowSpeed = 18000000.0f;
	if(From && To)
	{
		AWheeledVehiclePawn* PlayerPawn = Cast<AWheeledVehiclePawn>(To);
		UCameraComponent* PlayerCamera = Cast<UCameraComponent>(PlayerPawn->GetRootComponent()->GetChildComponent(0)->GetChildComponent(0));
		if(PlayerCamera)
		{
			FVector ThrowDirection = PlayerCamera->GetComponentLocation() - From->GetActorLocation();
			//DrawDebugLine(GetWorld(), From->GetActorLocation(), To->GetActorLocation(), FColor::Purple);
			ThrowDirection.Normalize();
			FVector Force = ThrowDirection*ThrowSpeed;
			USkeletalMeshComponent* MannequinSkeletalMeshComponent = Cast<USkeletalMeshComponent>(Mannequin->GetSkeletalMeshComponent());
			if(MannequinSkeletalMeshComponent)
			{
				MannequinSkeletalMeshComponent->AddForce(Force);
			}
		}
	}
}
