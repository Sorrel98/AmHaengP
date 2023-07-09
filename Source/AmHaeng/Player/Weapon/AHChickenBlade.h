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

	void SetChickenVisible(bool visible);
	
	void ChickenAttackSound();
	void MouseClickDelegate(bool IsClick);
	UFUNCTION(BlueprintCallable)
	bool GetIsClickng(){return IsClicking;}

	//Attack
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ChickenAttackDetect();
	
	
	ChickenAttackFinish ChickenAttackFinishDelegate;
protected:
	/*// Called when the game starts or when spawned
	virtual void BeginPlay() override;*/

	

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess= true))
	bool IsAttacking = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess= true))
	bool IsClicking = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess= true))
	AAHNPCVehicleBase* ChaseNPC = nullptr;
};
