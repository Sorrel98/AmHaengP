// Fill out your copyright notice in the Description page of Project Settings.


#include "AHNPCVehicleInfo.h"
#include "Kismet/KismetMathLibrary.h"

AAHNPCVehicleInfo::AAHNPCVehicleInfo()
{
	bIsScannable = UKismetMathLibrary::RandomBool();
	bIsTargetNPC = UKismetMathLibrary::RandomBool();
}

bool AAHNPCVehicleInfo::GetIsScannable()
{
	return bIsScannable;
}

void AAHNPCVehicleInfo::SetIsScannable(uint8 IsScannable)
{
	bIsScannable = UKismetMathLibrary::RandomBool();
}

bool AAHNPCVehicleInfo::GetIsTargetNPC()
{
	return bIsTargetNPC;
}

void AAHNPCVehicleInfo::SetIsTargetNPC(uint8 IsTargetNPC)
{
	bIsTargetNPC = UKismetMathLibrary::RandomBool();
}
