// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "AHVehiclePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AMHAENG_API AAHVehiclePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	//sets default values for this character controller's properties
	AAHVehiclePlayerController();
protected:
	//Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	//Called every frame;
	virtual void Tick(float DeltaTime) override;

	void MouseScan();

	void WidgetVisibleByMouseScan(AActor* HitActor);

private:
	UPROPERTY(EditAnywhere, Category = Scan)
	float ScanDistance;

	//FString MouseHitActorName;

	bool VisibleWidgetOnce = false;

	AActor* MousePrevActor;
	
};
