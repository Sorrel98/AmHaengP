// Fill out your copyright notice in the Description page of Project Settings.


#include "AHWorldWidget.h"

#include "AmHaeng/Player/AHVehiclePlayerController.h"

void UAHWorldWidget::BindWorldWidgetDelegate()
{
	
}

void UAHWorldWidget::SetReputation(uint32 InReputation)
{
	UE_LOG(LogTemp, Warning, TEXT("[WorldWidget] SetReputation : %d"), InReputation);
	Reputation->SetText(FText::FromString(FString::FromInt(InReputation)));
	this->InvalidateLayoutAndVolatility();
}

void UAHWorldWidget::SetWorldTime(uint32 InWorldTime)
{
	WorldTime->SetText(FText::FromString(FString::FromInt(InWorldTime)));
	this->InvalidateLayoutAndVolatility();
}
void UAHWorldWidget::SetGimmickWidgetText(EGimmickMode InGimmick)
{
	if(InGimmick == EGimmickMode::Patrol)
	{
		TextPatrol->SetVisibility(ESlateVisibility::Visible);
		TextChase->SetVisibility(ESlateVisibility::Hidden);
	}
	else if(InGimmick == EGimmickMode::Chase)
	{
		TextPatrol->SetVisibility(ESlateVisibility::Hidden);
		TextChase->SetVisibility(ESlateVisibility::Visible);
	}else
	{
		UE_LOG(LogTemp, Warning, TEXT("invalid EGimmickMode"));
	}
}

void UAHWorldWidget::TextChangeDelegateBind()
{
	AAHGameMode* GameMode = GetWorld()->GetAuthGameMode<AAHGameMode>();
	if(GameMode)
	{
		GameMode->GimmickChangeDelegate.AddUObject(this, &UAHWorldWidget::SetGimmickWidgetText);
	}
}

void UAHWorldWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//초기 설정
	SetGimmickWidgetText(EGimmickMode::Patrol);
	
	TextChangeDelegateBind();
}