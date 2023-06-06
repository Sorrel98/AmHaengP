// Fill out your copyright notice in the Description page of Project Settings.


#include "AHMouseActor.h"

#include "AmHaeng/Player/AHVehiclePlayerController.h"
#include "AmHaeng/Widget/AHNPCClickCPWidget.h"
#include "Components/WidgetComponent.h"

// Sets default values
AAHMouseActor::AAHMouseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UAHNPCClickCPWidget> CPWidgetRef(TEXT("/Game/Player/Widget/WBP_ClickLoading.WBP_ClickLoading_C"));
	if(CPWidgetRef.Succeeded())
	{
		CPWidgetClass = CPWidgetRef.Class;
	}
	CPWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("CPWidgetComponent"));
	CPWidgetComponent->SetupAttachment(this->GetRootComponent());
	CPWidgetComponent->SetWidgetClass(CPWidgetClass);
}

// Called when the game starts or when spawned
void AAHMouseActor::BeginPlay()
{
	Super::BeginPlay();
	
	SetCPWidgetVisibility(false);
	SetBindDelegate();
	SetCPWidget();
}


void AAHMouseActor::SetCPWidgetVisibility(bool Visible) const
{
	UE_LOG(LogTemp, Warning, TEXT("SetCP Widget Visibility Setting : %d"), Visible);
	CPWidgetComponent->SetVisibility(Visible);
}

void AAHMouseActor::SetCPWidget()
{
	CPWidgetComponent->SetCastShadow(false);
}



void AAHMouseActor::SetBindDelegate()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if(PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Binding Player Controller is variable 1 "));
		if(AAHVehiclePlayerController* CastedPlayerController = CastChecked<AAHVehiclePlayerController>(PlayerController))
		{
			UE_LOG(LogTemp, Warning, TEXT("Binding Player Controller is variable 2 "));
			
			CastedPlayerController->MouseClickDelegate.BindUObject(this, &AAHMouseActor::SetCPWidgetVisibility);
		}
	}
	
}

