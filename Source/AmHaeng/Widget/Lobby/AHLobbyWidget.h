// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AHLobbyWidget.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(FStartBtnClickedDelegate)
UCLASS()
class AMHAENG_API UAHLobbyWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent)
	void SetReputationTextValue(int32 InReputation);

	UFUNCTION(BlueprintNativeEvent)
	void InVisibleReputation();

	UFUNCTION(BlueprintNativeEvent)
	void InVisibleKeyBindBox();

	UFUNCTION(BlueprintNativeEvent)
	void VisibleReputation();

	UFUNCTION(BlueprintNativeEvent)
	void VisibleKeyBindBox();

	UFUNCTION(BlueprintCallable)
	void StartBtnClicked();

	FStartBtnClickedDelegate StartBtnClickedDelegate;
};
