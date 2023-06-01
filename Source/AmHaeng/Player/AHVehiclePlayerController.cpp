// Fill out your copyright notice in the Description page of Project Settings.


#include "AHVehiclePlayerController.h"
#include "GameFramework/PlayerController.h"
#include "AmHaeng/Interface/AHScannable.h"
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
}

void AAHVehiclePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MouseScan();
}

void AAHVehiclePlayerController::InVisiblePrevWidget(AActor* PrevActor)
{
	AAHNPCVehicleBase* HitPrevActor = Cast<AAHNPCVehicleBase>(PrevActor);
	if(HitPrevActor!=nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("기존 Widget을 끕니다"));
		HitPrevActor->SetNPCInfoWidgetVisible(false);
	}
}

void AAHVehiclePlayerController::DrawShpere(FHitResult HitResult)
{
	//sphere 그리기
	DrawDebugSphere(
		GetWorld(),
		HitResult.ImpactPoint,
		25.f,
		12,
		FColor::Red,
		false,
		-1.f);
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
			DrawShpere(HitResult);
			NowHitActor = HitResult.GetActor();
			if (NowHitActor==nullptr) return;
			
			//NPC가 아니면 return
			IAHScannable *IsScannable = Cast<IAHScannable>(NowHitActor);
			if (IsScannable==nullptr)
			{
				IsNPCScanning = false;
				InVisiblePrevWidget(MousePrevActor);
				MousePrevActor = NowHitActor;
				return;
			}
			IsNPCScanning = true;	
			//이 Pawn은 현재 주인공 Pawn
			APawn* VehiclePawn = GetPawn();
			float Distance = FVector::Distance(VehiclePawn->GetActorLocation(), NowHitActor->GetActorLocation());
			if (Distance < ScanDistance) {
				WidgetVisibleByMouseScan(NowHitActor);
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
			//원래 액터의 Widget을 Invisible하고
			InVisiblePrevWidget(MousePrevActor);
		}
		//변하지 않은 것이었다면 더이상의 로직은 필요없음
		else return;
	}
	//MousePrevActor update
	MousePrevActor = HitActor;
					
	//새로운 Widget Visible
	AAHNPCVehicleBase* HitActorBase = Cast<AAHNPCVehicleBase>(HitActor);
	if(HitActorBase==nullptr)return;
	HitActorBase->SetNPCInfoWidgetVisible(true);
}
