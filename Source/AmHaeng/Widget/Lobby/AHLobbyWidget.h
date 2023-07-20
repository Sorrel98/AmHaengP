// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AHLobbyWidget.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(FTutorialBtnDelegate)
UCLASS()
class AMHAENG_API UAHLobbyWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	FTutorialBtnDelegate TutorialBtnDelegate;
	
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
	void StandardOfTargetBtnClicked();

	UFUNCTION(BlueprintCallable)
	void StartPlayBtnClicked();

	UFUNCTION()
	void SettingWidgets();

	void TutorialWidgetVisible(bool visible);
	TObjectPtr<class UAHTutorialWidget> GetTutorialWidget();

	void StandardOfTargetWidgetVisible(bool visible);
	TObjectPtr<class UAHStandardOfTargetWidget> GetStandardOfTargetWidget();

	UFUNCTION()
	void OnStandardOfTargetWidget();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TSubclassOf<UAHTutorialWidget> TutorialWidgetClass;
	TObjectPtr<UAHTutorialWidget> TutorialWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TSubclassOf<class UAHStandardOfTargetWidget> StandardOfTargetWidgetClass;
	TObjectPtr<UAHStandardOfTargetWidget> StandardOfTargetWidget;
};
