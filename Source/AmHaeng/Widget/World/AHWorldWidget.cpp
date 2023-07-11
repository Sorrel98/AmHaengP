// Fill out your copyright notice in the Description page of Project Settings.


#include "AHWorldWidget.h"

#include "AmHaeng/Player/AHVehiclePlayerController.h"

void UAHWorldWidget::BindWorldWidgetDelegate()
{
	/*UE_LOG(LogTemp, Warning, TEXT("WorldWidget Init"));
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if(PlayerController)
	{
		if (AAHVehiclePlayerController* CastedPlayerController = CastChecked<AAHVehiclePlayerController>(PlayerController))
		{
			AAHPlayerPawn* PP = CastedPlayerController->PlayerPawn;
			if(PP)
			{
				UE_LOG(LogTemp, Warning, TEXT("ReputationChangeDelegate Binded"));
				PP->ReputationChangeDelegate.AddUObject(this, &UAHWorldWidget::SetReputation);
			}
		}
	}*/
}

void UAHWorldWidget::SetReputation(uint32 InReputation)
{
	UE_LOG(LogTemp, Warning, TEXT("[WorldWidget] SetReputation : %d"), InReputation);
	Reputation->SetText(FText::FromString(FString::FromInt(InReputation)));
	this->InvalidateLayoutAndVolatility();
}
