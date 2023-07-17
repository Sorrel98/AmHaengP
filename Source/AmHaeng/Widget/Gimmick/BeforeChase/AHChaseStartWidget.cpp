// Fill out your copyright notice in the Description page of Project Settings.


#include "AHChaseStartWidget.h"

void UAHChaseStartWidget::PlayAnims_Implementation()
{
}


void UAHChaseStartWidget::FinishAnims()
{
	UE_LOG(LogTemp, Log, TEXT("애니메이션이 끝났습니다"));
	if(SendToBeforeChaseClass.IsBound())
	{
		UE_LOG(LogTemp, Log, TEXT("SendToBeforeChaseClass이 바인딩 되어있습니다."));
		SendToBeforeChaseClass.Execute();
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("SendToBeforeChaseClass이 바인딩 되어있지 않습니다."));
	}
}
