// Fill out your copyright notice in the Description page of Project Settings.


#include "AHMouseActor.h"

#include "AmHaeng/Player/AHVehiclePlayerController.h"
#include "Components/WidgetComponent.h"

// Sets default values
AAHMouseActor::AAHMouseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UAHNPCClickCPWidget> CPWidgetRef(TEXT("/Game/Player/Widget/WBP_ClickLoading.WBP_ClickLoading_C"));
	if(CPWidgetRef.Succeeded())
	{
		CPWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("CPWidgetComponent"));
		CPWidgetComponent->SetupAttachment(this->GetRootComponent());
		CPWidgetComponent->SetWidgetClass(CPWidgetRef.Class);
	}
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
	SetCPWidgetVisibility(false);
	if(CPWidget->GetScanTimerValid())
	{
		ClickCPLoadingDelegate.Broadcast();
	}
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

