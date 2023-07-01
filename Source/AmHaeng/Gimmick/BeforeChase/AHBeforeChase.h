// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AHBeforeChase.generated.h"

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



private:
	//Gimmick Mode Widget
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UAHChaseStartWidget> ChaseStartWidgetClass;
	UAHChaseStartWidget* ChaseStartWidget = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UAHScreenCrashWidget> CameraCrashClass;
	class UAHScreenCrashWidget* CameraCrashWidget;


	AAHVehiclePlayerController* PC;
	AAHNPCVehicleBase* TargetNPC;
	class AAHPlayerPawn* PlayerPawn;
	
	//Ragdoll Mannequin
	class AAHMannequin* Mannequin;
	class AAHThrowMannequin* ThrowManager;

	//CameraShake
	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShakeBase> CameraShakeClass;

};
