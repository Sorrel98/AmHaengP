// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AHNPCClickCPWidget.generated.h"

/**
 * 
 */

UCLASS()
class AMHAENG_API UAHNPCClickCPWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void AHNPCClickCPWidget();

	//실제 UI Progressbar 변경
	UFUNCTION(BlueprintNativeEvent, Category="Percentage")
	void SetPercent(const float InPercentage);
	virtual void SetPercent_Implementation(const float InPercentage);

	virtual void SetVisibility(ESlateVisibility InVisibility) override;
	

protected:
	//이 함수가 실행될 때는 거의 모든 값이 초기화 된 상태
	virtual void NativeConstruct() override;
	
private:
	//float Percent = 0.3f;
};
