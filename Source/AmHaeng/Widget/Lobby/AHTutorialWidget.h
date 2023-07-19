// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AHTutorialWidget.generated.h"

/**
 * 
 */
UCLASS()
class AMHAENG_API UAHTutorialWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void StartBtnClick();
};
