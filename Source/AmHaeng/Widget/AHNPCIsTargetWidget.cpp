// Fill out your copyright notice in the Description page of Project Settings.


#include "AHNPCIsTargetWidget.h"
#include "Components/TextBlock.h"

void UAHNPCIsTargetWidget::SetNPCIsTargetWidget(uint8 InIsTargetNPC)
{
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
}

void UAHNPCIsTargetWidget::AllTextInvisible()
{
	CorrectTargetText->SetVisibility(ESlateVisibility::Hidden);
	FailTargetText->SetVisibility(ESlateVisibility::Hidden);
}
