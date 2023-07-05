// Fill out your copyright notice in the Description page of Project Settings.


#include "AHNPCClickCPWidget.h"
#include "AmHaeng/Player/AHVehiclePlayerController.h"

void UAHNPCClickCPWidget::AHNPCClickCPWidget()
{
}

void UAHNPCClickCPWidget::SetPercent_Implementation(const float InPercentage)
{
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
	if (PlayerController == nullptr)
	{
		return;
	}
	if (AAHVehiclePlayerController* CastedPlayerController = CastChecked<AAHVehiclePlayerController>(PlayerController))
	{
		CastedPlayerController->PatrolMouseClickDelegate.AddUObject(this, &UAHNPCClickCPWidget::MouseClicked);
	}
}

void UAHNPCClickCPWidget::MouseClicked(bool ClickOrReleased)
{
	ScanTimer.Invalidate();
	NowClickTime = 0.0f;
	SetMouseClickTimer(ClickOrReleased);
}

int8 UAHNPCClickCPWidget::GetScanTimerValid()
{
	return (ScanTimer.IsValid()? true : false);
}


void UAHNPCClickCPWidget::NativeConstruct()
{
	Super::NativeConstruct();
	MaxClickTime = 1.0f;
	NowClickTime = 0.0f;
	MouseClickDelegateBind();
}

void UAHNPCClickCPWidget::SetMouseClickTimer(bool ClickOrReleased)
{
	//잘 들어옴

	//click 이었다면
	if (ClickOrReleased)
	{
		//타이머 시작
		GetWorld()->GetTimerManager().SetTimer(ScanTimer, TimerFinishSuccessDelegate, MaxClickTime, false);
	}
	//release였다면
	else
	{
		ScanTimer.Invalidate();
		NowClickTime = 0.0f;
	}
}
