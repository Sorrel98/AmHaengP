// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmHaeng/Widget/AHNPCClickCPWidget.h"
#include "AHMouseActor.generated.h"

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
	TSubclassOf<UAHNPCClickCPWidget> CPWidgetClass;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Widgets")
	class UAHNPCClickCPWidget* CPWidget;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetCPWidgetVisiblity(bool Visible);
	void SetCPWidget();
	void CPWidgetOnViewport();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	TObjectPtr<class UWidgetComponent> CPWidgetComponent;
};
