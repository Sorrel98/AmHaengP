// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmHaeng/Interface/Player/AHWeapon.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"
#include "GameFramework/Actor.h"
#include "AHChickenBlade.generated.h"

DECLARE_DELEGATE(ChickenAttackFinish)
UCLASS()
class AMHAENG_API AAHChickenBlade : public AActor, public IAHWeapon
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAHChickenBlade();

	
	void InitChickenBlade(AAHNPCVehicleBase* ChasedNPC);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ChickenAttackTimeline(AAHChickenBlade* ChickenBlade);
	UFUNCTION(BlueprintCallable)
	void ChickenAttackTimelineFinish();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetChickenRotate(float XRotateRate, AAHChickenBlade* ChickenBlade);
	//void ChickenBladeUp();
	
	void ChickenAttackSound();
	
	ChickenAttackFinish ChickenAttackFinishDelegate;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

private:
	bool IsAttacking = false;
	bool IsClicking = false;
};
