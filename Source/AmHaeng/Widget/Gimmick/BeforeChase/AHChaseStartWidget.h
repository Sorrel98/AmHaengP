// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AHChaseStartWidget.generated.h"

/**
 * 
 */

DECLARE_DELEGATE(FFinishChaseAnim)
UCLASS()
class AMHAENG_API UAHChaseStartWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PlayAnims();
	UFUNCTION(BlueprintCallable)
	void FinishAnims();

	FWidgetAnimationDynamicEvent FinishWidgetAnimationEvent;
	FFinishChaseAnim SendToBeforeChaseClass;

private:
	UPROPERTY(BlueprintReadOnly, Transient, Category="Anim", meta = (BindWidgetAnim, AllowPrivateAccess = true))
	class UWidgetAnimation* PlayerChaseStartAnim = nullptr;
	UPROPERTY(BlueprintReadOnly, Transient, Category="Anim", meta = (BindWidgetAnim, AllowPrivateAccess = true))
	class UWidgetAnimation* NPCChasedStartAnim = nullptr;
};
