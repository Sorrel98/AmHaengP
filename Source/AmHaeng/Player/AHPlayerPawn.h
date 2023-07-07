// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "AHPlayerPawn.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(FMannequinDetect)
UCLASS()
class AMHAENG_API AAHPlayerPawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()

public:
	void MouseClick();
	void MouseClickReleased();
	void MouseDelegate(bool IsClick);
	virtual void BeginPlay() override;

	//Chicken Blade
	UFUNCTION(BlueprintNativeEvent)
	void ChickenAttack();
	UFUNCTION(BlueprintCallable)
	void SetChickenRotate(FRotator RotateRate);
	UFUNCTION(BlueprintCallable)
	void ChickenAttackFinish();
	
	FMannequinDetect MannequinDetect;

	UFUNCTION(BlueprintCallable)
	void PlayerMannequinDetect();

	UFUNCTION(BlueprintNativeEvent)
	void GetSkeletalMesh();

	USkeletalMeshComponent* GetPlayerPawnSkeletalMesh();
	UStaticMeshComponent* GetMannequinDestMeshComponent();

private:
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	USkeletalMeshComponent* WeaponComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TSubclassOf<class AAHChickenBlade> ChickenBladeClass;
	TObjectPtr<AAHChickenBlade> ChickenBlade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	class USkeletalMeshComponent* PlayerSkeletalMeshComponent;

	uint8 IsAttacking;

	FRotator OriginChickenRotation;
};
