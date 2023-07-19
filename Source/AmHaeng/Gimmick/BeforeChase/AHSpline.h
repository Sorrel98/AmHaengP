// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmHaeng/Player/AHPlayerPawn.h"
#include "GameFramework/Actor.h"
#include "AHSpline.generated.h"

UCLASS()
class AMHAENG_API AAHSpline : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ThrowMannequin", meta=(AllowPrivateAccess = true))
	float ThrowSpeed;
};
