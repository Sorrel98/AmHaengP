// Fill out your copyright notice in the Description page of Project Settings.


#include "AHNPCStatComponent.h"
#include "AmHaeng/Dictionary/AHMathFunctions.h"
#include "AmHaeng/Prop/AHTypes.h"

// Sets default values for this component's properties
UAHNPCStatComponent::UAHNPCStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAHNPCStatComponent::BeginPlay()
{
	Super::BeginPlay();
	StatsSetting();
}


// Called every frame
void UAHNPCStatComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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
	NPCLicenseNumber = CombineString(2);
}

FString UAHNPCStatComponent::MakeRandString(int32 Length)
{
	const FString Characters = TEXT("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");
	FString RandomString;
	RandomString.Reserve(Length);

	for (int32 ix = 0; ix < Length; ++ix)
	{
		int32 RandomIdx = FMath::RandRange(0, Characters.Len() - 1);
		RandomString.AppendChar(Characters[RandomIdx]);
	}

	return RandomString;
}

FString UAHNPCStatComponent::CombineString(int32 WordsNumber)
{
	FString CombinedString;
	for (int32 ix = 0; ix < WordsNumber; ++ix)
	{
		if (ix != 0)
		{
			CombinedString.AppendChar('_');
		}
		CombinedString.Append(MakeRandString(3));
	}
	return CombinedString;
}

const FString UAHNPCStatComponent::GetLicenseNumber()
{
	return NPCLicenseNumber;
}

int UAHNPCStatComponent::MakeRandInteger(int32 num1, int32 num2)
{
	return FMath::RandRange(num1, num2);
}

void UAHNPCStatComponent::SetNPCSpeed()
{
	NPCMinSpeed = MakeRandInteger(30, 50);
	NPCMaxSpeed = MakeRandInteger(90, 110);
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
	NPCSway = MakeRandInteger(10, 50);
}

const int32 UAHNPCStatComponent::GetNPCSway()
{
	return NPCSway;
}
