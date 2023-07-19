// Fill out your copyright notice in the Description page of Project Settings.


#include "AHVehiclePlayerController.h"
#include "GameFramework/PlayerController.h"
#include "AmHaeng/Interface/NPC/AHScannable.h"
#include "EnhancedInputComponent.h"
#include "AmHaeng/Game/AHGameMode.h"
#include "EnhancedInputSubsystems.h"
#include "AmHaeng/Prop/AHTypes.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"
#include "Weapon/AHChickenBlade.h"

TObjectPtr<AAHPlayerPawn> AAHVehiclePlayerController::PlayerPawn = nullptr;
AAHVehiclePlayerController::AAHVehiclePlayerController()
{
	bShowMouseCursor = true;
	ScanDistance = 2000.0f;
	MousePrevActor = nullptr;

}

void AAHVehiclePlayerController::SetPlayerPawn()
{
	PlayerPawn = Cast<AAHPlayerPawn>(GetPawn());
}

void AAHVehiclePlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInitMousePrevActor();
}

void AAHVehiclePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(AAHGameMode::NowGimmickMode == EGimmickMode::Patrol)
	{
		MouseScan();
	}
}

void AAHVehiclePlayerController::DrawShpere(FHitResult HitResult)
{
	/*//sphere 그리기
	DrawDebugSphere(
		GetWorld(),
		HitResult.ImpactPoint,
		25.f,
		12,
		FColor::Red,
		false,
		-1.f);*/
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
			//DrawShpere(HitResult);
			NowHitActor = HitResult.GetActor();
			if (NowHitActor == nullptr) return;
			if(MousePrevActor == nullptr) return;
			MousePosition = HitResult.Location;

			
			//다른 물체로 변경됨
			if(NowHitActor != MousePrevActor)
			{
				if (IsNPCClicking)
				{
					PatrolMouseClickReleased();
				}
				//새로운 Hit Actor가 NPC 인지 판별
				IAHScannable* IsScannable = Cast<IAHScannable>(NowHitActor);
				//Hit Actor != NPC
				if (IsScannable == nullptr)
				{
					if (IsNPCScanning)
					{
						IsNPCScanning = false;
						NPCMouseUnscaned(MousePrevActor);
					}
					MousePrevActor = NowHitActor;
				}
				//Hit Actor == NPC
				else
				{
					if(IsNPCScanning)
					{
						NPCMouseUnscaned(MousePrevActor);
					}
					//이 Pawn은 현재 주인공 Pawn
					APawn* VehiclePawn = GetPawn();
					float Distance = FVector::Distance(VehiclePawn->GetActorLocation(), NowHitActor->GetActorLocation());
					if (Distance < ScanDistance)
					{
						//MousePrevActor update
						MousePrevActor = NowHitActor;
						NPCMouseScaned(NowHitActor);
						IsNPCScanning = true;
					}
				}
			}
		}
	}
}

void AAHVehiclePlayerController::NPCMouseScaned(AActor* HitActor)
{
	//새로운 Widget Visible
	AAHNPCVehicleBase* HitActorBase = Cast<AAHNPCVehicleBase>(HitActor);
	if (HitActorBase)
	{
		HitActorBase->MouseScaned();
	}
}

void AAHVehiclePlayerController::NPCMouseUnscaned(AActor* HitActor)
{
	//새로운 Widget Visible
	AAHNPCVehicleBase* HitActorBase = Cast<AAHNPCVehicleBase>(HitActor);
	if (HitActorBase)
	{
		HitActorBase->MouseUnscaned();
	}
}

void AAHVehiclePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputComponent == nullptr)
	{
		return;
	}
	//UE_LOG(LogTemp, Log, TEXT("SetupInputComponent"));
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(PatrolClickAction, ETriggerEvent::Triggered, this, &AAHVehiclePlayerController::PatrolMouseClick);
	EnhancedInputComponent->BindAction(PatrolClickReleasedAction, ETriggerEvent::Triggered, this, &AAHVehiclePlayerController::PatrolMouseClickReleased);
	EnhancedInputComponent->BindAction(ChaseClickAction, ETriggerEvent::Triggered, this, &AAHVehiclePlayerController::ChaseMouseClick);
	EnhancedInputComponent->BindAction(ChaseClickReleasedAction, ETriggerEvent::Triggered, this, &AAHVehiclePlayerController::ChaseMouseClickReleased);
}

void AAHVehiclePlayerController::PatrolMouseClick()
{
	UE_LOG(LogTemp, Log, TEXT("Patrol Click"));
	//add Delegate and Start Loading UI
	if (IsNPCScanning)
	{
		IsNPCClicking = true;
		PatrolMouseClickDelegate.Broadcast(true);
		if (NowHitActor)
		{
			AAHNPCVehicleBase* HitActorBase = Cast<AAHNPCVehicleBase>(NowHitActor);
			if (HitActorBase)
			{
				HitActorBase->AHSetTooltipVisible(false);
				ChasedNPC = HitActorBase;
				//얘는 Chase 시작할 때
				SendNowClickNPCToGameMode.Execute(HitActorBase);
			}
		}
	}
}

void AAHVehiclePlayerController::PatrolMouseClickReleased()
{
	if (IsNPCClicking)
	{
		IsNPCClicking = false;
		//add delegate and ShutDown Loading UI
		PatrolMouseClickDelegate.Broadcast(false);
		
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

void AAHVehiclePlayerController::ChaseMouseClick()
{
	ChaseMouseClickDelegate.Broadcast(true);
}

void AAHVehiclePlayerController::ChaseMouseClickReleased()
{
	ChaseMouseClickDelegate.Broadcast(false);
}

void AAHVehiclePlayerController::ChaseFinished()
{
	UE_LOG(LogTemp, Log, TEXT("Controller : Chase Finish"));
	SetPatrolIMC();
	PlayerPawn->GetChickenBlade()->SetChickenVisible(false);
	IsNPCClicking = false;
	IsNPCScanning = false;
}


void AAHVehiclePlayerController::SetPatrolIMC_Implementation()
{
}

void AAHVehiclePlayerController::SetChaseIMC_Implementation()
{
}

