// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "AmHaeng/Interface/NPC/AHScannable.h"
#include "AmHaeng/Interface/NPC/AHTargetNPC.h"
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
	//virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AHSetMaxEngineTorque(float InMaxTorque);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	
	void AHDestroyFrontSphere();

	//NPC info - bIsTargetNPC
	virtual bool GetIsTargetNPC() override;
	virtual void SetIsTargetNPC(const uint8& IsTarget) override;


	void SetMassOne();
	
	//set info widget
	void SetInfoWidget();
	void SetGoodInfoWidgetData(int32 NPCID);
	void SetBadInfoWidgetData(int32 NPCID);
	virtual void SetNPCInfoWidgetVisible(bool visible) override;

	//Click Tooltip
	void AHSetTooltipVisible(bool visible) const;

	//Test NPC Setting
	void TESTGoodNPCInfoSetting();
	void TESTBadNPCInfoSetting();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetOutline(bool bOutlineEnabled);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SlowDown();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Brake();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DetectNothing();

	//Chase 기믹
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetIsChased(uint8 IsChased){ bIsChased = IsChased; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE uint8 GetIsChased(){ return bIsChased; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void FinishChased();


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

	//Chase 기믹
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	uint8 bIsChased;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	UChaosVehicleMovementComponent* NowNPCChaosVehicleMovementComponent;
};
