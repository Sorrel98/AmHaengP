// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"
#include "AHNPCMinimapCursor.generated.h"

/**
 * 
 */
UCLASS()
class AMHAENG_API UAHNPCMinimapCursor : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetNPCActor(AAHNPCVehicleBase* InNPCActor);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	AAHNPCVehicleBase* NPCActor;
	
};
