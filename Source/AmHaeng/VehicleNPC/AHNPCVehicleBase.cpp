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
	
	ConstructorHelpers::FClassFinder<UAHNPCInfoWidget> NPCInfoWidgetRef(TEXT("/Game/VehicleNPC/Widget/WBP_AIInfo.WBP_AIInfo_C"));
	if(NPCInfoWidgetRef.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("NPCInfoWidgetRef.Succeeded() 성공"));
		NPCInfoWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InfoWidgetComponent"));
		NPCInfoWidgetComponent->SetWidgetClass(NPCInfoWidgetRef.Class);
		NPCInfoWidgetComponent->SetupAttachment(GetRootComponent());
		NPCInfoWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		NPCInfoWidgetComponent->SetVisibility(false);
	}
}

void AAHNPCVehicleBase::SetInfoWidgetData()
{
	NPCStat->StatsSetting();
	UUserWidget* NPCWidget = NPCInfoWidgetComponent->GetUserWidgetObject();
	if(NPCWidget == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("GetUserWidgetObject이 안됩니다"));
		return;
	}
	NPCInfoWidget = Cast<UAHNPCInfoWidget>(NPCWidget);
	if (NPCInfoWidget == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("NPCInfoWidget 캐스팅이 안됩니다"));
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
	if(NPCInfoWidgetComponent)
	{
		NPCInfoWidgetComponent->SetVisibility(visible);
	}
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

void AAHNPCVehicleBase::GoodNPCInfoSetting()
{
	bIsTargetNPC = false;

	//Stat
	NPCStat->SetOwnerName("GoodNPC");
	NPCStat->SetLicenseNumber("123_345_122");
	NPCStat->SetNPCSpeed(30, 70);
	NPCStat->SetNPCSway(20);

	//Widget
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

void AAHNPCVehicleBase::BadNPCInfoSetting()
{
	bIsTargetNPC = true;

	NPCStat->SetOwnerName("BadNPC");
	NPCStat->SetLicenseNumber("12_333_544");
	NPCStat->SetNPCSpeed(50, 120);
	NPCStat->SetNPCSway(40);

	//Widget
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
