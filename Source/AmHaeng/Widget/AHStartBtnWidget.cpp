// Fill out your copyright notice in the Description page of Project Settings.


#include "AHStartBtnWidget.h"

void UAHStartBtnWidget::NativeOnInitialized()
{
}

void UAHStartBtnWidget::TextButtonCallback()
{
	UE_LOG(LogTemp, Log, TEXT("Button Clicked"));

	//Delegate to Game Mode "Pushed Start Button"
		//PushedStartButton.Broadcast();
}
