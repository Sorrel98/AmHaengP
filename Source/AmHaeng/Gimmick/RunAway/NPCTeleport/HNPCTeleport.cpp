// Fill out your copyright notice in the Description page of Project Settings.


#include "HNPCTeleport.h"

#include "AmHaeng/Player/AHVehiclePlayerController.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"
#include "Kismet/GameplayStatics.h"

void UAHNPCTeleport::SetTeleportLocations()
{
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("NPCSpawnLocation"), NPCTeleportLocationActors);
	/*for (AActor* NPCTeleportActor : NPCTeleportLocationActors)
	{
		TeleportLocations.Add(NPCTeleportActor->GetActorLocation());
		TeleportRotations.Add(NPCTeleportActor->GetActorRotation());
	}*/
}

void UAHNPCTeleport::Teleport(AAHNPCVehicleBase* InTargetNPC)
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	AAHVehiclePlayerController* AHPC = Cast<AAHVehiclePlayerController>(PC);
	APawn* PlayerPawn = AHPC->GetPawn();
	FVector PlayerLocation = PlayerPawn->GetActorLocation();
	InTargetNPC->SetActorLocation(GetFarTeleportActor(PlayerLocation)->GetActorLocation());
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
