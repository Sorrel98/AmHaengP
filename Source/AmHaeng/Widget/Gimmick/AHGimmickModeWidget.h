// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AmHaeng/Prop/AHTypes.h"
#include "AHGimmickModeWidget.generated.h"

/**
 * 
 */
UCLASS()
class AMHAENG_API UAHGimmickModeWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetGimmickWidgetText(EGimmickMode InGimmick);

	void TextChangeDelegateBind();

private:
	UPROPERTY(meta=(BindWidget, AllowPrivateAccess = true))
	TObjectPtr<class UTextBlock> TextPatrol;

	UPROPERTY(meta=(BindWidget, AllowPrivateAccess = true))
	TObjectPtr<class UTextBlock> TextChase;
	
protected:
	virtual void NativeConstruct() override;
};
