// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AHStartBtnWidget.generated.h"
//AHTestWidget Delegate
DECLARE_MULTICAST_DELEGATE(FStartButtonDelegate);
/**
 * 
 */
UCLASS()
class AMHAENG_API UAHStartBtnWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FStartButtonDelegate PushedStartButton;

	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable)
	void TextButtonCallback();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UButton> SpawnStartBtn;
};
