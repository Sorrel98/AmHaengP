// Fill out your copyright notice in the Description page of Project Settings.


#include "AHPlayerPawn.h"

void AAHPlayerPawn::PlayerMannequinDetect()
{
	UE_LOG(LogTemp, Log, TEXT("Mannequin is Detected"));
	if(MannequinDetect.IsBound())
	{
		MannequinDetect.Execute();
	}
}
