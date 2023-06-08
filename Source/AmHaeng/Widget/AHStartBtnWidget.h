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

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* SpawnStartBtn;

	//나중에 사용
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//class UButton* SpawnFinBtn;


public:
	virtual void NativeOnInitialized() override;

public:
	UFUNCTION(BlueprintCallable)
	void TextButtonCallback();
};
