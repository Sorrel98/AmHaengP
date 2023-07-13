// Fill out your copyright notice in the Description page of Project Settings.


#include "AHMouseActor.h"

#include "AmHaeng/Player/AHVehiclePlayerController.h"
#include "Components/WidgetComponent.h"

// Sets default values
AAHMouseActor::AAHMouseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CPWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("CPWidgetComponent"));
	CPWidgetComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AAHMouseActor::BeginPlay()
{
	Super::BeginPlay();
	SetBindDelegate();
	InitCPWidget();
}


void AAHMouseActor::SetCPWidgetVisibility(bool Visible) const
{
	CPWidgetComponent->SetVisibility(Visible);
}

void AAHMouseActor::InitCPWidget()
{
	CPWidgetComponent->SetCastShadow(false);
	SetCPWidgetVisibility(false);
}

void AAHMouseActor::ClickTimerFinishDelegateBind()
{
	if(CPWidget->GetScanTimerValid())
	{
		ClickCPLoadingDelegate.Broadcast();
	}
	SetCPWidgetVisibility(false);
}


void AAHMouseActor::SetBindDelegate()
{
	//클릭 유무 delegate with controller
	if(AAHGameMode::PlayerController)
	{
		AAHGameMode::PlayerController->PatrolMouseClickDelegate.AddUObject(this, &AAHMouseActor::SetCPWidgetVisibility);
	}

	//timer 끝남 delegate with click cp widget
	CPWidget = Cast<UAHNPCClickCPWidget>(CPWidgetComponent->GetWidget());
	if(CPWidget!=nullptr)
	{
		CPWidget->TimerFinishSuccessDelegate.BindUObject(this, &AAHMouseActor::ClickTimerFinishDelegateBind);
	}
}

