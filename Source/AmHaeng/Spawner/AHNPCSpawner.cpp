// Fill out your copyright notice in the Description page of Project Settings.


#include "AHNPCSpawner.h"

AHNPCSpawner::AHNPCSpawner()
{
	SpawnLocations.Emplace(FVector(11650.0f, 3560.0f, 0.0f));
	SpawnLocations.Emplace(FVector(-9030.0f, -770.0f, 0.0f));
	SpawnLocations.Emplace(FVector(2293.372449f, 10120.637944f, 0.0f));
	SpawnLocations.Emplace(FVector(421.089786f, -1400.890789f, 0.0f));
	SpawnLocations.Emplace(FVector(-6150.0f, 5310.0f, 0.0f));
	SpawnLocations.Emplace(FVector(4030.0f, 5600.0f, 0.0f));
}

AHNPCSpawner::~AHNPCSpawner()
{
}
