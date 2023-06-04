// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AHNPCClickCPWidget.generated.h"

/**
 * 
 */
UCLASS()
class AMHAENG_API UAHNPCClickCPWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void AHNPCClickCPWidget();

	//실제 UI Progressbar 변경
	UFUNCTION(BlueprintNativeEvent, Category="Percentage")
	void SetPercent(const float InPercentage);
	virtual void SetPercent_Implementation(const float InPercentage);

	//변수 값 변경
	

	
private:
	//float Percent = 0.3f;
};
