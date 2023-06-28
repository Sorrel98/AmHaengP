// Fill out your copyright notice in the Description page of Project Settings.


#include "AHGimmickModeWidget.h"

#include "AmHaeng/Game/AHGameMode.h"
#include "Components/TextBlock.h"
#include "AmHaeng/Prop/AHTypes.h"

void UAHGimmickModeWidget::SetGimmickWidgetText(EGimmickMode InGimmick)
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

void UAHGimmickModeWidget::TextChangeDelegateBind()
{
	AAHGameMode* GameMode = GetWorld()->GetAuthGameMode<AAHGameMode>();
	if(GameMode)
	{
		GameMode->GimmickChangeDelegate.AddUObject(this, &UAHGimmickModeWidget::SetGimmickWidgetText);
	}
}

void UAHGimmickModeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//초기 설정
	SetGimmickWidgetText(EGimmickMode::Patrol);
	
	TextChangeDelegateBind();
}
