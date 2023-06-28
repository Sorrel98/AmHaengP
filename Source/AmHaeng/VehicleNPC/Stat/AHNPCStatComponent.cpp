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

void UAHNPCStatComponent::StatsSetting()
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

void UAHNPCStatComponent::SetLicenseNumber()
{
	NPCLicenseNumber = AHMathFunctions::CombineString(2);
}

const FString UAHNPCStatComponent::GetLicenseNumber()
{
	return NPCLicenseNumber;
}

void UAHNPCStatComponent::SetNPCSpeed()
{
	NPCMinSpeed = AHMathFunctions::MakeRandInteger(30, 50);
	NPCMaxSpeed = AHMathFunctions::MakeRandInteger(90, 110);
}

const int32 UAHNPCStatComponent::GetNPCMinSpeed()
{
	return NPCMinSpeed;
}

const int32 UAHNPCStatComponent::GetNPCMaxSpeed()
{
	return NPCMaxSpeed;
}

void UAHNPCStatComponent::SetNPCSway()
{
	NPCSway = AHMathFunctions::MakeRandInteger(10, 50);
}

const int32 UAHNPCStatComponent::GetNPCSway()
{
	return NPCSway;
}
