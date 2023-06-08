// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmHaeng/Mouse/AHMouseActor.h"
#include "GameFramework/PlayerController.h"
#include "Components/WidgetComponent.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"
#include "AHVehiclePlayerController.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(MouseClickDelegate, bool)
DECLARE_DELEGATE_OneParam(TooltipDelegate, bool)

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


	//==============================
	//사용자 지정 함수 및 변수들
	//==============================	
public:
	//Called every frame;
	virtual void Tick(float DeltaTime) override;
	void InVisiblePrevWidget(AActor* PrevActor);
	void DrawShpere(FHitResult HitResult);

	void MouseScan();

	void WidgetVisibleByMouseScan(AActor* HitActor);

	//mouse Click Binding Functions
	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintCallable)
	FVector GetMouseLocation() { return MousePosition; }

	MouseClickDelegate MouseClickDelegate;

	TooltipDelegate TTDelegate;

private:
	UPROPERTY(EditAnywhere, Category = Scan)
	float ScanDistance;

	//FString MouseHitActorName;
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"))
	uint8 IsNPCScanning = false;

	AActor* MousePrevActor;


	//mouse input system
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ClickReleasedAction;

	void MouseClick();
	void MouseClickReleased();

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"))
	uint8 IsNPCClicking = false;

	//click Circular Progressbar UI
	FVector MousePosition;

	AActor* NowHitActor;

	AAHMouseActor* MouseActor;
};
