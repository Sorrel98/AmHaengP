// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AHNPCIsTargetWidget.generated.h"

/**
 * 
 */
UCLASS()
class AMHAENG_API UAHNPCIsTargetWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetNPCIsTargetWidget(uint8 InIsTargetNPC);
	void AllTextInvisible();

private:
	UPROPERTY(meta=(BindWidget, AllowPrivateAccess = true))
	TObjectPtr<class UTextBlock> CorrectTargetText;

	UPROPERTY(meta=(BindWidget, AllowPrivateAccess = true))
	TObjectPtr<class UTextBlock> FailTargetText;

	uint8 IsTargetNPC;

	FTimerHandle WidgetInvisibleTimer;
};
