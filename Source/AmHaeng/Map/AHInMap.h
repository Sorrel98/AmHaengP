// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "AHInMap.generated.h"

UCLASS()
class AMHAENG_API AAHInMap : public AActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void NPCIsOutOfMap(class AAHNPCVehicleBase* OutNPC);

	void SetSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = true))
	TObjectPtr<class UAHNPCSpawner> Spawner;
};
