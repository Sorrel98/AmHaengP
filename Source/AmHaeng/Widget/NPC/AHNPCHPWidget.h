// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AHNPCHPWidget.generated.h"

/**
 * 
 */
UCLASS()
class AMHAENG_API UAHNPCHPWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetNPCHP(float InHP);
	void NativeConstruct();
	/*virtual void NativeConstruct() override;*/


private:
	UPROPERTY(meta=(BindWidget, AllowPrivateAccess = true))
	TObjectPtr<class UProgressBar> NPC_HPBar;

};
