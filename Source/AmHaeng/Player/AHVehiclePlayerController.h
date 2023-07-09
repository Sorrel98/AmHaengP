// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingQuery.h"
#include "AmHaeng/Game/AHGameMode.h"
#include "GameFramework/PlayerController.h"
#include "AmHaeng/Player/AHPlayerPawn.h"
#include "AHVehiclePlayerController.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FPatrolMouseClickDelegate, bool)
DECLARE_MULTICAST_DELEGATE_OneParam(FChaseMouseClickDelegate, bool)
DECLARE_DELEGATE_OneParam(FTooltipDelegate, bool)
DECLARE_DELEGATE_OneParam(FNowClickNPCToGameModeDelegate, class AAHNPCVehicleBase*)

UCLASS()
class AMHAENG_API AAHVehiclePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	//sets default values for this character controller's properties
	AAHVehiclePlayerController();

	//Static
	static AAHPlayerPawn* PlayerPawn;

protected:
	//Called when the game starts or when spawned
	virtual void BeginPlay() override;


	//==============================
	//사용자 지정 함수 및 변수들
	//==============================	
public:
	//Called every frame;
	virtual void Tick(float DeltaTime) override;
	void DrawShpere(FHitResult HitResult);

	void MouseScan();

	void WidgetVisibleByMouseScan(AActor* HitActor);
	void WidgetInVisibleByMouseScan(AActor* HitActor);

	//mouse Click Binding Functions
	virtual void SetupInputComponent() override;
	UFUNCTION(BlueprintCallable)
	FVector GetMouseLocation() { return MousePosition; }
	void SetInitMousePrevActor();


	//Input mapping
	void PatrolMouseClick();
	void PatrolMouseClickReleased();
	UFUNCTION()
	void ChaseMouseClick();
	void ChaseMouseClickReleased();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetChaseIMC();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetPatrolIMC();
	
	//const uint8 GetIsNPCTarget();
	
	//Delegate
	FPatrolMouseClickDelegate PatrolMouseClickDelegate;
	FNowClickNPCToGameModeDelegate SendNowClickNPCToGameMode;
	FChaseMouseClickDelegate ChaseMouseClickDelegate;

private:
	UPROPERTY(EditAnywhere, Category = Scan)
	float ScanDistance;

	//FString MouseHitActorName;
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"))
	uint8 IsNPCScanning = false;

	AActor* MousePrevActor;


	//mouse input system
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> PatrolClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> PatrolClickReleasedAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ChaseClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ChaseClickReleasedAction;



	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"))
	uint8 IsNPCClicking = false;

	//click Circular Progressbar UI
	FVector MousePosition;

	AActor* NowHitActor;
};
