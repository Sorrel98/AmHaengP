// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AHTutorialWidget.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(FStandardOfTargetDelegate)
UCLASS()
class AMHAENG_API UAHTutorialWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FStandardOfTargetDelegate StandardOfTargetDelegate;
	
	UFUNCTION(BlueprintCallable)
	void StartBtnClick();
};
