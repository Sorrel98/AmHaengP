// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AHHUD.generated.h"

/**
 * 
 */
UCLASS()
class AMHAENG_API AAHHUD : public AHUD
{
	GENERATED_BODY()
public:
	void HUDOnViewport(int32 InitReputationValue, int32 PastSecond);

	void DrawWorldWidget();
	void DrawIsTargetWidget();
	void DrawMinimap();

	class UAHWorldWidget* GetWorldWidget(){ return WorldWidget;}
	class UAHNPCIsTargetWidget* GetIsTargetWidget(){ return NPCIsTargetWidget;}
	class UAHMinimapWidget* GetMinimap(){ return MinimapWidget;}
	
protected:
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;
	
public:
	//WorldWidget
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAHWorldWidget> WorldWidgetClass;
	TObjectPtr<UAHWorldWidget> WorldWidget;

	//NPCIsTarget Widget
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> NPCIsTargetWidgetClass;
	TObjectPtr<UAHNPCIsTargetWidget> NPCIsTargetWidget;

	//Minimap Widget
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAHMinimapWidget> MinimapWidgetClass;
	TObjectPtr<UAHMinimapWidget> MinimapWidget;

	int32 InitReputationValue;
	int32 PastSecond;
};
