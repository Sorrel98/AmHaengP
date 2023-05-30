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

	//NPC info - bIsScannable
	virtual bool GetIsScannable() override;
	virtual void SetIsScannable(const uint8& IsScannable) override;

	//NPC info - bIsTargetNPC
	virtual bool GetIsTargetNPC() override;
	virtual void SetIsTargetNPC(const uint8& IsTarget) override;

	void DetailInfoSetting();

	//NPC info - OwnerName
	void SetOwnerName();
	
	//NPC info - LicenseNumber
	void SetLicenseNumber();
	FString MakeRandString(int32 Length);
	FString CombineString(int32 WordsNumber);
	

	int MakeRandInteger(int32 num1, int32 num2);

	//NPC info - NPCSpeed
	void SetNPCSpeed();

	//NPC info - NPCSway
	void SetNPCSway();

	
private:
	//NPC info - Main
	uint8 bIsScannable : 1;
	uint8 bIsTargetNPC : 1;

	//NPC info - Detail
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FString NPCOwnerName;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FString NPCLicenseNumber;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	int32 NPCMaxSpeed;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	int32 NPCMinSpeed;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	int32 NPCSway;
};
