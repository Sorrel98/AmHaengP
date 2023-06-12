// Fill out your copyright notice in the Description page of Project Settings.


#include "AHNPCSpawner.h"
#include "Engine/Blueprint.h"
#include "AmHaeng/Player/AHVehiclePlayerController.h"
#include "Kismet/GameplayStatics.h"

UAHNPCSpawner::UAHNPCSpawner()
{
	//SetSpawningRandomLocations();
}


void UAHNPCSpawner::SetSpawningRandomLocations()
{
	SpawnLocations.Emplace(FVector(11650.0f, 3560.0f, 0.0f));
	SpawnLocations.Emplace(FVector(-9030.0f, -770.0f, 0.0f));
	SpawnLocations.Emplace(FVector(2293.372449f, 10120.637944f, 0.0f));
	SpawnLocations.Emplace(FVector(421.089786f, -1400.890789f, 0.0f));
	SpawnLocations.Emplace(FVector(-6150.0f, 5310.0f, 0.0f));
	SpawnLocations.Emplace(FVector(4030.0f, 5600.0f, 0.0f));

	SpawnRotations.Emplace(FRotator(0.0f, 90.0f, 0.0f));
	SpawnRotations.Emplace(FRotator(0.0f, 90.0f, 0.0f));
	SpawnRotations.Emplace(FRotator(0.0f, 90.0f, 0.0f));
	SpawnRotations.Emplace(FRotator(0.0f, 0.0f, 0.0f));
	SpawnRotations.Emplace(FRotator(0.0f, -30.0f, 0.0f));
	SpawnRotations.Emplace(FRotator(0.0f, 0.0f, 0.0f));
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


void UAHNPCSpawner::GetDelegateFromWidget()
{
	if (NPCSpawnLocationActors.Num() == 0)
	{
		GetSpawnActorsLocation();
	}
	int32 NewSpawnIndex = MathFunctions->GetRandomIndex(SpawnLocations.Num());
	UE_LOG(LogTemp, Warning, TEXT("New Spawn location is %f %f %f"), SpawnLocations[NewSpawnIndex].X,
	       SpawnLocations[NewSpawnIndex].Y, SpawnLocations[NewSpawnIndex].Z);
	TestSpawnNPC();
	//RandomNPCVehicleSpawn(NewSpawnIndex);
}

void UAHNPCSpawner::TestSpawnNPC()
{
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


	AActor* NPCVehicleSpawnActor = World->SpawnActor<AActor>(NPCBPClass, FVector(-6990.0f, 5960.0f, 0.0f),
	                                                         FRotator(0, 0, 0), SpawnParams);
	if (NPCVehicleSpawnActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("World Is not Valid"));
		AAHVehiclePlayerController* SpawnedNPCController = GetWorld()->SpawnActor<AAHVehiclePlayerController>();
		/*if (SpawnedNPCController)
		{
			UE_LOG(LogTemp, Warning, TEXT("실제 스폰하는 곳입니다"));
			SpawnedNPCController->Possess(Cast<APawn>(NPCVehicleSpawnActor));
		}*/
	}
}

//현재 사용하지 않음
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

	for (int32 ix = 0; ix < SpawnLocations.Num(); ++ix)
	{
		AActor* NPCVehicleSpawnActor = World->SpawnActor<AActor>(NPCBPClass, SpawnLocations[ix], SpawnRotations[ix],
		                                                         SpawnParams);
		if (NPCVehicleSpawnActor)
		{
			AAHVehiclePlayerController* SpawnedNPCController = GetWorld()->SpawnActor<AAHVehiclePlayerController>();
			if (SpawnedNPCController)
			{
				SpawnedNPCController->Possess(Cast<APawn>(NPCVehicleSpawnActor));
			}
		}
	}
}

void UAHNPCSpawner::RandomNPCVehicleSpawn(int32 Index)
{
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
