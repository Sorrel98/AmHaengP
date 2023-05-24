// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VisualLogger/VisualLoggerTypes.h"

/**
 * 
 */



UENUM()
enum class NPCOwnerNames : uint8
{
	Name1 UMETA(DisplayName = "김수영"),
	Name2 UMETA(DisplayName = "김근홍"),
	Name3 UMETA(DisplayName = "김도형"),
	Name4 UMETA(DisplayName = "김민정"),
	Name5 UMETA(DisplayName = "김소현"),
	Name6 UMETA(DisplayName = "박진영"),
	Name7 UMETA(DisplayName = "이삭"),
	Name8 UMETA(DisplayName = "조별희"),
};

//TArray를 받아서 그 Enum들 중 랜덤으로 하나를 반환하는 템플릿 함수
template<typename T>
T GetRandomEnumValue(const TArray<T>& EnumValues)
{
	int32 RandomIndex = FMath::RandRange(0, EnumValues.Num()-1);
	return EnumValues[RandomIndex];
}

template<typename T>
FString GetNPCEnumName(T InNPCOwnerName, FString EnumName)
{
	const UEnum* OwnerEnum = FindObject<UEnum>(ANY_PACKAGE, *EnumName, true);
	if(OwnerEnum)
	{
		return OwnerEnum->GetDisplayNameTextByValue((int32)InNPCOwnerName).ToString();
	}
	else
	{
		return "InValid";
	}
}


class AMHAENG_API AHTypes
{
public:
	AHTypes();
	~AHTypes();

	//TArray를 반환하는 함수
	const TArray<NPCOwnerNames>& GetNPCOwnerNameArray() const;

	//Enum을 input으로 하여 해당 Enum의 DisplayName을 반환하는 함수
	const FString GetNPCEnumName(NPCOwnerNames InNPCOwnerName) const;


private:
	//랜덤성을 위한 TArray -> 생성자 코드에서 한번에 넣을 수 있게 수정해야 함
	TArray<NPCOwnerNames> NPCOwnerNamesArray = {
		NPCOwnerNames::Name1,
		NPCOwnerNames::Name2,
		NPCOwnerNames::Name3,
		NPCOwnerNames::Name4,
		NPCOwnerNames::Name5,
		NPCOwnerNames::Name6,
		NPCOwnerNames::Name7,
		NPCOwnerNames::Name8
	};
};
