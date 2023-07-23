// Fill out your copyright notice in the Description page of Project Settings.


#include "AHMathFunctions.h"
#include "Misc/DateTime.h"

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

FString AHMathFunctions::MakeGoodLicenseNumber(int32 IDNumber)
{
	FString Year = RandomYear();
	FString Month = RandomMonth();
	FString Day = RandomDay(FCString::Atoi(*Year), FCString::Atoi(*Month));
	
	FString CombinedString;
	FString Hyphen = "-";
	//Year
	CombinedString.Append(Year);
	CombinedString.Append(Hyphen);
	//Month
	CombinedString.Append(Month);
	CombinedString.Append(Hyphen);
	//Day
	CombinedString.Append(Day);
	CombinedString.Append(Hyphen);
	//OwnNumber
	CombinedString.Append(FString::FromInt(IDNumber));
	
	return CombinedString;
}

FString AHMathFunctions::MakeBadLicenseNumber(int32 WrongPart, int32 IDNumber)
{
	FString Year = RandomYear();
	FString Month = RandomMonth();
	FString Day = RandomDay(FCString::Atoi(*Year), FCString::Atoi(*Month));

	switch(WrongPart)
	{
	case 0:
		Year = WrongRandomYear();
		break;
	case 1:
		Month = WrongRandomMonth();
		break;
	case 2:
		Day = WrongRandomDay();
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Wrong Part Number"));
		return "";
	}

	FString CombinedString;
	FString Hyphen = "-";
	//Year
	CombinedString.Append(Year);
	CombinedString.Append(Hyphen);
	//Month
	CombinedString.Append(Month);
	CombinedString.Append(Hyphen);
	//Day
	CombinedString.Append(Day);
	CombinedString.Append(Hyphen);
	//OwnNumber
	CombinedString.Append(FString::FromInt(IDNumber));
	
	return CombinedString;
}

FString AHMathFunctions::RandomYear()
{
	return FString::FromInt(FMath::RandRange(1980, 2023));
}

FString AHMathFunctions::RandomMonth()
{
	return FString::FromInt(FMath::RandRange(1, 12));
}

FString AHMathFunctions::RandomDay(int32 Year, int32 Month)
{
	return FString::FromInt(FDateTime::DaysInMonth(Year, Month));
}

FString AHMathFunctions::WrongRandomYear()
{
	int32 random = FMath::RandRange(1, 3);
	switch (random)
	{
	case 1:
		return FString::FromInt(FMath::RandRange(2025, 2040));
	case 2:
		return FString::FromInt(FMath::RandRange(19900, 20230));
	case 3:
		return FString::FromInt(0);
	default:
		return "";
	}
}

FString AHMathFunctions::WrongRandomMonth()
{
	bool random = FMath::RandBool();
	if(random)
	{
		return FString::FromInt(FMath::RandRange(1, 12))+"0";
	}
	else
	{
		return FString::FromInt(FMath::RandRange(13, 20));
	}
}

FString AHMathFunctions::WrongRandomDay()
{
	bool random = FMath::RandBool();
	if(random)
	{
		return FString::FromInt(FMath::RandRange(1, 30))+"0";
	}
	else
	{
		return FString::FromInt(FMath::RandRange(32, 40));
	}
}