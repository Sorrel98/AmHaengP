// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AHThrowMannequin.generated.h"

UCLASS()
class AMHAENG_API AAHThrowMannequin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAHThrowMannequin();

	UFUNCTION(BlueprintCallable, Category="ThrowMannequin")
	void Throw(AActor* From, AActor* To, AAHMannequin* Mannequin);

	

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ThrowMannequin", meta=(AllowPrivateAccess = true))
	float ThrowSpeed;

};
