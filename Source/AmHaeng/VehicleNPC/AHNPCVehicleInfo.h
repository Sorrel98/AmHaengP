// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "AmHaeng/Interface/AHScannable.h"
#include "AmHaeng/Interface/AHTargetNPC.h"
#include "AHNPCVehicleInfo.generated.h"

/**
 * 
 */
UCLASS()
class AMHAENG_API AAHNPCVehicleInfo : public AWheeledVehiclePawn, public IAHScannable, public IAHTargetNPC
{
	GENERATED_BODY()
	
public:
	AAHNPCVehicleInfo();

	virtual bool GetIsScannable() override;
	virtual void SetIsScannable(uint8 IsScannable) override;

	virtual bool GetIsTargetNPC() override;
	virtual void SetIsTargetNPC(uint8 IsTargetNPC) override;
private:
	uint8 bIsScannable : 1;
	uint8 bIsTargetNPC : 1;
};
