// Fill out your copyright notice in the Description page of Project Settings.


#include "AHNPCClickCPWidget.h"

#include "AmHaeng/Player/AHVehiclePlayerController.h"

void UAHNPCClickCPWidget::AHNPCClickCPWidget()
{
	
	//Percent = 0.3f;
}

void UAHNPCClickCPWidget::SetPercent_Implementation(const float InPercentage)
{
	//PercentValue = InPercentage;
}

const float UAHNPCClickCPWidget::GetPercent()
{
	return PercentValue;
}

void UAHNPCClickCPWidget::SetVisibility(ESlateVisibility InVisibility)
{
	Super::SetVisibility(InVisibility);
}

void UAHNPCClickCPWidget::MouseClickDelegateBind()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if(PlayerController==nullptr) return;
	if(AAHVehiclePlayerController* CastedPlayerController = CastChecked<AAHVehiclePlayerController>(PlayerController))
	{
		CastedPlayerController->MouseClickDelegate.AddUObject(this, &UAHNPCClickCPWidget::MouseClicked);
	}
}

void UAHNPCClickCPWidget::MouseClicked(bool ClickOrReleased)
{
	ScanTimer.Invalidate();
	NowClickTime = 0.0f;
	SetMouseClickTimer(ClickOrReleased);
}

void UAHNPCClickCPWidget::AddPercentageByTick()
{
	NowClickTime+=0.1f;
}


void UAHNPCClickCPWidget::NativeConstruct()
{
	Super::NativeConstruct();
	MaxClickTime = 2.0f;
	NowClickTime = 0.0f;
	MouseClickDelegateBind();
}

void UAHNPCClickCPWidget::SetMouseClickTimer(bool ClickOrReleased)
{
	//잘 들어옴

	FTimerDelegate TimerDelegate;
	//TimerDelegate.BindUFunction(this, FName("AddPercentageByTick"));
	//TimerDelegate.BindUFunction(this, FName("SetPercent_Implementation"), NowClickTime/MaxClickTime);
	
	//click 이었다면
	if(ClickOrReleased)
	{
		//타이머 시작
		GetWorld()->GetTimerManager().SetTimer(ScanTimer, TimerDelegate, MaxClickTime, false);
	}
	//release였다면
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(ScanTimer);
		NowClickTime = 0.0f;
	}
	
}
