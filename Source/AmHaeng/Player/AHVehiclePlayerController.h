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
	void SetPlayerPawn();

	//Static
	static TObjectPtr<AAHPlayerPawn> PlayerPawn;

	//Delegate
	FPatrolMouseClickDelegate PatrolMouseClickDelegate;
	FNowClickNPCToGameModeDelegate SendNowClickNPCToGameMode;
	FChaseMouseClickDelegate ChaseMouseClickDelegate;

protected:
	//Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//Called every frame;
	virtual void Tick(float DeltaTime) override;

	//사용하지 않음
	void DrawShpere(FHitResult HitResult);

	void MouseScan();
	//Info Widget by Mouse Scan
	void NPCMouseScaned(AActor* HitActor);
	void NPCMouseUnscaned(AActor* HitActor);

	//mouse Click Binding Functions
	virtual void SetupInputComponent() override;
	void SetInitMousePrevActor();
	UFUNCTION(BlueprintCallable)
	FVector GetMouseLocation() { return MousePosition; }
	
	//Input mapping
	UFUNCTION()
	void PatrolMouseClick();
	UFUNCTION()
	void PatrolMouseClickReleased();
	UFUNCTION()
	void ChaseMouseClick();
	UFUNCTION()
	void ChaseMouseClickReleased();

	//IMC
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetChaseIMC();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetPatrolIMC();

	//Player Pawn
	UFUNCTION(BlueprintCallable)
	AAHPlayerPawn* GetPlayerPawn(){ return PlayerPawn; }

	//Chase Finish
	void ChaseFinished();

private:
	//mouse input system
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> PatrolClickAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> PatrolClickReleasedAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ChaseClickAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ChaseClickReleasedAction;
	
	UPROPERTY(EditAnywhere, Category = Scan)
	float ScanDistance;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"))
	uint8 IsNPCScanning = false;
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"))
	uint8 IsNPCClicking = false;

	FVector MousePosition;
	TObjectPtr<AActor> MousePrevActor;
	TObjectPtr<AActor> NowHitActor;
	
	TObjectPtr<AAHNPCVehicleBase> ChasedNPC = nullptr;
};
