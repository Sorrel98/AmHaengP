// Fill out your copyright notice in the Description page of Project Settings.


#include "AHNPCVehicleBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "AmHaeng/VehicleNPC/Stat/AHNPCStatComponent.h"
#include "Components/WidgetComponent.h"
#include "AmHaeng/Widget/NPC/AHNPCInfoWidget.h"
#include "DrawDebugHelpers.h"
#include "AmHaeng/Widget/NPC/AHNPCHPWidget.h"

/*AAHNPCVehicleBase::AAHNPCVehicleBase()
{

}*/


AAHNPCVehicleBase::AAHNPCVehicleBase()
{
	//Debug 위해 모든 NPC target

	//attachment 없어도 됨
	NPCStat = CreateDefaultSubobject<UAHNPCStatComponent>(TEXT("NPCSTAT"));
	NPCStat->ZeroHPDelegateToNPC.AddUObject(this, &AAHNPCVehicleBase::BroadCastNPCArrestedDelegate);
	SetInfoWidget();
	SetHPWidget();

	DetectionDistance = 1000.f;
	bIsAnotherNPCForward = false;
	BrakeDistance = 10000.f;
	bIsDetected = false;
	bIsChased = false;
}

void AAHNPCVehicleBase::BeginPlay()
{
	Super::BeginPlay();
	SetNPCHPWidget();
}

void AAHNPCVehicleBase::BroadCastNPCArrestedDelegate()
{
	UE_LOG(LogTemp, Log, TEXT("NPCVehicleBase : NPC Arresting"));
	//NPC 체포 성공 GameMode에게 알림
	NPCArrestedDelegate.Broadcast(true);
}

void AAHNPCVehicleBase::AHSetMaxEngineTorque_Implementation(float InMaxTorque)
{
}

void AAHNPCVehicleBase::AHDestroyFrontSphere_Implementation()
{
}

bool AAHNPCVehicleBase::GetIsTargetNPC()
{
	return bIsTargetNPC;
}

void AAHNPCVehicleBase::SetIsTargetNPC(const uint8& IsTargetNPC)
{
	bIsTargetNPC = IsTargetNPC;
}

void AAHNPCVehicleBase::SetMassOne()
{
	this->GetMesh()->SetSimulatePhysics(false);
	// 물리 시뮬레이션 컴포넌트 가져오기
	UMeshComponent* RC = Cast<UMeshComponent>(GetRootComponent());
	if (RC)
	{
		float NewMassScale = 0.000000000000000000000000000000001f; // 변경할 무게 비율
		RC->SetMassScale(NAME_None, NewMassScale);
	}
	this->GetMesh()->SetSimulatePhysics(true);
}


//=================================================
//NPC Info Widget
//=================================================
void AAHNPCVehicleBase::SetInfoWidget()
{
	NPCInfoWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InfoWidgetComponent"));
	NPCInfoWidgetComponent->SetWidgetClass(NPCInfoWidgetClass);
	NPCInfoWidgetComponent->SetupAttachment(GetRootComponent());
	NPCInfoWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	NPCInfoWidgetComponent->SetVisibility(false);
}

void AAHNPCVehicleBase::SetNPCHPWidget()
{
	UUserWidget* UserWidget = NPCHPWidgetComponent->GetUserWidgetObject();
	if(UserWidget)
	{
		NPCHPWidget = Cast<UAHNPCHPWidget>(UserWidget);
	}
}

void AAHNPCVehicleBase::SetHPWidget()
{
	NPCHPWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPWidgetComponent"));
	NPCHPWidgetComponent->SetupAttachment(GetRootComponent());
	NPCHPWidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
	NPCHPWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	NPCHPWidgetComponent->SetDrawSize(FVector2d(150.f, 50.f));
	NPCHPWidgetComponent->SetVisibility(false);
}

//Stat 정보를 갖고 Widget 값을 셋팅합니다
void AAHNPCVehicleBase::SetNPCStatAndInfoWidget(int32 NPCID)
{
	NPCStat->StatsSetting(NPCID, bIsTargetNPC);
	UUserWidget* NPCWidget = NPCInfoWidgetComponent->GetUserWidgetObject();
	if (NPCWidget)
	{
		NPCInfoWidget = Cast<UAHNPCInfoWidget>(NPCWidget);
		if (NPCInfoWidget)
		{
			NPCInfoWidget->SetNPCOwnerName(NPCStat->GetOwnerName());
			NPCInfoWidget->SetNPCLicenseNumber(NPCStat->GetLicenseNumber());
			NPCInfoWidget->SetNPCMinSpeed(NPCStat->GetNPCMinSpeed());
			NPCInfoWidget->SetNPCMaxSpeed(NPCStat->GetNPCMaxSpeed());
			NPCInfoWidget->SetNPCSway(NPCStat->GetNPCSway());
		}
	}
}

void AAHNPCVehicleBase::SetNPCInfoWidgetVisible(bool visible)
{
	if (NPCInfoWidgetComponent)
	{
		NPCInfoWidgetComponent->SetVisibility(visible);
	}
}



void AAHNPCVehicleBase::AHSetTooltipVisible(bool visible) const
{
	if (NPCInfoWidget)
	{
		NPCInfoWidget->SetTooltipVisible(visible);
	}
}


void AAHNPCVehicleBase::TESTGoodNPCInfoSetting()
{
	bIsTargetNPC = false;

	//Stat
	NPCStat->SetOwnerName("GoodNPC");
	//NPCStat->SetLicenseNumber("123_345_122");
	//NPCStat->SetNPCSpeed(30, 70);
	//NPCStat->SetGoodSway(20);

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

void AAHNPCVehicleBase::TESTBadNPCInfoSetting()
{
	bIsTargetNPC = true;

	NPCStat->SetOwnerName("BadNPC");
	//NPCStat->SetLicenseNumber("12_333_544");
	//NPCStat->SetNPCSpeed(50, 120);
	//NPCStat->SetGoodSway(40);

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

void AAHNPCVehicleBase::SetIsChased(bool IsChased)
{
	bIsChased = IsChased;
	NPCHPWidgetComponent->SetVisibility(true);
}

void AAHNPCVehicleBase::NPCHPDown()
{
	if(NPCStat)
	{
		UE_LOG(LogTemp, Log, TEXT("Groggy Gage Down"));
		NPCStat->NPCHPDown();
		if(NPCHPWidget)
		{
			if(KINDA_SMALL_NUMBER < NPCStat->GetNPCHP())
			{
				NPCHPWidget->SetNPCHP(NPCStat->GetNPCHP());
			}
			else
			{
				NPCHPWidget->SetNPCHP(0);
			}
		}
		/*else
		{
			UE_LOG(LogTemp, Log, TEXT("NPCHPWidget is null"));
		}*/
	}
}


void AAHNPCVehicleBase::DetectNothing_Implementation()
{
}


void AAHNPCVehicleBase::Brake_Implementation()
{
}

void AAHNPCVehicleBase::SlowDown_Implementation()
{
}


void AAHNPCVehicleBase::SetOutline_Implementation(bool bOutlineEnabled)
{
}
