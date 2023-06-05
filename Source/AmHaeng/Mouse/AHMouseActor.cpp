// Fill out your copyright notice in the Description page of Project Settings.


#include "AHMouseActor.h"

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
	SetCPWidget();
}

// Called when the game starts or when spawned
void AAHMouseActor::BeginPlay()
{
	Super::BeginPlay();
	
	//CPWidgetOnViewport();
	
}

// Called every frame
void AAHMouseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAHMouseActor::SetCPWidget()
{
	CPWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("CPWidgetComponent"));
	CPWidgetComponent->SetupAttachment(this->GetRootComponent());
	CPWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	CPWidgetComponent->SetWidgetClass(CPWidgetClass);
	//CPWidgetComponent->SetVisibility(false);
}

void AAHMouseActor::CPWidgetOnViewport()
{
	//class UWidgetComponent* CPWidgetComponent = NewObject<UWidgetComponent>(this);
	//CPWidgetComponent->SetWidgetClass(CPWidget->StaticClass());
	//CPWidgetComponent->SetupAttachment(GetRootComponent());
	//CPWidgetComponent->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	
}

