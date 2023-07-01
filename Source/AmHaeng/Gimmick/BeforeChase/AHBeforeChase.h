// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmHaeng/Player/AHVehiclePlayerController.h"
#include "AHBeforeChase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class AMHAENG_API UAHBeforeChase : public UObject
{
	GENERATED_BODY()
public:
	UAHBeforeChase();
	void BeforeChaseProcess(AAHVehiclePlayerController* PC);
	void PlayChaseStartWidget();

	void FinishChaseStartWidget();

	void SetPause(bool InPause);


private:
	//Gimmick Mode Widget
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UAHChaseStartWidget> ChaseStartWidgetClass;
	UAHChaseStartWidget* ChaseStartWidget = nullptr;

	AAHVehiclePlayerController* PC;


};
