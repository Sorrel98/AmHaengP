// Fill out your copyright notice in the Description page of Project Settings.


#include "AHNPCTeleport.h"

#include "AmHaeng/Gimmick/BeforeChase/AHBeforeChase.h"
#include "AmHaeng/Player/AHVehiclePlayerController.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"
#include "Kismet/GameplayStatics.h"

void UAHNPCTeleport::SetTeleportLocations()
{
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("NPCRunAwayLocation"), NPCTeleportLocationActors);
}

void UAHNPCTeleport::Teleport(AAHNPCVehicleBase* InTargetNPC)
{
	SetTeleportLocations();

	if(GetWorld())
	{
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		if(PC)
		{
			AAHVehiclePlayerController* AHPC = Cast<AAHVehiclePlayerController>(PC);
			if(AHPC)
			{
				APawn* PlayerPawn = AHPC->GetPawn();
				if(PlayerPawn)
				{
					FVector PlayerLocation = PlayerPawn->GetActorLocation();
					AActor* FarActor = GetFarTeleportActor(PlayerLocation);
					if(FarActor)
					{
						InTargetNPC->GetMesh()->SetSimulatePhysics(false);
						InTargetNPC->SetActorLocation(FarActor->GetActorLocation());
						InTargetNPC->GetMesh()->SetSimulatePhysics(true);
					}
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("World is wrong"));
	}
}


AActor* UAHNPCTeleport::GetFarTeleportActor(FVector InCriterion)
{
	AActor* MaxDistanceActor = nullptr;
	float MaxDistance = 0;
	for(AActor* NPCTeleportActor : NPCTeleportLocationActors)
	{
		float NowDistance = FVector::Distance(NPCTeleportActor->GetActorLocation(), InCriterion);
		if(MaxDistance < NowDistance)
		{
			MaxDistance = NowDistance;
			MaxDistanceActor = NPCTeleportActor;
		}
	}
	return MaxDistanceActor;
}
