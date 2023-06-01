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
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"

AAHVehiclePlayerController::AAHVehiclePlayerController()
{
	bShowMouseCursor = true;
	ScanDistance = 2000.0f;
	MousePrevActor = nullptr;
}

void AAHVehiclePlayerController::BeginPlay()
{
	Super::BeginPlay();
	//MouseHitActorName = "DefaultHitActor";
}

void AAHVehiclePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//스캔 됐을 때 한번만 인식하는 방법 찾아보기
	MouseScan();
}

void AAHVehiclePlayerController::MouseScan()
{
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
				WidgetVisibleByMouseScan(HitActor);
				
				//만약에 가리키는 액터가 같으면
				//최초에만 Widget를 Visible 시키고 이후는 다 넘어가기
				//이 Pawn은 현재 주인공 Pawn
				APawn* VehiclePawn = GetPawn();
				float Distance = FVector::Distance(VehiclePawn->GetActorLocation(), HitActor->GetActorLocation());
				
				if (Distance < ScanDistance) {
					UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Hit Actor Name: %s"), *HitActor->GetActorLabel()), true, true,
						FColor::Red, 1.0f, FName("HitName"));

					IAHScannable *IsScannable = Cast<IAHScannable>(HitActor);
					if (IsScannable==nullptr) return;
					IAHTargetNPC *IsTargetNPC = Cast<IAHTargetNPC>(HitActor);
					if (IsTargetNPC!=nullptr)
					{
						UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Hit Actor Is Targetable: %d"), IsTargetNPC->GetIsTargetNPC()), true, true,
							FColor::Red, 1.0f, FName("IsTarget"));
					}
					//npc info widget visible
					IsScannable->SetNPCInfoWidgetVisible(true);
				}
			}
		}
	}
}

void AAHVehiclePlayerController::WidgetVisibleByMouseScan(AActor* HitActor)
{
	//기존 prev actor가 null이 아니라면 Widget 꺼줘야 해
	if(MousePrevActor!=nullptr)
	{
		//만약에 가리키는 액터가 변하면
		if(*HitActor->GetActorLabel() != *MousePrevActor->GetActorLabel())
		{
			UE_LOG(LogTemp, Log, TEXT("%s"), *HitActor->GetActorLabel());
			//원래 액터의 Widget을 Invisible하고
			AAHNPCVehicleBase* HitPrevActor = Cast<AAHNPCVehicleBase>(MousePrevActor);
			if(HitPrevActor!=nullptr)
			{
				UE_LOG(LogTemp, Log, TEXT("기존 Widget을 끕니다"));
				HitPrevActor->SetNPCInfoWidgetVisible(false);
			}
			//MousePrevActor = HitActor;
		}
		//변하지 않은 것이었다면 더이상의 로직은 필요없음
		else return;
	}
	//MousePrevActor update
	MousePrevActor = HitActor;
					
	//현재 Widget Visible
	AAHNPCVehicleBase* HitActorBase = Cast<AAHNPCVehicleBase>(HitActor);
	if(HitActorBase==nullptr)return;
	UE_LOG(LogTemp, Log, TEXT("새로운 Widget을 켭니다"));
	HitActorBase->SetNPCInfoWidgetVisible(true);
}
