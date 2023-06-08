// Fill out your copyright notice in the Description page of Project Settings.


#include "AHNPCVehicleBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "AHNPCStatComponent.h"
#include "Components/WidgetComponent.h"
#include "AmHaeng/Widget/AHNPCInfoWidget.h"

AAHNPCVehicleBase::AAHNPCVehicleBase()
{
	//Main Info Setting
	uint32 bIsTargetNPCPercentage = UKismetMathLibrary::RandomIntegerInRange(1, 10);
	bIsTargetNPC = (bIsTargetNPCPercentage<=3)? true:false;

	//ingame 위치값이 필요한 애는 아니라서 attachment 없어도 됨
	NPCStat = CreateDefaultSubobject<UAHNPCStatComponent>(TEXT("NPCSTAT"));
	SetInfoWidget();
	
}

void AAHNPCVehicleBase::BeginPlay()
{
	Super::BeginPlay();
	SetInfoWidgetData();
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
	UAHNPCInfoWidget* NPCInfoWidget = Cast<UAHNPCInfoWidget>(NPCInfoWidgetComponent->GetUserWidgetObject());
	if(NPCInfoWidget==nullptr) return;
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
