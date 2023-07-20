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
	FStartChaseDelegate StartChaseDelegate;
	
	void BeforeChaseProcess(class AAHVehiclePlayerController* PC, class AAHNPCVehicleBase* InTargetNPC);

	//Chase Start Widget & Anim
	void PlayChaseStartAnim();
	void SettingChaseStartWidget();
	UFUNCTION()
	void FinishChaseStartWidget();

	//Pause
	//void SetPause(bool InPause);
	
	//Mannequin
	void RagdollMannequinSpawn();
	void ThrowMannequin();

	//Crash
	void CameraShake();
	void PlayCrashWidget();

private:
	FTimerHandle TempTimer;
	
	//Gimmick Mode Widget
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UAHChaseStartWidget> ChaseStartWidgetClass;
	TObjectPtr<UAHChaseStartWidget> ChaseStartWidget = nullptr;

	//Camera Crash Widget
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UAHScreenCrashWidget> CameraCrashClass;
	TObjectPtr<UAHScreenCrashWidget> CameraCrashWidget;

	//CameraShake
	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShakeBase> CameraShakeClass;
	
	TObjectPtr<AAHVehiclePlayerController> PlayerController;
	TObjectPtr<AAHNPCVehicleBase> ChasedNPC;
	
	//Ragdoll Mannequin
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true))
	TSubclassOf<class AAHMannequin> MannequinClass;
	TObjectPtr<AAHMannequin> Mannequin;
};
