// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class AMHAENG_API AHNPCSpawner
{
public:
	AHNPCSpawner();
	~AHNPCSpawner();
private:
	TArray<FVector> SpawnLocations;
};
