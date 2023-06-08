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

	FTimerDelegate TimerDelegate;
	
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
		//TimerFinishSuccessDelegate.Execute();
		NowClickTime = 0.0f;
	}
	
}
