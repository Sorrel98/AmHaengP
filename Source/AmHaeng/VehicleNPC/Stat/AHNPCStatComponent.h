// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AHNPCStatComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AMHAENG_API UAHNPCStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAHNPCStatComponent();
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:
	void StatsSetting(int32 InIDNumber, uint8 IsTarget);

	//NPC info - OwnerName
	void SetOwnerName();
	FORCEINLINE void SetOwnerName(FString InOwnerName){ NPCOwnerName = InOwnerName; };
	const FString GetOwnerName();

	//NPC info - LicenseNumber
	void SetGoodLicenseNumber();
	void SetBadLicenseNumber();
	const FString GetLicenseNumber();


	//NPC info - NPCSpeed
	void SetGoodSpeed();
	void SetBadSpeed();
	const int32 GetNPCMinSpeed();
	const int32 GetNPCMaxSpeed();

	//NPC info - NPCSway
	void SetGoodSway();
	void SetBadSway();
	const int32 GetNPCSway();

	//NPC info - ID Number
	void SetIDNumber(int32 InNumber);

	//NPC info - Groggy Gage
	void SetNPCHP();
	int32 GetNPCHP(){ return NPCHP; };
	void NPCHPDown();

private:
	//NPC info - Detail
	UPROPERTY()
	FString NPCOwnerName;
	UPROPERTY()
	FString NPCLicenseNumber;
	UPROPERTY()
	int32 NPCMaxSpeed;
	UPROPERTY()
	int32 NPCMinSpeed;
	UPROPERTY()
	int32 NPCSway;
	UPROPERTY()
	int32 NPCIDNumber;

	//0 ~ 100
	UPROPERTY()
	int32 NPCHP;
};
