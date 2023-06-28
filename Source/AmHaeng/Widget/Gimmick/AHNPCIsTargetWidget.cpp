// Fill out your copyright notice in the Description page of Project Settings.


#include "AHNPCIsTargetWidget.h"
#include "Components/TextBlock.h"

void UAHNPCIsTargetWidget::SetNPCIsTargetWidget(uint8 InIsTargetNPC)
{

	if(CorrectTargetText==nullptr || FailTargetText==nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("CorrectTargetText or FailTargetText is nullptr"));
		return;
	}
	if(InIsTargetNPC)
	{
		CorrectTargetText->SetVisibility(ESlateVisibility::Visible);
		FailTargetText->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		CorrectTargetText->SetVisibility(ESlateVisibility::Hidden);
		FailTargetText->SetVisibility(ESlateVisibility::Visible);
	}
	GetWorld()->GetTimerManager().SetTimer(WidgetInvisibleTimer, this, &UAHNPCIsTargetWidget::AllTextInvisible, 3.0f, false);
}

void UAHNPCIsTargetWidget::AllTextInvisible()
{
	CorrectTargetText->SetVisibility(ESlateVisibility::Hidden);
	FailTargetText->SetVisibility(ESlateVisibility::Hidden);
}
