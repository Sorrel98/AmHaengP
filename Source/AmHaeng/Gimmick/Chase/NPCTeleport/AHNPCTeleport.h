// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AHNPCTeleport.generated.h"

/**
 * 
 */
UCLASS()
class AMHAENG_API UAHNPCTeleport : public UObject
{
	GENERATED_BODY()
public:
	void SetTeleportLocations();

	void Teleport(class AAHNPCVehicleBase* InTargetNPC);

	AActor* GetFarTeleportActor(FVector InPlayerLocation);
	
private:
	TArray<AActor*> NPCTeleportLocationActors;
	
	TArray<FVector> TeleportLocations;
	TArray<FRotator> TeleportRotations;
};
