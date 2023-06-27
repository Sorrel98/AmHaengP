// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "AmHaeng/Interface/AHScannable.h"
#include "AmHaeng/Interface/AHTargetNPC.h"
#include "AHNPCVehicleBase.generated.h"

/**
 * 
 */
UCLASS()
class AMHAENG_API AAHNPCVehicleBase : public AWheeledVehiclePawn, public IAHScannable, public IAHTargetNPC
{
	GENERATED_BODY()

public:
	AAHNPCVehicleBase();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	//NPC info - bIsTargetNPC
	virtual bool GetIsTargetNPC() override;
	virtual void SetIsTargetNPC(const uint8& IsTarget) override;


	//set info widget
	void SetInfoWidget();
	void SetInfoWidgetData();
	virtual void SetNPCInfoWidgetVisible(bool visible) override;

	//Click Tooltip
	void AHSetTooltipVisible(bool visible);

	//Test NPC Setting
	void GoodNPCInfoSetting();
	void BadNPCInfoSetting();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetOutline(bool bOutlineEnabled);

	//Other NPC Detection
	UFUNCTION(BlueprintCallable)
	void SetRay();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SlowDown();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Brake();

	void RayDebugDraw(const FVector& InStartLocation, const FVector& InEndLocation, uint8 bDetected) const;

	void DetectNPC(AAHNPCVehicleBase* NPCActor);

private:
	//NPC info - Main
	//true(1) : 범법, false(2) : 일반
	uint8 bIsTargetNPC : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	TObjectPtr<class UWidgetComponent> NPCInfoWidgetComponent;

	//NPC Stat Component
	UPROPERTY(VisibleAnywhere, Category=Stat)
	class UAHNPCStatComponent* NPCStat;

	TObjectPtr<class UAHNPCInfoWidget> NPCInfoWidget;

	//Other NPC Detection
	float DetectionDistance;

	float BrakeDistance;

	uint8 bIsAnotherNPCForward;

	uint8 bIsDetected;
};
