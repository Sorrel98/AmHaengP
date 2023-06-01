// Fill out your copyright notice in the Description page of Project Settings.


#include "AHNPCInfoWidget.h"
#include "Components/TextBlock.h"

UAHNPCInfoWidget::UAHNPCInfoWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UAHNPCInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ensure(TB_Owner);
	ensure(TB_License);
	ensure(TB_MinSpeed);
	ensure(TB_MaxSpeed);
	ensure(TB_Sway);
	
	
}