// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "AHNPCInfoWidget.generated.h"


/**
 * 
 */
UCLASS()
class AMHAENG_API UAHNPCInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//Set Stats
	FORCEINLINE void SetNPCOwnerName(const FString NewName) { TB_Owner->SetText(FText::FromString(NewName)); }
	FORCEINLINE void SetNPCLicenseNumber(const FString NewLicenseNumber)
	{
		TB_License->SetText(FText::FromString(NewLicenseNumber));
	}

	FORCEINLINE void SetNPCMaxSpeed(const int32 NewMaxSpeed)
	{
		TB_MaxSpeed->SetText(FText::FromString(FString::FromInt(NewMaxSpeed)));
	}

	FORCEINLINE void SetNPCMinSpeed(const int32 NewMinSpeed)
	{
		TB_MinSpeed->SetText(FText::FromString(FString::FromInt(NewMinSpeed)));
	}

	FORCEINLINE void SetNPCSway(const int32 NewSway) { TB_Sway->SetText(FText::FromString(FString::FromInt(NewSway))); }

	void SetTooltipVisible(int8 visible);
	

protected:
	//이 함수가 실행될 때는 거의 모든 값이 초기화 된 상태
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta=(BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> TB_Owner;

	UPROPERTY(meta=(BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> TB_License;

	UPROPERTY(meta=(BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> TB_MinSpeed;

	UPROPERTY(meta=(BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> TB_MaxSpeed;

	UPROPERTY(meta=(BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> TB_Sway;

	UPROPERTY(meta=(BindWidget, AllowPrivateAccess = true))
	TObjectPtr<class UVerticalBox> BackGroundVerticalBox;

	UPROPERTY()
	FString NPCOwnerName;
	UPROPERTY()
	FString NPCLicenseNumber;
	UPROPERTY()
	int32 NPCMaxSpeed;
	UPROPERTY()
	int32 NPCMinSpeed;
	UPROPERTY()
	int32 NPCSway;

	const FString TooltipText = "If you want an arrest, hold the click for one second";
};
