// Fill out your copyright notice in the Description page of Project Settings.


#include "AHVehiclePlayerController.h"
#include "GameFramework/PlayerController.h"
#include "AmHaeng/Interface/AHScannable.h"
#include "EnhancedInputComponent.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"
#include "AmHaeng/Widget/AHNPCClickCPWidget.h"
#include "Components/WidgetComponent.h"

AAHVehiclePlayerController::AAHVehiclePlayerController()
{
	bShowMouseCursor = true;
	ScanDistance = 2000.0f;
	MousePrevActor = nullptr;
	

	//Mouse Click Input Ref Find
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionClickRef(TEXT("/Script/EnhancedInput.InputAction'/Game/VehicleTemplate/Input/Actions/IA_Click.IA_Click'"));
	if(InputActionClickRef.Object != nullptr)
	{
		ClickAction = InputActionClickRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionClickReleasedRef(TEXT("/Script/EnhancedInput.InputAction'/Game/VehicleTemplate/Input/Actions/IA_ClickReleased.IA_ClickReleased'"));
	if(InputActionClickReleasedRef.Object != nullptr)
	{
		ClickReleasedAction = InputActionClickReleasedRef.Object;
	}
	//NPCClickCPWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("MouseClickCPWidgetComponent"));
	//NPCClickCPWidgetComponent->SetupAttachment(GetRootComponent());

}

void AAHVehiclePlayerController::BeginPlay()
{
	Super::BeginPlay();
	if(NPCClickCPWidgetComponent)
	{
		UE_LOG(LogTemp, Log, TEXT("NPC Click Widget is here"));
	}
	//Mouse Click CP Widget Setting
	SettingCPWidget();
}

void AAHVehiclePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("Is Clicking on NPC : %d"), IsNPCClicking);
	MouseScan();

	//NPCClickCPWidgetComponent->SetWorldLocation(FVector{0.0f, 0.0f, 0.0f});
}

void AAHVehiclePlayerController::InVisiblePrevWidget(AActor* PrevActor)
{
	AAHNPCVehicleBase* HitPrevActor = Cast<AAHNPCVehicleBase>(PrevActor);
	if(HitPrevActor!=nullptr)
	{
		//UE_LOG(LogTemp, Log, TEXT("기존 Widget을 끕니다"));
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
			MousePosition = HitResult.Location;
			NowHitActor = HitResult.GetActor();
			if (NowHitActor==nullptr) return;
			
			//NPC가 아니면 return
			IAHScannable *IsScannable = Cast<IAHScannable>(NowHitActor);
			if (IsScannable==nullptr)
			{
				if(IsNPCScanning) IsNPCScanning = false;
				if(IsNPCClicking)
				{
					IsNPCClicking = false;
					//add delegate and ShutDown Loading UI
				}
				InVisiblePrevWidget(MousePrevActor);
				MousePrevActor = NowHitActor;
				return;
			}
			//이 Pawn은 현재 주인공 Pawn
			APawn* VehiclePawn = GetPawn();
			float Distance = FVector::Distance(VehiclePawn->GetActorLocation(), NowHitActor->GetActorLocation());
			if (Distance < ScanDistance) {
				IsNPCScanning = true;	
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

void AAHVehiclePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if(InputComponent==nullptr) return;
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Triggered, this, &AAHVehiclePlayerController::MouseClick);
	EnhancedInputComponent->BindAction(ClickReleasedAction, ETriggerEvent::Triggered, this, &AAHVehiclePlayerController::MouseClickReleased);
}

void AAHVehiclePlayerController::SettingCPWidget()
{
	/*if(NPCClickCPWidgetComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("NPC Click CP Widget Component"));
		NPCClickCPWidgetComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		NPCClickCPWidgetComponent->RegisterComponent();
		NPCClickCPWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		NPCClickCPWidgetComponent->SetVisibility(true);
		
		NPCClickWidget = Cast<UAHNPCClickCPWidget>(NPCClickCPWidgetComponent->GetUserWidgetObject());
		if(NPCClickWidget==nullptr) return;
	}*/
}

FVector AAHVehiclePlayerController::GetMouseLocation()
{
	return MousePosition;
}

void AAHVehiclePlayerController::MouseClick()
{
	//add Delegate and Start Loading UI
	if(IsNPCScanning)
	{
		IsNPCClicking = true;
		UE_LOG(LogTemp, Warning, TEXT("Mouse Clicked"));
	}
}

void AAHVehiclePlayerController::MouseClickReleased()
{
	IsNPCClicking = false;
	//add delegate and ShutDown Loading UI
	if(IsNPCScanning)
	{
		UE_LOG(LogTemp, Warning, TEXT("Mouse Click Released"));
	}
}
