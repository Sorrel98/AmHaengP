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
	void StatsSetting();

	//NPC info - OwnerName
	void SetOwnerName();
	FORCEINLINE void SetOwnerName(FString InOwnerName){ NPCOwnerName = InOwnerName; };
	const FString GetOwnerName();

	//NPC info - LicenseNumber
	void SetLicenseNumber();
	FORCEINLINE void SetLicenseNumber(FString InLicenseNumber){ NPCLicenseNumber = InLicenseNumber; };
	const FString GetLicenseNumber();


	//NPC info - NPCSpeed
	void SetNPCSpeed();
	FORCEINLINE void SetNPCSpeed(int32 InNPCMinSpeed, int32 InNPCMaxSpeed){ NPCMinSpeed = InNPCMinSpeed, NPCMaxSpeed = InNPCMaxSpeed; };
	const int32 GetNPCMinSpeed();
	const int32 GetNPCMaxSpeed();

	//NPC info - NPCSway
	void SetNPCSway();
	FORCEINLINE void SetNPCSway(int32 InNPCSway){ NPCSway = InNPCSway; };
	const int32 GetNPCSway();

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
};
