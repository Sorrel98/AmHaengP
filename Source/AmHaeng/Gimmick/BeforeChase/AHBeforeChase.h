// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AHBeforeChase.generated.h"

DECLARE_DELEGATE(FStartChaseDelegate)
UCLASS(Blueprintable, BlueprintType)
class AMHAENG_API AAHBeforeChase : public AActor
{
	GENERATED_BODY()
public:
	AAHBeforeChase();
	void BeforeChaseProcess(class AAHVehiclePlayerController* PC, class AAHNPCVehicleBase* InTargetNPC);
	void PlayChaseStartAnim();
	void SettingChaseStartWidget();

	UFUNCTION()
	void FinishChaseStartWidget();

	void SetPause(bool InPause);
	void RagdollMannequinSpawn();
	void ThrowMannequin();
	void CameraShake();

	void PlayCrashWidget();

	FStartChaseDelegate StartChaseDelegate;

private:
	//Gimmick Mode Widget
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UAHChaseStartWidget> ChaseStartWidgetClass;
	TObjectPtr<UAHChaseStartWidget> ChaseStartWidget = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UAHScreenCrashWidget> CameraCrashClass;
	TObjectPtr<UAHScreenCrashWidget> CameraCrashWidget;

	//CameraShake
	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShakeBase> CameraShakeClass;

	AAHVehiclePlayerController* PlayerController;
	TObjectPtr<AAHNPCVehicleBase> ChasedNPC;
	
	//Ragdoll Mannequin
	TObjectPtr<class AAHMannequin> Mannequin;

	FTimerHandle TempTimer;

	

};
