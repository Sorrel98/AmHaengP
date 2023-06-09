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
	void PlayChaseStartWidget();

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
	UAHChaseStartWidget* ChaseStartWidget = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UAHScreenCrashWidget> CameraCrashClass;
	class UAHScreenCrashWidget* CameraCrashWidget;

	//CameraShake
	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShakeBase> CameraShakeClass;

	AAHVehiclePlayerController* PC;
	AAHNPCVehicleBase* TargetNPC;
	
	//Ragdoll Mannequin
	class AAHMannequin* Mannequin;

	

};
