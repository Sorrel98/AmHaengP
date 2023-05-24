// Fill out your copyright notice in the Description page of Project Settings.


//#include "Widget/AHWidget.h"
#include "AHWidget.h"

void UAHWidget::NativeOnInitialized()
{
}

void UAHWidget::TextButtonCallback()
{
	UE_LOG(LogTemp, Log, TEXT("Button Clicked"));

	//Delegate to Game Mode "Pushed Start Button"
	if (PushedStartButton.IsBound())
	{
		PushedStartButton.Broadcast();
	}
}
