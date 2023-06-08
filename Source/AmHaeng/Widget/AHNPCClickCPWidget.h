// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AHNPCClickCPWidget.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(TimerFinised)
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
	const float GetPercent();

	virtual void SetVisibility(ESlateVisibility InVisibility) override;

	void MouseClickDelegateBind();

	void MouseClicked(bool ClickOrReleased);

	TimerFinised TimerFinishSuccessDelegate;

protected:
	//이 함수가 실행될 때는 거의 모든 값이 초기화 된 상태
	virtual void NativeConstruct() override;

	
	UFUNCTION(BlueprintCallable)
	void SetMouseClickTimer(bool ClickState);
	
	UPROPERTY(BlueprintReadWrite, Category="ParentClass", meta=(AllowPrivateAccess = "true"))
	float PercentValue = 0.8123f;

	//Mouse Scan Timer -> 삭제 예정 (마우스 스캔을 시간 재는 것이 아닌, 마우스 스캔 시 클릭이 활성화되고 클릭 시간을 재는 방향으로)
	UPROPERTY(BlueprintReadWrite, Category="ParentClass", meta=(AllowPrivateAccess="true"))
	FTimerHandle ScanTimer;
	
private:
	UPROPERTY(BlueprintReadWrite, Category="ParentClass", meta=(AllowPrivateAccess="true"))
	float MaxClickTime;
	UPROPERTY(BlueprintReadWrite, Category="ParentClass", meta=(AllowPrivateAccess="true"))
	float NowClickTime;

};