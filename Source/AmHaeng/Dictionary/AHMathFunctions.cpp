// Fill out your copyright notice in the Description page of Project Settings.


#include "AHMathFunctions.h"
int32 AHMathFunctions::GetRandomIndex(const int32 TArraySize)
{
	return FMath::RandRange(0, TArraySize-1);
}
