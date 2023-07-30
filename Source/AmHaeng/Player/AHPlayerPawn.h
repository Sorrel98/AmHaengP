// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "Components/CapsuleComponent.h"
#include "AHPlayerPawn.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(FMannequinDetect)
DECLARE_MULTICAST_DELEGATE_OneParam(FReputationChangeDelegate, uint32)

UCLASS()
class AMHAENG_API AAHPlayerPawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	//Mennequin
	FMannequinDetect MannequinDetect;

	//Reputation
	static uint32 Reputation;

	//Mouse Click
	UFUNCTION(BlueprintNativeEvent)
	void MouseClick();
	void MouseClickReleased();
	UFUNCTION()
	void ChaseMouseDelegate(bool IsClick);
	void ChaseMouseDelegateBind();
	void SpawnChickenBlade();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Brake();
	UFUNCTION(BlueprintNativeEvent)
	void SetSkeletalMesh();
	USkeletalMeshComponent* GetPlayerPawnSkeletalMesh();

	//NowSpeed
	UFUNCTION(BlueprintNativeEvent)
	void SetNowSpeedFromBP();
	float GetNowSpeed(){return PlayerNowSpeed;}

	//Chicken Blade
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ChickenRotation();
	UFUNCTION(BlueprintCallable)
	void SetChickenRotate(FRotator RotateRate);
	UFUNCTION(BlueprintCallable)
	void ChickenAttackFinish();
	class AAHChickenBlade* GetChickenBlade(){ return ChickenBlade; }
	UFUNCTION(BlueprintCallable)
	void SetChickenVisible(bool Visible);
	
	//Mannequin
	UFUNCTION(BlueprintCallable)
	void PlayerMannequinDetect();
	UStaticMeshComponent* GetMannequinTarget(){return MannequinTarget;}
	UFUNCTION(BlueprintNativeEvent)
	void SetMannequinDestMeshComponent();
	
	//Gimmick
	void RaisingReputation();
	void DecreasingReputation();

private:
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> WeaponComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TSubclassOf<class AAHChickenBlade> ChickenBladeClass;
	TObjectPtr<AAHChickenBlade> ChickenBlade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TObjectPtr<UCapsuleComponent> ChickenBladeCapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> PlayerSkeletalMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	bool IsChickenRotating;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	bool AlreadyAttacked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> MannequinTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	float PlayerNowSpeed;
};
