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

	bool IsHitActorOnSpawnActor(int32 TeleportLocationIndex);

	UFUNCTION()
	int32 SetRandomIndex();

	void SpawnNewNPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = true))
	class UAHNPCSpawner* Spawner;

	FTimerHandle FindSpawnerTimerHandle;

	int32 SpawnIndex;
};
