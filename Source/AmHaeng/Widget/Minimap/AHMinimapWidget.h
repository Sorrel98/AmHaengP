// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"
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

	//void SetNPCArray(class AAHNPCVehicleBase* InNPCVehicleBase);

	void MinimapSettingEnd();

	UFUNCTION(BlueprintNativeEvent, Category="NPCIcon")
	void AddNPCIcon(class AAHNPCVehicleBase* InNPCVehicleBase);
	void AddNPCIcon_Implementation(AAHNPCVehicleBase* InNPCVehicleBase);

	void CallAddNPCIcon(AAHNPCVehicleBase* InNPCVehicleBase);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TArray<AActor*> NPCArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	class UAHNPCSpawner* Spawner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	AAHNPCVehicleBase* NPCActor;

	TSubclassOf<class UAHNPCMinimapCursor> NPCCursorClass;
	class UAHNPCMinimapCursor* NPCCursor;
};
