// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "AmHaeng/Interface/NPC/AHScannable.h"
#include "AmHaeng/Interface/NPC/AHTargetNPC.h"
#include "AmHaeng/Widget/NPC/AHNPCHPWidget.h"
#include "Stat/AHNPCStatComponent.h"
#include "AHNPCVehicleBase.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FDeadNPCDelegate, bool)
UCLASS()
class AMHAENG_API AAHNPCVehicleBase : public AWheeledVehiclePawn, public IAHScannable, public IAHTargetNPC
{
	GENERATED_BODY()

public:
	AAHNPCVehicleBase();
	virtual void BeginPlay() override;

	void BroadCastNPCArrestedDelegate();
	FDeadNPCDelegate NPCArrestedDelegate;

	//NPC info - bIsTargetNPC
	virtual bool GetIsTargetNPC() override;
	virtual void SetIsTargetNPC(const uint8& IsTarget) override;

	//MouseScan
	void MouseScaned();
	void MouseUnscaned();
	
	//set info widget
	void SetInfoWidget();
	void SetNPCHPWidget();
	void SetNPCStatAndInfoWidget(int32 NPCID);
	virtual void SetNPCInfoWidgetVisible(bool visible) override;

	//Set HP Widget
	void SetHPWidget();
	
	//Click Tooltip
	void AHSetTooltipVisible(bool visible) const;

	//Test NPC Setting, 사용 안 함
	/*void TESTGoodNPCInfoSetting();
	void TESTBadNPCInfoSetting();*/

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetOutline(bool bOutlineEnabled);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SlowDown();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Brake();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DetectNothing();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void JustMaxEngineTorque(float InMaxTorque);

	//Chase 기믹
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AHSetMaxEngineTorque(float InMaxTorque);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AHDestroyFrontSphere();
	UFUNCTION(BlueprintCallable)
	void SetIsChased(bool IsChased);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetIsChased(){ return bIsChased; }
	
	UFUNCTION(BlueprintCallable)
	void NPCHPDown();

private:
	//NPC info - Main
	//true : 범법, false : 일반
	uint8 bIsTargetNPC : 1;

	//Info Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	TSubclassOf<class UAHNPCInfoWidget> NPCInfoWidgetClass;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAHNPCInfoWidget> NPCInfoWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	TObjectPtr<class UWidgetComponent> NPCInfoWidgetComponent;

	//NPC Stat Component
	UPROPERTY(VisibleAnywhere, Category=Stat)
	TObjectPtr<UAHNPCStatComponent> NPCStat;

	//HP Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	TSubclassOf<UAHNPCHPWidget> NPCHPWidgetClass;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAHNPCHPWidget> NPCHPWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	TObjectPtr<UWidgetComponent> NPCHPWidgetComponent;
	
	//Other NPC Detection
	/*float DetectionDistance;
	float BrakeDistance;
	uint8 bIsAnotherNPCForward;
	uint8 bIsDetected;*/

	//Chase 기믹
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	bool bIsChased;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TObjectPtr<UChaosVehicleMovementComponent> NowNPCChaosVehicleMovementComponent;
};
