// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "AHMannequin.generated.h"

UCLASS()
class AMHAENG_API AAHMannequin : public AActor
{
	GENERATED_BODY()
	
public:	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetSplineRoute(FVector Start, FVector End);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Throw();
	UFUNCTION(BlueprintCallable)
	class AAHSpline* GetSplineActor();
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* SkeletalMeshComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USplineComponent* Spline;
};
