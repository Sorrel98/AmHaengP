// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AHMannequin.generated.h"

UCLASS()
class AMHAENG_API AAHMannequin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAHMannequin();

	FORCEINLINE USkeletalMeshComponent* GetSkeletalMeshComponent(){ return SkeletalMeshComponent; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* SkeletalMeshComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
