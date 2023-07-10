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
UCLASS()
class AMHAENG_API AAHPlayerPawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void MouseClick();
	void MouseClickReleased();
	void ChaseMouseDelegate(bool IsClick);
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Brake();

	//Chicken Blade
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ChickenRotation();
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

	UFUNCTION(BlueprintNativeEvent)
	void SetMannequinDestMeshComponent();

	UStaticMeshComponent* GetMannequinTarget(){return MannequinTarget;}


	//Chicken Actor
	UFUNCTION(BlueprintCallable)
	void SetChickenVisible(bool Visible);
	
	/*UFUNCTION(BlueprintCallable)
	void SetInputEnable();*/
	
	class AAHChickenBlade* GetChickenBlade(){ return ChickenBlade; }
	

	/*UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetChickenCapsuleComponent();*/

private:
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	USkeletalMeshComponent* WeaponComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TSubclassOf<class AAHChickenBlade> ChickenBladeClass;
	TObjectPtr<AAHChickenBlade> ChickenBlade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	UCapsuleComponent* ChickenBladeCapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	class USkeletalMeshComponent* PlayerSkeletalMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	bool IsChickenRotating;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	bool AlreadyAttacked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	UStaticMeshComponent* MannequinTarget;
};
