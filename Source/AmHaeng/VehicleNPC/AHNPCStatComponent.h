// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AHNPCStatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void StatsSetting();
	
	//NPC info - OwnerName
	void SetOwnerName();
	const FString GetOwnerName();
	
	//NPC info - LicenseNumber
	void SetLicenseNumber();
	FString MakeRandString(int32 Length);
	FString CombineString(int32 WordsNumber);
	const FString GetLicenseNumber();
	
	int MakeRandInteger(int32 num1, int32 num2);

	//NPC info - NPCSpeed
	void SetNPCSpeed();
	const int32 GetNPCMinSpeed();
	const int32 GetNPCMaxSpeed();

	//NPC info - NPCSway
	void SetNPCSway();
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
