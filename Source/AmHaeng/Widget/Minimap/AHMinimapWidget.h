// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AHNPCMinimapCursor.h"
#include "Blueprint/UserWidget.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"
#include "Containers/Map.h"
#include "AHMinimapWidget.generated.h"

/**
 * 
 */
UCLASS()
class AMHAENG_API UAHMinimapWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void MinimapSettingEnd();

	UFUNCTION(BlueprintNativeEvent, Category="NPCIcon")
	void AddNPCIcon(AAHNPCVehicleBase* InNPCVehicleBase);

	void CallAddNPCIcon(AAHNPCVehicleBase* InNPCVehicleBase);

	void SetNPCCursorRed(AAHNPCVehicleBase* InTarget);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TMap<AAHNPCVehicleBase*, UAHNPCMinimapCursor*> NPCCursorMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TObjectPtr<class UAHNPCSpawner> Spawner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TObjectPtr<AAHNPCVehicleBase> NPCActor;
};
