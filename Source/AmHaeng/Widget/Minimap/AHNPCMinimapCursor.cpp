// Fill out your copyright notice in the Description page of Project Settings.


#include "AHNPCMinimapCursor.h"

void UAHNPCMinimapCursor::SetNPCActor(AAHNPCVehicleBase* InNPCActor)
{
	NPCActor = InNPCActor;
}

void UAHNPCMinimapCursor::NPCCursorDestroy()
{
	this->RemoveFromParent();
}


void UAHNPCMinimapCursor::SetNPCCursorRed_Implementation()
{
}
