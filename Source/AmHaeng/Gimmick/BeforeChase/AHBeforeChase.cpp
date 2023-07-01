// Fill out your copyright notice in the Description page of Project Settings.


#include "AHBeforeChase.h"

#include "AmHaeng/Player/AHVehiclePlayerController.h"
#include "AmHaeng/Widget/Gimmick/BeforeChase/AHChaseStartWidget.h"

UAHBeforeChase::UAHBeforeChase()
{
	static ConstructorHelpers::FClassFinder<UAHChaseStartWidget> ChaseStartRef(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_ChaseStartCutscene.WBP_ChaseStartCutscene_C'"));
	if (ChaseStartRef.Succeeded())
	{
		UE_LOG(LogTemp, Log, TEXT("ChaseStartREf"));
		ChaseStartWidgetClass = ChaseStartRef.Class;
	}
	
}


void UAHBeforeChase::BeforeChaseProcess(AAHVehiclePlayerController* InPC)
{
	UE_LOG(LogTemp, Log, TEXT("Before Chase Class"));
	if(ChaseStartWidgetClass)
	{
		PlayChaseStartWidget();
	}
	PC = InPC;
	//GamePasue 풀고
	
	//ThrowMannequin
	
	//Camera Shake + Crash Widget
}

void UAHBeforeChase::PlayChaseStartWidget()
{
	if(ChaseStartWidgetClass)
	{
		UE_LOG(LogTemp, Log, TEXT("ChaseStartWidgetClass Is Valid"));
		if(GetWorld())
		{
			UE_LOG(LogTemp, Log, TEXT("GetWorld Is Valid"));
			ChaseStartWidget = Cast<UAHChaseStartWidget>(CreateWidget(GetWorld(), ChaseStartWidgetClass));
			if(IsValid(ChaseStartWidget))
			{
				ChaseStartWidget->SendToBeforeChaseClass.BindUObject(this, &UAHBeforeChase::FinishChaseStartWidget);
				ChaseStartWidget->AddToViewport();
				ChaseStartWidget->PlayAnims();
			}
		}
		
	}
}

void UAHBeforeChase::FinishChaseStartWidget()
{
	UE_LOG(LogTemp, Log, TEXT("BeforeCHase CLass에서 전달받았습니다"));
	SetPause(false);
}

void UAHBeforeChase::SetPause(bool InPause)
{
	PC->SetPause(InPause);
	//todo:여기까지 구현됨
}
