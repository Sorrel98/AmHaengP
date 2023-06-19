// Fill out your copyright notice in the Description page of Project Settings.


#include "AHNPCSpawner.h"
#include "Engine/Blueprint.h"
#include "AmHaeng/Player/AHVehiclePlayerController.h"
#include "Kismet/GameplayStatics.h"

UAHNPCSpawner::UAHNPCSpawner()
{
	//Spawn 위치들 Setting하기
}

void UAHNPCSpawner::GetSpawnActorsLocation()
{
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("NPCSpawnLocation"), NPCSpawnLocationActors);
	for (AActor* NPCSpawnActor : NPCSpawnLocationActors)
	{
		SpawnLocations.Add(NPCSpawnActor->GetActorLocation());
		SpawnRotations.Add(NPCSpawnActor->GetActorRotation());
	}
}


/*void UAHNPCSpawner::GetDelegateFromWidget()
{
	if (NPCSpawnLocationActors.Num() == 0)
	{
		GetSpawnActorsLocation();
	}
	int32 NewSpawnIndex = MathFunctions->GetRandomIndex(SpawnLocations.Num());
	//UE_LOG(LogTemp, Warning, TEXT("New Spawn location is %f %f %f"), SpawnLocations[NewSpawnIndex].X, SpawnLocations[NewSpawnIndex].Y, SpawnLocations[NewSpawnIndex].Z);
	TestSpawnNPC();
}*/

void UAHNPCSpawner::TestSpawnNPC()
{
	//여기서 good npc와 bad npc를 두개를 test 용으로 spawn 합니다.
	if (GetOuter() == nullptr)
	{
		return;
	}
	FSoftObjectPath NPCBPRef(TEXT("/Script/Engine.Blueprint'/Game/VehicleNPC/AH_VehicleAI.AH_VehicleAI'"));
	if (!NPCBPRef.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("NPCBPRef Is not Valid"));
	}
	UBlueprint* NPCBPObj = Cast<UBlueprint>(NPCBPRef.TryLoad());
	check(NPCBPObj);
	UClass* NPCBPClass = NPCBPObj->GeneratedClass;
	check(NPCBPClass);

	UWorld* World = GetWorld();
	check(World);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;


	AActor* NPCVehicleSpawnActor = World->SpawnActor<AActor>(NPCBPClass, FVector(-6990.0f, 5960.0f, 0.0f),
	                                                         FRotator(0, 0, 0), SpawnParams);
	/*if (NPCVehicleSpawnActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("World Is not Valid"));
		AAHVehiclePlayerController* SpawnedNPCController = GetWorld()->SpawnActor<AAHVehiclePlayerController>();
		if (SpawnedNPCController)
		{
			UE_LOG(LogTemp, Warning, TEXT("실제 스폰하는 곳입니다"));
			SpawnedNPCController->Possess(Cast<APawn>(NPCVehicleSpawnActor));
		}
	}*/
}

void UAHNPCSpawner::NPCVehicleSpawn()
{
	if (GetOuter() == nullptr)
	{
		return;
	}
	FSoftObjectPath NPCBPRef(TEXT("/Script/Engine.Blueprint'/Game/VehicleNPC/AH_VehicleAI.AH_VehicleAI'"));
	UBlueprint* NPCBPObj = Cast<UBlueprint>(NPCBPRef.TryLoad());
	if (NPCBPObj == nullptr)
	{
		return;
	}

	UClass* NPCBPClass = NPCBPObj->GeneratedClass;
	if (NPCBPClass == nullptr)
	{
		return;
	}

	UWorld* World = GetWorld();
	if (World == nullptr)
	{
		return;
	}
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	UE_LOG(LogTemp, Log, TEXT("Spawn location %d"), SpawnLocations.Num());
	for (int32 ix = 0; ix < SpawnLocations.Num(); ++ix)
	{
		
		AActor* NPCVehicleSpawnActor = World->SpawnActor<AActor>(NPCBPClass, SpawnLocations[ix], SpawnRotations[ix], SpawnParams);
		if (NPCVehicleSpawnActor)
		{
			UE_LOG(LogTemp, Log, TEXT("Spawn 합니다."));
			AAHVehiclePlayerController* SpawnedNPCController = GetWorld()->SpawnActor<AAHVehiclePlayerController>();
			if (SpawnedNPCController)
			{
				UE_LOG(LogTemp, Log, TEXT("controller 붙입니다."));
				SpawnedNPCController->Possess(Cast<APawn>(NPCVehicleSpawnActor));
			}
		}
	}
}

void UAHNPCSpawner::RandomNPCVehicleSpawn(int32 Index)
{
	if (GetOuter() == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Outer is invalid"));
		return;
	}
	FSoftObjectPath NPCBPRef(TEXT("/Script/Engine.Blueprint'/Game/VehicleNPC/AH_VehicleAI.AH_VehicleAI'"));
	if (!NPCBPRef.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("NPCBPRef Is not Valid"));
	}
	UBlueprint* NPCBPObj = Cast<UBlueprint>(NPCBPRef.TryLoad());
	if (NPCBPObj == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("NPCBPObj Is not Valid"));
		return;
	}

	UClass* NPCBPClass = NPCBPObj->GeneratedClass;
	if (NPCBPClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("NPCBPClass Is not Valid"));
		return;
	}

	UWorld* World = GetWorld();
	if (World == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("World Is not Valid"));
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AActor* NPCVehicleSpawnActor = World->SpawnActor<AActor>(NPCBPClass, SpawnLocations[Index], SpawnRotations[Index],
	                                                         SpawnParams);
	if (NPCVehicleSpawnActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("World Is not Valid"));
		AAHVehiclePlayerController* SpawnedNPCController = GetWorld()->SpawnActor<AAHVehiclePlayerController>();
		if (SpawnedNPCController)
		{
			UE_LOG(LogTemp, Warning, TEXT("실제 스폰하는 곳입니다"));
			SpawnedNPCController->Possess(Cast<APawn>(NPCVehicleSpawnActor));
		}
	}
}


UAHNPCSpawner::~UAHNPCSpawner()
{
}
