// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmHaeng/Interface/Player/AHWeapon.h"
#include "AmHaeng/Player/AHPlayerPawn.h"
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
	void SetChickenBladeCapsuleComponent();

	UCapsuleComponent* GetChickenBladeCapsuleComponent(){return CapsuleComponent;};

	void SetChickenVisible(bool visible);
	
	void ChickenAttackSound();
	void MouseClickDelegate(bool IsClick);

	//Attack
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ChickenAttackDetect();
	
	
	ChickenAttackFinish ChickenAttackFinishDelegate;

	

private:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess= true))
	AAHNPCVehicleBase* ChaseNPC = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess= true))
	AAHPlayerPawn* PlayerPawn = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess= true))
	UCapsuleComponent* CapsuleComponent = nullptr;
};
