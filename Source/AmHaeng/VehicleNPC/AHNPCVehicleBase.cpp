// Fill out your copyright notice in the Description page of Project Settings.


#include "AHNPCVehicleBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "AHNPCStatComponent.h"
#include "AmHaeng/Player/AHVehiclePlayerController.h"
#include "Components/WidgetComponent.h"
#include "AmHaeng/Widget/AHNPCInfoWidget.h"

AAHNPCVehicleBase::AAHNPCVehicleBase()
{
	//Main Info Setting
	uint32 bIsTargetNPCPercentage = UKismetMathLibrary::RandomIntegerInRange(1, 10);
	//3:7 비율로 Target NPC Setting
	AAHNPCVehicleBase::SetIsTargetNPC((bIsTargetNPCPercentage <= 3) ? true : false);

	//attachment 없어도 됨
	NPCStat = CreateDefaultSubobject<UAHNPCStatComponent>(TEXT("NPCSTAT"));
	SetInfoWidget();
	SetInfoWidgetData();
}

void AAHNPCVehicleBase::BeginPlay()
{
	Super::BeginPlay();
	
	BindTTDelegate();
}


bool AAHNPCVehicleBase::GetIsTargetNPC()
{
	return bIsTargetNPC;
}

void AAHNPCVehicleBase::SetIsTargetNPC(const uint8& IsTargetNPC)
{
	bIsTargetNPC = IsTargetNPC;
}


//=================================================
//NPC Info Widget
//=================================================
void AAHNPCVehicleBase::SetInfoWidget()
{
	NPCInfoWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InfoWidgetComponent"));
	NPCInfoWidgetComponent->SetupAttachment(GetRootComponent());
	NPCInfoWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	NPCInfoWidgetComponent->SetVisibility(false);
}

void AAHNPCVehicleBase::SetInfoWidgetData()
{
	NPCInfoWidget = Cast<UAHNPCInfoWidget>(NPCInfoWidgetComponent->GetUserWidgetObject());
	if (NPCInfoWidget == nullptr)
	{
		return;
	}
	NPCInfoWidget->SetNPCOwnerName(NPCStat->GetOwnerName());
	NPCInfoWidget->SetNPCLicenseNumber(NPCStat->GetLicenseNumber());
	NPCInfoWidget->SetNPCMinSpeed(NPCStat->GetNPCMinSpeed());
	NPCInfoWidget->SetNPCMaxSpeed(NPCStat->GetNPCMaxSpeed());
	NPCInfoWidget->SetNPCSway(NPCStat->GetNPCSway());
}

void AAHNPCVehicleBase::SetNPCInfoWidgetVisible(bool visible)
{
	NPCInfoWidgetComponent->SetVisibility(visible);
}

void AAHNPCVehicleBase::AHSetTooltipVisible(bool visible)
{
	if(NPCInfoWidget)
	{
		NPCInfoWidget->SetTooltipVisible(visible);
	}
}

void AAHNPCVehicleBase::BindTTDelegate()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController == nullptr)
	{
		return;
	}
	if (AAHVehiclePlayerController* CastedPlayerController = CastChecked<AAHVehiclePlayerController>(PlayerController))
	{
		CastedPlayerController->TTDelegate.BindUObject(this, &AAHNPCVehicleBase::AHSetTooltipVisible);
	}
}
