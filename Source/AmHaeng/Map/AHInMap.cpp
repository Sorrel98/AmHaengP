// Fill out your copyright notice in the Description page of Project Settings.


#include "AHInMap.h"

#include "AmHaeng/Game/AHGameMode.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"
#include "Components/BoxComponent.h"

class UBoxComponent;

void AAHInMap::NPCIsOutOfMap(AAHNPCVehicleBase* OutNPC)
{
	if(Spawner==nullptr)
	{
		SetSpawner();
	}
	OutNPC->Destroy();
	GetWorld()->GetTimerManager().SetTimer(FindSpawnerTimerHandle, this, &AAHInMap::SpawnNewNPC, 5.0f, true);
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

bool AAHInMap::IsHitActorOnSpawnActor(int32 TeleportLocationIndex)
{
	AActor* TeleportActor = Spawner->GetTeleportLocationActor(TeleportLocationIndex);
	TArray<UActorComponent*> Components = TeleportActor->GetComponentsByTag(UActorComponent::StaticClass(), FName(TEXT("NPCCollision")));
	UBoxComponent* TeleportActorCollision = nullptr;
	bool bResult = false;
	if(!Components.IsEmpty())
	{
		TeleportActorCollision = Cast<UBoxComponent>(Components[0]);
		if(GetWorld())
		{
			FHitResult OutHitResult;
			FVector Start = TeleportActorCollision->GetComponentLocation();
			FCollisionShape Box = FCollisionShape::MakeBox(TeleportActorCollision->GetScaledBoxExtent()/2);
			FVector End = Start;
			bResult = GetWorld()->SweepSingleByProfile(OutHitResult, Start, End, TeleportActorCollision->GetComponentRotation().Quaternion(), FName(TEXT("BlockAll")), Box);
			DrawDebugBox(GetWorld(), Start, TeleportActorCollision->GetScaledBoxExtent(), bResult ? FColor::Red : FColor::Yellow, false, 30.f);
			//무엇인가 있었다면 true
		}
	}
	//없었다면 false
	return bResult;
}

int32 AAHInMap::SetRandomIndex()
{

	SpawnIndex = FMath::RandRange(0, Spawner->GetSpawnLocationNumber()-1);
	UE_LOG(LogTemp, Log, TEXT("Make Random Index : %d"), SpawnIndex);
	return SpawnIndex;
	
}

void AAHInMap::SpawnNewNPC()
{
	if(!IsHitActorOnSpawnActor(SetRandomIndex()))
	{
		//없었다면
		if(FindSpawnerTimerHandle.IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(FindSpawnerTimerHandle);
			Spawner->SpecificLocationNPCVehicleSpawn(Spawner->GetTeleportLocationActor(SpawnIndex));
		}
		//있었다면 계속 Timer 돌아가게
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Something On Spawn Location Actor"));
		}
	}
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

