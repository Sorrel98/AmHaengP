// Fill out your copyright notice in the Description page of Project Settings.


#include "AHNPCVehicleBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "AHNPCStatComponent.h"
#include "Components/WidgetComponent.h"
#include "AmHaeng/Widget/AHNPCInfoWidget.h"
#include "DrawDebugHelpers.h"

AAHNPCVehicleBase::AAHNPCVehicleBase()
{
	//Main Info Setting
	uint32 bIsTargetNPCPercentage = UKismetMathLibrary::RandomIntegerInRange(1, 10);
	//3:7 비율로 Target NPC Setting
	AAHNPCVehicleBase::SetIsTargetNPC((bIsTargetNPCPercentage <= 3) ? true : false);

	//attachment 없어도 됨
	NPCStat = CreateDefaultSubobject<UAHNPCStatComponent>(TEXT("NPCSTAT"));
	SetInfoWidget();

	DetectionDistance = 1000.f;
	bIsAnotherNPCForward = false;
	BrakeDistance = 10000.f;
	bIsDetected = false;
}

void AAHNPCVehicleBase::BeginPlay()
{
	Super::BeginPlay();
}

void AAHNPCVehicleBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	SetRay();
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
	ConstructorHelpers::FClassFinder<UAHNPCInfoWidget> NPCInfoWidgetRef(
		TEXT("/Game/VehicleNPC/Widget/WBP_AIInfo.WBP_AIInfo_C"));
	if (NPCInfoWidgetRef.Succeeded())
	{
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
	if (NPCWidget == nullptr)
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
	if (NPCInfoWidgetComponent)
	{
		NPCInfoWidgetComponent->SetVisibility(visible);
	}
}

void AAHNPCVehicleBase::AHSetTooltipVisible(bool visible)
{
	if (NPCInfoWidget)
	{
		NPCInfoWidget->SetTooltipVisible(visible);
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

void AAHNPCVehicleBase::SetRay()
{
	FHitResult HitResult1;
	FHitResult HitResult2;
	FHitResult HitResult3;
	FVector StartLocation1 = this->GetActorLocation() + FVector(0.0f, 0.0f, 100.f);
	FVector EndLocation1 = StartLocation1 + this->GetActorForwardVector() * DetectionDistance;
	FVector StartLocation2 = this->GetMesh()->GetSocketLocation(FName("PhysWheel_FLSocket"));
	FVector EndLocation2 = StartLocation2 + this->GetActorForwardVector() * DetectionDistance;
	FVector StartLocation3 = this->GetMesh()->GetSocketLocation(FName("PhysWheel_FRSocket"));
	FVector EndLocation3 = StartLocation3 + this->GetActorForwardVector() * DetectionDistance;


	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	bool bHit1 = GetWorld()->LineTraceSingleByChannel(HitResult1, StartLocation1, EndLocation1, ECC_Visibility, QueryParams);
	bool bHit2 = GetWorld()->LineTraceSingleByChannel(HitResult2, StartLocation2, EndLocation2, ECC_Visibility, QueryParams);
	bool bHit3 = GetWorld()->LineTraceSingleByChannel(HitResult3, StartLocation3, EndLocation3, ECC_Visibility, QueryParams);
	RayDebugDraw(StartLocation1, EndLocation1,bHit1);
	RayDebugDraw(StartLocation2, EndLocation2,bHit2);
	RayDebugDraw(StartLocation3, EndLocation3,bHit3);
	
	if (bHit1 || bHit2 || bHit3)
	{
		//충돌 감지될 때만
		AActor* HitActor1 = HitResult1.GetActor();
		AAHNPCVehicleBase* NPCActor1 = Cast<AAHNPCVehicleBase>(HitActor1);
		if(NPCActor1)
		{
			DetectNPC(NPCActor1);
		}

		//충돌 감지될 때만
		AActor* HitActor2 = HitResult2.GetActor();
		AAHNPCVehicleBase* NPCActor2 = Cast<AAHNPCVehicleBase>(HitActor2);
		if(NPCActor2)
		{
			DetectNPC(NPCActor2);
		}

		//충돌 감지될 때만
		AActor* HitActor3 = HitResult3.GetActor();
		AAHNPCVehicleBase* NPCActor3 = Cast<AAHNPCVehicleBase>(HitActor3);
		if(NPCActor3)
		{
			DetectNPC(NPCActor3);
		}
	}
}

void AAHNPCVehicleBase::RayDebugDraw(const FVector& InStartLocation, const FVector& InEndLocation, const uint8 bDetected) const
{
	FColor RayColor = (bDetected?FColor::Green : FColor::Red);
	//Debug Line
	DrawDebugLine(GetWorld(), InStartLocation, InEndLocation, RayColor, false, -1.f, 0, 2.f);
}

void AAHNPCVehicleBase::DetectNPC(AAHNPCVehicleBase* NPCActor)
{
	if(NPCActor->Tags.Contains("AIVehicle"))
	{
		float NPCDistance = FVector::Distance(this->GetOwner()->GetActorLocation(), NPCActor->GetActorLocation());
		UE_LOG(LogTemp, Log, TEXT("%f"), NPCDistance);
		bIsDetected = true;
		if(NPCDistance <= BrakeDistance)
		{
			UE_LOG(LogTemp, Warning, TEXT("[c_1] Distance : %f, Brake"), NPCDistance);
			Brake();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SlowDown"));
			SlowDown();
		}
	}
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
