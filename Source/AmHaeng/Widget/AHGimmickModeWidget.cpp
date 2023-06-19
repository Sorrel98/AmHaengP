// Fill out your copyright notice in the Description page of Project Settings.


#include "AHGimmickModeWidget.h"

#include "AmHaeng/Game/AHGameMode.h"
#include "Components/TextBlock.h"
#include "AmHaeng/Prop/AHTypes.h"

void UAHGimmickModeWidget::SetGimmickWidgetText(EGimmickMode InGimmick)
{
	UEnum* EnumPtr = StaticEnum<EGimmickMode>();
	int32 Index = EnumPtr->GetIndexByValue((int64)InGimmick);
	FString EnumMemberDisplayName = EnumPtr->GetDisplayNameTextByIndex(Index).ToString();
	GimmickText->SetText(FText::FromString(EnumMemberDisplayName));
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
