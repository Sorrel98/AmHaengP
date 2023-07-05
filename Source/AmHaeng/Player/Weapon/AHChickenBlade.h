// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmHaeng/Interface/Player/AHWeapon.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"
#include "GameFramework/Actor.h"
#include "AHChickenBlade.generated.h"

UCLASS()
class AMHAENG_API AAHChickenBlade : public AActor, public IAHWeapon
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAHChickenBlade();

	
	void InitChickenBlade(AAHNPCVehicleBase* ChasedNPC);
	UFUNCTION(BlueprintNativeEvent)
	void GetChickenComponent();
	UFUNCTION(BlueprintNativeEvent)
	void ChickenBladeDown();
	//void ChickenBladeUp();
	

	void MouseDelegate(bool IsClick);
	void MouseClick();
	void MouseClickReleased();
	

	void ChickenAttackSound();
	void ChickenBladeSetVisible(bool InVisible);

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	TArray<UActorComponent*> ChickenBladeComponentArray;
	USkeletalMeshComponent* ChickenBladeSkeletalMeshComponent;

	FTimerHandle ChickenDownTimer;
	FTimerHandle ChickenDownCallbackTimer;
	FTimerHandle ChickenUpTimer;

	bool IsAttacking = false;
	bool IsClicking = false;
};
