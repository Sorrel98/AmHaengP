// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AHScannable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAHScannable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AMHAENG_API IAHScannable
{
	GENERATED_BODY()

public:

	virtual void SetNPCInfoWidgetVisible(bool visible){ }
};
