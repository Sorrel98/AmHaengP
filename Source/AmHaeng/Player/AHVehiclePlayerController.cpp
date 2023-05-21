// Fill out your copyright notice in the Description page of Project Settings.


#include "AHVehiclePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystemInterface.h"
#include <Kismet/KismetSystemLibrary.h>
#include "GameFramework/PlayerController.h"

AAHVehiclePlayerController::AAHVehiclePlayerController()
{
	bShowMouseCursor = true;
	ScanDistance = 2000.0f;
}

void AAHVehiclePlayerController::BeginPlay()
{
	Super::BeginPlay();
	/*
	APlayerController* PlayerController = CastChecked<APlayerController>(this);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer());
	
	if (nullptr != Subsystem)
	{
		Subsystem->AddMappingContext(DefaultContext, 0);
	}*/


}

void AAHVehiclePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	APlayerController* ABPlayerVehicleController = this;
	if (this)
	{
		FHitResult HitResult;
		this->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
		if (HitResult.bBlockingHit)
		{
			DrawDebugSphere(
				GetWorld(),
				HitResult.ImpactPoint,
				25.f,
				12,
				FColor::Red,
				false,
				-1.f);
			
			if (AActor* HitActor = HitResult.GetActor())
			{
				APawn* VehiclePawn = GetPawn();
				check(VehiclePawn);
				float Distance = FVector::Distance(VehiclePawn->GetActorLocation(), HitActor->GetActorLocation());

				if (Distance < ScanDistance) {
					FString HitName = *HitActor->GetName();
					if (HitName.Contains(TEXT("AH_VehicleAI")))
					{
						UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Hit Actor Name: %s"), *HitActor->GetActorLabel()), true, true,
							FColor::Red, 1.0f, FName(HitName));
						/*GEngine->AddOnScreenDebugMessage(-1, 0.05f, FColor::Red, FString::Printf(TEXT("Hit Actor Name: %s"), *HitActor->GetActorLabel()));
						UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"),
							HitResult.ImpactPoint.X,
							HitResult.ImpactPoint.Y,
							HitResult.ImpactPoint.Z);*/
					}
				}

				
			}
		}
	}
}
