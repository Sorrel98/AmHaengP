// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Components/WidgetComponent.h"
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

	//Mouse Click CP Widget
	void SettingCPWidget();

	UFUNCTION(BlueprintCallable)
	FVector GetMouseLocation();

	
private:
	UPROPERTY(EditAnywhere, Category = Scan)
	float ScanDistance;

	//FString MouseHitActorName;
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"))
	uint8 IsNPCScanning = false;

	AActor* MousePrevActor;
	
	//Mouse Scan Timer -> 삭제 예정 (마우스 스캔을 시간 재는 것이 아닌, 마우스 스캔 시 클릭이 활성화되고 클릭 시간을 재는 방향으로)
	FTimerHandle ScanTimer;
	AActor* NowHitActor;

	//mouse input system
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ClickAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ClickReleasedAction;

	void MouseClick();
	void MouseClickReleased();

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"))
	uint8 IsNPCClicking = false;


	//click Circular Progressbar UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	UWidgetComponent* NPCClickCPWidgetComponent;

	FVector MousePosition;

	class UAHNPCClickCPWidget* NPCClickWidget;
};
