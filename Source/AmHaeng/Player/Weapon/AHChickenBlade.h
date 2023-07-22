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
	virtual void BeginPlay() override;

	ChickenAttackFinish ChickenAttackFinishDelegate;
	void MouseClickDelegate(bool IsClick);
	
	void InitChickenBlade(AAHNPCVehicleBase* ChasedNPC);

	//Capsule Component
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetChickenBladeCapsuleComponent();
	UCapsuleComponent* GetChickenBladeCapsuleComponent(){return CapsuleComponent;}

	//Mesh
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetChickenMesh();

	//Visible
	void SetChickenVisible(bool Visible);

	//Sound
	void ChickenAttackSound();
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess= true))
	TObjectPtr<AAHNPCVehicleBase> ChaseNPC = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess= true))
	TObjectPtr<AAHPlayerPawn> PlayerPawn = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess= true))
	TObjectPtr<UCapsuleComponent> CapsuleComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess= true))
	TObjectPtr<USkeletalMeshComponent> ChickenSkeletal = nullptr;
};
