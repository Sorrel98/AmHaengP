// Fill out your copyright notice in the Description page of Project Settings.


#include "AHAfterChase.h"

// Sets default values
AAHAfterChase::AAHAfterChase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AAHAfterChase::AfterChaseProcess()
{
}

// Called when the game starts or when spawned
void AAHAfterChase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAHAfterChase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

