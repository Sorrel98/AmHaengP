// Fill out your copyright notice in the Description page of Project Settings.


#include "AHMannequin.h"

#include "AmHaeng/Game/AHGameMode.h"
#include "Components/SkeletalMeshComponent.h"

void AAHMannequin::SetSplineRoute_Implementation(FVector Start, FVector End)
{
}

void AAHMannequin::Throw_Implementation()
{
}

AAHSpline* AAHMannequin::GetSplineActor()
{
	if(AAHGameMode::SplineActor)
	{
		return AAHGameMode::SplineActor;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("SplineActor is null"));
		return nullptr;
	}
}

