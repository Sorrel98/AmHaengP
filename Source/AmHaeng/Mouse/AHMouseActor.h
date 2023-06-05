// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AHNPCClickCPWidget.generated.h"
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
	TSubclassOf<UUserWidget> CPWidgetClass;
	UAHNPCClickCPWidget* CPWidget;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetCPWidgetVisiblity(bool Visible);

	void CPWidgetOnViewport();

private:
};
