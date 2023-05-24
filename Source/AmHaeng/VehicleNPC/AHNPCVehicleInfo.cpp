// Fill out your copyright notice in the Description page of Project Settings.


#include "AHNPCVehicleInfo.h"
#include "AmHaeng/Prop/AHTypes.h"
#include "Kismet/KismetMathLibrary.h"
#include "VisualLogger/VisualLoggerTypes.h"

AAHNPCVehicleInfo::AAHNPCVehicleInfo()
{
	//Main Info Setting
	bIsScannable = true;
	uint32 bIsTargetNPCPercentage = UKismetMathLibrary::RandomIntegerInRange(1, 10);
	bIsTargetNPC = (bIsTargetNPCPercentage<=3)? true:false;

	//Detail Info Setting
	DetailInfoSetting();

	//Log
	UE_LOG(LogTemp, Log, TEXT("IsTargetCar : %d, Car Owner : %s, LicenseNumber : %s, Min Speed : %d, Max Speed : %d, Vehicle Sway : %d"),
								bIsTargetNPC, *NPCOwnerName, *NPCLicenseNumber, NPCMinSpeed, NPCMaxSpeed, NPCSway);
}

bool AAHNPCVehicleInfo::GetIsScannable()
{
	return bIsScannable;
}

void AAHNPCVehicleInfo::SetIsScannable(const uint8& IsScannable)
{
	bIsScannable = IsScannable;
}

bool AAHNPCVehicleInfo::GetIsTargetNPC()
{
	return bIsTargetNPC;
}

void AAHNPCVehicleInfo::SetIsTargetNPC(const uint8& IsTargetNPC)
{
	bIsTargetNPC = IsTargetNPC;
}

void AAHNPCVehicleInfo::DetailInfoSetting()
{
	//NPCOwnerNameSetting
	SetOwnerName();

	//LicenseNumberSetting
	SetLicenseNumber();

	//NPCSpeedSetting
	SetNPCSpeed();
	
	//NPCSwaySetting
	SetNPCSway();
	
}

void AAHNPCVehicleInfo::SetOwnerName()
{
	AHTypes MyTypes;
	FString EnumName = "NPCOwnerNames";
	FString OwnerName = GetNPCEnumName(GetRandomEnumValue(MyTypes.GetNPCOwnerNameArray()), *EnumName);
	NPCOwnerName = OwnerName;
}

void AAHNPCVehicleInfo::SetLicenseNumber()
{
	NPCLicenseNumber = CombineString(2);
}

FString AAHNPCVehicleInfo::MakeRandString(int32 Length)
{
	const FString Characters = TEXT("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");
	FString RandomString;
	RandomString.Reserve(Length);

	for(int32 ix = 0; ix<Length; ++ix)
	{
		int32 RandomIdx = FMath::RandRange(0, Characters.Len()-1);
		RandomString.AppendChar(Characters[RandomIdx]);
	}

	return RandomString;
}

FString AAHNPCVehicleInfo::CombineString(int32 WordsNumber)
{
	FString CombinedString;
	for(int32 ix = 0; ix<WordsNumber; ++ix)
	{
		if(ix != 0)
		{
			CombinedString.AppendChar('_');
		}
		CombinedString.Append(MakeRandString(3));
	}
	return CombinedString;
}

int AAHNPCVehicleInfo::MakeRandInteger(int32 num1, int32 num2)
{
	return FMath::RandRange(num1, num2);
}

void AAHNPCVehicleInfo::SetNPCSpeed()
{
	NPCMinSpeed = MakeRandInteger(30, 50);
	NPCMaxSpeed = MakeRandInteger(90, 110);
}

void AAHNPCVehicleInfo::SetNPCSway()
{
	NPCSway = MakeRandInteger(10, 50);
}
