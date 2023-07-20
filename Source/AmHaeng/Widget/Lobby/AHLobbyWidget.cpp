// Fill out your copyright notice in the Description page of Project Settings.


#include "AHLobbyWidget.h"

#include "AHStandardOfTargetWidget.h"
#include "AHTutorialWidget.h"

void UAHLobbyWidget::SetReputationTextValue_Implementation(int32 InReputation)
{
}

void UAHLobbyWidget::InVisibleReputation_Implementation()
{
}

void UAHLobbyWidget::VisibleReputation_Implementation()
{
}

void UAHLobbyWidget::InVisibleKeyBindBox_Implementation()
{
}

void UAHLobbyWidget::VisibleKeyBindBox_Implementation()
{
}

void UAHLobbyWidget::StandardOfTargetBtnClicked()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	StandardOfTargetWidgetVisible(false);
	TutorialWidgetVisible(true);
}

void UAHLobbyWidget::StartPlayBtnClicked()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	TutorialWidgetVisible(false);
	StandardOfTargetWidgetVisible(true);
}

void UAHLobbyWidget::SettingWidgets()
{
	if(TutorialWidgetClass)
	{
		TutorialWidget = Cast<UAHTutorialWidget>(CreateWidget(GetWorld(),TutorialWidgetClass));
		if(TutorialWidget)
		{
			TutorialWidget->AddToViewport();
			TutorialWidgetVisible(false);
			TutorialWidget->StandardOfTargetDelegate.BindUObject(this, &UAHLobbyWidget::OnStandardOfTargetWidget);
		}
	}
	if(StandardOfTargetWidgetClass)
	{
		StandardOfTargetWidget = Cast<UAHStandardOfTargetWidget>(CreateWidget(GetWorld(),StandardOfTargetWidgetClass));
		if(StandardOfTargetWidget)
		{
			StandardOfTargetWidget->AddToViewport();
			StandardOfTargetWidgetVisible(false);
		}
	}
}

void UAHLobbyWidget::TutorialWidgetVisible(bool visible)
{
	if(TutorialWidget)
	{
		if(!visible)
		{
			TutorialWidget->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			TutorialWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
	
}

TObjectPtr<UAHTutorialWidget> UAHLobbyWidget::GetTutorialWidget()
{
	return TutorialWidget;
}

void UAHLobbyWidget::StandardOfTargetWidgetVisible(bool visible)
{
	if(StandardOfTargetWidget)
	{
		if(!visible)
		{
			StandardOfTargetWidget->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			StandardOfTargetWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

TObjectPtr<UAHStandardOfTargetWidget> UAHLobbyWidget::GetStandardOfTargetWidget()
{
	return StandardOfTargetWidget;
}

void UAHLobbyWidget::OnStandardOfTargetWidget()
{
	UE_LOG(LogTemp, Log, TEXT("StandardOftargetwidget"));
	this->SetVisibility(ESlateVisibility::Hidden);
	TutorialWidgetVisible(false);
	StandardOfTargetWidgetVisible(true);
}
