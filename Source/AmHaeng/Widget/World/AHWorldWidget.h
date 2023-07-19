// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AmHaeng/Prop/AHTypes.h"
#include "Components/TextBlock.h"
#include "AHWorldWidget.generated.h"

/**
 * 
 */
UCLASS()
class AMHAENG_API UAHWorldWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void BindWorldWidgetDelegate();
	void SetReputation(uint32 InReputation);
	void SetWorldTime(uint32 InWorldTime);
	
	void SetGimmickWidgetText(EGimmickMode InGimmick);

	void TextChangeDelegateBind();

private:
	UPROPERTY(meta=(BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> TextPatrol;

	UPROPERTY(meta=(BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> TextChase;
	
protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta=(BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> Reputation;

	UPROPERTY(meta=(BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> WorldTime;
};
