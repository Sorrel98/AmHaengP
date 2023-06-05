// Fill out your copyright notice in the Description page of Project Settings.


#include "AHMouseActor.h"

#include "AmHaeng/Widget/AHNPCClickCPWidget.h"

// Sets default values
AAHMouseActor::AAHMouseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UAHNPCClickCPWidget> CPWidgetRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Player/Widget/WBP_ClickLoading.WBP_ClickLoading_C'"));
	if(CPWidgetRef.Succeeded())
	{
		CPWidgetClass = CPWidgetRef.Class;
	}
}

// Called when the game starts or when spawned
void AAHMouseActor::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AAHMouseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAHMouseActor::CPWidgetOnViewport()
{
	if(IsValid(CPWidgetClass))
	{
		CPWidget = Cast<UAHNPCClickCPWidget>(CreateWidget(GetWorld(), CPWidgetClass));
		if(IsValid(CPWidget))
		{
			CPWidget->AddToViewport();
		}
	}
}

