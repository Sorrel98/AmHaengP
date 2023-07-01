// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AHScreenCrashWidget.generated.h"

/**
 * 
 */
UCLASS()
class AMHAENG_API UAHScreenCrashWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PlayAnims();
	UFUNCTION(BlueprintCallable)
	void FinishAnims();
};
