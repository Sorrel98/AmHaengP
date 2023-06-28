// Fill out your copyright notice in the Description page of Project Settings.


#include "AHNPCStatComponent.h"
#include "AmHaeng/Dictionary/AHMathFunctions.h"
#include "AmHaeng/Prop/AHTypes.h"

// Sets default values for this component's properties
UAHNPCStatComponent::UAHNPCStatComponent()
{
}


// Called when the game starts
void UAHNPCStatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAHNPCStatComponent::StatsSetting(int32 InIDNumber, uint8 IsTarget)
{
	UE_LOG(LogTemp, Warning, TEXT("Setting NPC ID : %d"), InIDNumber);
	//NPC Id Setting
	SetIDNumber(InIDNumber);
	
	//NPCOwnerNameSetting
	SetOwnerName();

	//LicenseNumberSetting
	SetGoodLicenseNumber();

	//NPCSpeedSetting
	SetGoodSpeed();

	//NPCSwaySetting
	SetGoodSway();
	if(IsTarget)
	{
		int32 WrongPoint = FMath::RandRange(0, 2);
		switch (WrongPoint)
		{
		case 0:
			//LicenseNumberSetting
			SetBadLicenseNumber();
			break;
		case 1:
			//NPCSpeedSetting
			SetBadSpeed();
			break;
		case 2:
			//NPCSwaySetting
			SetBadSway();
			break;
		default:
			return;	
		}
	}
	
}

void UAHNPCStatComponent::SetOwnerName()
{
	AHTypes MyTypes;
	FString EnumName = "NPCOwnerNames";
	FString OwnerName = GetNPCEnumName(GetRandomValue(MyTypes.GetNPCOwnerNameArray()), *EnumName);
	NPCOwnerName = OwnerName;
}

const FString UAHNPCStatComponent::GetOwnerName()
{
	return NPCOwnerName;
}

void UAHNPCStatComponent::SetGoodLicenseNumber()
{
	NPCLicenseNumber = AHMathFunctions::MakeGoodLicenseNumber(NPCIDNumber);
}

void UAHNPCStatComponent::SetBadLicenseNumber()
{
	int32 WrongPart = FMath::RandRange(0, 2); //Year, Month, Day 중에 하나만 Wrong
	NPCLicenseNumber = AHMathFunctions::MakeBadLicenseNumber(WrongPart, NPCIDNumber);
}

const FString UAHNPCStatComponent::GetLicenseNumber()
{
	return NPCLicenseNumber;
}

void UAHNPCStatComponent::SetGoodSpeed()
{
	NPCMinSpeed = AHMathFunctions::MakeRandInteger(30, 50);
	NPCMaxSpeed = AHMathFunctions::MakeRandInteger(NPCMinSpeed, 70);
}

void UAHNPCStatComponent::SetBadSpeed()
{
	NPCMinSpeed = AHMathFunctions::MakeRandInteger(70, 90);
	NPCMaxSpeed = AHMathFunctions::MakeRandInteger(NPCMinSpeed, 110);
}

const int32 UAHNPCStatComponent::GetNPCMinSpeed()
{
	return NPCMinSpeed;
}

const int32 UAHNPCStatComponent::GetNPCMaxSpeed()
{
	return NPCMaxSpeed;
}

void UAHNPCStatComponent::SetGoodSway()
{
	NPCSway = AHMathFunctions::MakeRandInteger(10, 30);
}

void UAHNPCStatComponent::SetBadSway()
{
	NPCSway = AHMathFunctions::MakeRandInteger(31, 50);
}

const int32 UAHNPCStatComponent::GetNPCSway()
{
	return NPCSway;
}

void UAHNPCStatComponent::SetIDNumber(int32 InNumber)
{
	NPCIDNumber = InNumber;
}
