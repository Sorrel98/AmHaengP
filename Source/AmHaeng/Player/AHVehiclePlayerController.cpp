// Fill out your copyright notice in the Description page of Project Settings.


#include "AHVehiclePlayerController.h"
#include "GameFramework/PlayerController.h"
#include "AmHaeng/Interface/AHScannable.h"
#include "EnhancedInputComponent.h"
#include "InteractiveToolManager.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"

AAHVehiclePlayerController::AAHVehiclePlayerController()
{
	bShowMouseCursor = true;
	ScanDistance = 2000.0f;
	MousePrevActor = nullptr;


	//Mouse Click Input Ref Find
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionClickRef(
		TEXT("/Script/EnhancedInput.InputAction'/Game/VehicleTemplate/Input/Actions/IA_Click.IA_Click'"));
	if (InputActionClickRef.Object != nullptr)
	{
		ClickAction = InputActionClickRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionClickReleasedRef(
		TEXT(
			"/Script/EnhancedInput.InputAction'/Game/VehicleTemplate/Input/Actions/IA_ClickReleased.IA_ClickReleased'"));
	if (InputActionClickReleasedRef.Object != nullptr)
	{
		ClickReleasedAction = InputActionClickReleasedRef.Object;
	}
}

void AAHVehiclePlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInitMousePrevActor();
}

void AAHVehiclePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MouseScan();
}

/*void AAHVehiclePlayerController::InVisiblePrevWidget(AActor* PrevActor)
{
	AAHNPCVehicleBase* HitPrevActor = Cast<AAHNPCVehicleBase>(PrevActor);
	if (HitPrevActor != nullptr)
	{
		//UE_LOG(LogTemp, Log, TEXT("기존 Widget을 끕니다"));
		HitPrevActor->SetNPCInfoWidgetVisible(false);
	}
}*/

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

void AAHVehiclePlayerController::SetInitMousePrevActor()
{
	MousePrevActor = GetPawn();
}

void AAHVehiclePlayerController::MouseScan()
{
	if (this)
	{
		FHitResult HitResult;
		this->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
		if (HitResult.bBlockingHit)
		{
			DrawShpere(HitResult);
			NowHitActor = HitResult.GetActor();
			if (NowHitActor == nullptr) return;
			if(MousePrevActor == nullptr) return;
			MousePosition = HitResult.Location;

			
			//다른 물체로 변경됨
			if(NowHitActor->GetActorLabel() != *MousePrevActor->GetActorLabel())
			{
				if (IsNPCClicking)
				{
					MouseClickReleased();
				}
				//새로운 Hit Actor가 NPC 인지 판별
				IAHScannable* IsScannable = Cast<IAHScannable>(NowHitActor);
				//Hit Actor != NPC
				if (IsScannable == nullptr)
				{
					if (IsNPCScanning)
					{
						IsNPCScanning = false;
						WidgetInVisibleByMouseScan(MousePrevActor);
					}
					MousePrevActor = NowHitActor;
				}
				//Hit Actor == NPC
				else
				{
					if(IsNPCScanning)
					{
						WidgetInVisibleByMouseScan(MousePrevActor);
					}
					//이 Pawn은 현재 주인공 Pawn
					APawn* VehiclePawn = GetPawn();
					float Distance = FVector::Distance(VehiclePawn->GetActorLocation(), NowHitActor->GetActorLocation());
					if (Distance < ScanDistance)
					{
						//기존 prev actor가 null이 아니라면 Widget 꺼줘야 해
						/*if (MousePrevActor != nullptr)
						{
							//원래 액터의 Widget을 Invisible하고
							InVisiblePrevWidget(MousePrevActor);
						}*/
						//MousePrevActor update
						MousePrevActor = NowHitActor;
						WidgetVisibleByMouseScan(NowHitActor);
						IsNPCScanning = true;
					}
				}
			}
		}
	}
}

void AAHVehiclePlayerController::WidgetVisibleByMouseScan(AActor* HitActor)
{
	//새로운 Widget Visible
	AAHNPCVehicleBase* HitActorBase = Cast<AAHNPCVehicleBase>(HitActor);
	if (HitActorBase == nullptr)
	{
		return;
	}
	HitActorBase->SetNPCInfoWidgetVisible(true);
	HitActorBase->AHSetTooltipVisible(true);
	HitActorBase->SetOutline(true);
}

void AAHVehiclePlayerController::WidgetInVisibleByMouseScan(AActor* HitActor)
{
	//새로운 Widget Visible
	AAHNPCVehicleBase* HitActorBase = Cast<AAHNPCVehicleBase>(HitActor);
	if (HitActorBase == nullptr)
	{
		return;
	}
	HitActorBase->SetNPCInfoWidgetVisible(false);
	HitActorBase->AHSetTooltipVisible(false);
	HitActorBase->SetOutline(false);
}

void AAHVehiclePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputComponent == nullptr)
	{
		return;
	}
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Triggered, this,
	                                   &AAHVehiclePlayerController::MouseClick);
	EnhancedInputComponent->BindAction(ClickReleasedAction, ETriggerEvent::Triggered, this,
	                                   &AAHVehiclePlayerController::MouseClickReleased);
}

/*const uint8 AAHVehiclePlayerController::GetIsNPCTarget()
{
	AAHNPCVehicleBase* HitActorBase = Cast<AAHNPCVehicleBase>(NowHitActor);
	if (HitActorBase)
	{
		return HitActorBase->GetIsTargetNPC();
	}
	return NULL;
}*/

void AAHVehiclePlayerController::MouseClick()
{
	//add Delegate and Start Loading UI
	if (IsNPCScanning)
	{
		IsNPCClicking = true;
		if (MouseClickDelegate.IsBound())
		{
			MouseClickDelegate.Broadcast(true);
		}
		if (NowHitActor)
		{
			AAHNPCVehicleBase* HitActorBase = Cast<AAHNPCVehicleBase>(NowHitActor);
			if (HitActorBase)
			{
				HitActorBase->AHSetTooltipVisible(false);
				if(SendNowClickNPCToGameMode.IsBound())
				{
					SendNowClickNPCToGameMode.Execute(HitActorBase);
				}
			}
		}
	}
}

void AAHVehiclePlayerController::MouseClickReleased()
{
	if (IsNPCClicking)
	{
		IsNPCClicking = false;
		//add delegate and ShutDown Loading UI
		if (MouseClickDelegate.IsBound())
		{
			MouseClickDelegate.Broadcast(false);
		}
		if (NowHitActor)
		{
			AAHNPCVehicleBase* HitActorBase = Cast<AAHNPCVehicleBase>(NowHitActor);
			if (HitActorBase)
			{
				HitActorBase->AHSetTooltipVisible(false);
			}
		}
	}
}
