// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmHaeng/Widget/NPC/AHNPCClickCPWidget.h"
#include "Components/WidgetComponent.h"
#include "AHMouseActor.generated.h"

DECLARE_MULTICAST_DELEGATE(FClickCPLoadingDelegate);
UCLASS()
class AMHAENG_API AAHMouseActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAHMouseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Widgets")
	TObjectPtr<UAHNPCClickCPWidget> CPWidget;

	void SetCPWidgetVisibility(bool Visible) const;
	void InitCPWidget();
	
	void ClickTimerFinishDelegateBind();

	FClickCPLoadingDelegate ClickCPLoadingDelegate;

private:
	void SetBindDelegate();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	TSubclassOf<UAHNPCClickCPWidget> CPWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	TObjectPtr<class UWidgetComponent> CPWidgetComponent;
	
};
