// Fill out your copyright notice in the Description page of Project Settings.


#include "AHTypes.h"

AHTypes::AHTypes()
{
}

AHTypes::~AHTypes()
{
}

const TArray<NPCOwnerNames>& AHTypes::GetNPCOwnerNameArray() const
{
	return NPCOwnerNamesArray;
}


const FString AHTypes::GetNPCEnumName(NPCOwnerNames InNPCOwnerName) const
{
	const UEnum* OwnerEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("NPCOwnerNames"), true);
	if(OwnerEnum)
	{
		return OwnerEnum->GetDisplayNameTextByValue((int32)InNPCOwnerName).ToString();
	}
	else
	{
		return "InValid";
	}
}
