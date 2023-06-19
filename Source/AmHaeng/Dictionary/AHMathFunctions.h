// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

//TArray를 받아서 그 Enum들 중 랜덤으로 하나를 반환하는 템플릿 함수
template <typename T>
T GetRandomValue(const TArray<T>& EnumValues)
{
	int32 RandomIndex = FMath::RandRange(0, EnumValues.Num() - 1);
	return EnumValues[RandomIndex];
}


template <typename T>
FString GetNPCEnumName(T InNPCOwnerName, FString EnumName)
{
	const UEnum* OwnerEnum = FindObject<UEnum>(ANY_PACKAGE, *EnumName, true);
	if (OwnerEnum)
	{
		return OwnerEnum->GetDisplayNameTextByValue(static_cast<int32>(InNPCOwnerName)).ToString();
	}
	return "InValid";
}


class AMHAENG_API AHMathFunctions
{
public:
	static int32 GetRandomIndex(int32 TArraySize);
	static FString MakeRandString(int32 Length);
	static FString CombineString(int32 WordsNumber);
	static int MakeRandInteger(int32 num1, int32 num2);
};


