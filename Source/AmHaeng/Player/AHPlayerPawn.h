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
	virtual void BeginPlay() override;
	
	FMannequinDetect MannequinDetect;

	UFUNCTION(BlueprintCallable)
	void PlayerMannequinDetect();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void GetWeaponFromBP();

	UFUNCTION(BlueprintNativeEvent)
	void GetSkeletalMesh();

	USkeletalMeshComponent* GetPlayerPawnSkeletalMesh();


	USkeletalMeshComponent* GetWeaponComponent();
private:
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	USkeletalMeshComponent* WeaponComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TSubclassOf<class AAHChickenBlade> ChickenBladeClass;
	TObjectPtr<AAHChickenBlade> ChickenBlade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	class USkeletalMeshComponent* PlayerSkeletalMeshComponent;
};
