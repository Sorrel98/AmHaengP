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
	//UAHNPCInfoWidget(const FObjectInitializer& ObjectInitializer);

public:
	//OwnerName
	void SetTextOwnerName(FString NewOwnerName){}
private:
	UPROPERTY()
	TObjectPtr<class UTextBlock> TB_OwnerName;
	
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
	
};
