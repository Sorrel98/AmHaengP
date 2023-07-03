// Fill out your copyright notice in the Description page of Project Settings.


#include "AHInMap.h"

#include "AmHaeng/Game/AHGameMode.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"

void AAHInMap::NPCIsOutOfMap(AAHNPCVehicleBase* OutNPC)
{
	if(Spawner==nullptr)
	{
		SetSpawner();
	}
	OutNPC->Destroy();
	int32 SpawnLocation;
	do
	{
		SpawnLocation = FMath::RandRange(0, Spawner->GetSpawnLocationNumber()-1);
		Spawner->SpecificLocationNPCVehicleSpawn(SpawnLocation);
	}while(IsHitActorOnSpawnActor(Spawner->GetSpawnLocationByIndex(SpawnLocation)));
}

void AAHInMap::SetSpawner()
{
	AGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode();
	if(GameModeBase)
	{
		AAHGameMode* AHGameMode = Cast<AAHGameMode>(GameModeBase);
		if(AHGameMode)
		{
			Spawner = AHGameMode->GetSpawner();
		}
	}
}

bool AAHInMap::IsHitActorOnSpawnActor(FVector SpawnActorLocation)
{
	FHitResult OutHit;
	FVector RaycastEndLocation = SpawnActorLocation + FVector(0.f, 0.f, 1.f) * 10;

	FCollisionQueryParams Params;
	Params.bTraceComplex = true; // 자세한 충돌 검사를 위해 true로 설정
	if (GetWorld()->LineTraceSingleByChannel(OutHit, SpawnActorLocation, RaycastEndLocation, ECC_Pawn, Params))
	{
		// 충돌이 감지되었을 때 처리
		AActor* HitActor = OutHit.GetActor();
		AAHNPCVehicleBase* HittedNPC = Cast<AAHNPCVehicleBase>(HitActor);
		if(HittedNPC)
		{
			return true;
		}
	}
	return false;
}

// Called when the game starts or when spawned
void AAHInMap::BeginPlay()
{
	Super::BeginPlay();
	SetSpawner();
}

// Called every frame
void AAHInMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

