// Fill out your copyright notice in the Description page of Project Settings.


#include "AHVehiclePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystemInterface.h"
#include <Kismet/KismetSystemLibrary.h>
#include "GameFramework/PlayerController.h"
#include "AmHaeng/Interface/AHScannable.h"
#include "AmHaeng/Interface/AHTargetNPC.h"

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
				float Distance = FVector::Distance(VehiclePawn->GetActorLocation(), HitActor->GetActorLocation());
				if (Distance < ScanDistance) {
					UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Hit Actor Name: %s"), *HitActor->GetActorLabel()), true, true,
						FColor::Red, 1.0f, FName("HitName"));

					IAHScannable *IsScannable = Cast<IAHScannable>(HitActor);
					if (IsScannable!=nullptr)
					{
						UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Hit Actor Is Scannable: %d"), IsScannable->GetIsScannable()), true, true,
						FColor::Red, 1.0f, FName("IsScan"));
					}
					IAHTargetNPC *IsTargetNPC = Cast<IAHTargetNPC>(HitActor);
					if (IsTargetNPC!=nullptr)
					{
						UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Hit Actor Is Targetable: %d"), IsTargetNPC->GetIsTargetNPC()), true, true,
							FColor::Red, 1.0f, FName("IsTarget"));
					}
					
				}

				
			}
		}
	}
}
