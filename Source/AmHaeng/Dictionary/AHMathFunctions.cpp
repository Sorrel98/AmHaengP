// Fill out your copyright notice in the Description page of Project Settings.


#include "AHMathFunctions.h"

int32 AHMathFunctions::GetRandomIndex(const int32 TArraySize)
{
	return FMath::RandRange(0, TArraySize - 1);
}

FString AHMathFunctions::MakeRandString(int32 Length)
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

FString AHMathFunctions::CombineString(int32 WordsNumber)
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

int AHMathFunctions::MakeRandInteger(int32 num1, int32 num2)
{
	return FMath::RandRange(num1, num2);
}