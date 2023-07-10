// Fill out your copyright notice in the Description page of Project Settings.


#include "AHNPCSpawner.h"
#include "Engine/Blueprint.h"
#include "AmHaeng/Player/AHVehiclePlayerController.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"
#include "Kismet/GameplayStatics.h"

UAHNPCSpawner::UAHNPCSpawner()
{
	//Spawn 위치들 Setting하기
}

void UAHNPCSpawner::SetSpawnActorsLocation()
{
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("NPCSpawnLocation"), NPCSpawnLocationActors);
	for (AActor* NPCSpawnActor : NPCSpawnLocationActors)
	{
		SpawnLocations.Add(NPCSpawnActor->GetActorLocation());
		SpawnRotations.Add(NPCSpawnActor->GetActorRotation());
	}

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("NPCRunAwayLocation"), NPCTeleportLocationActors);
}

AActor* UAHNPCSpawner::GetTeleportLocationActor(int32 Index)
{
	if(NPCTeleportLocationActors.Num() > Index && Index >= 0)
	{
		return NPCTeleportLocationActors[Index];
	}
	return nullptr;
}

void UAHNPCSpawner::SetNPCNumber(int32 InNPCNumber)
{
	UE_LOG(LogTemp, Log,TEXT("[Spawner] Set NPC Number : %d"), InNPCNumber);
	NPCNumber = InNPCNumber;
}

void UAHNPCSpawner::TestSpawnNPC()
{
	//여기서 good npc와 bad npc를 두개를 test 용으로 spawn 합니다.
	if (GetOuter() == nullptr)
	{
		return;
	}
	FSoftObjectPath NPCBPRef(TEXT("/Script/Engine.Blueprint'/Game/VehicleNPC/AH_VehicleAITEST.AH_VehicleAITEST'"));
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

	FVector GoodNPCLocation;
	FRotator GoodNPCRotator;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("GoodNPC"), GoodNPCSpawnLocationActors);
	for (AActor* NPCSpawnActor : GoodNPCSpawnLocationActors)
	{
		GoodNPCLocation = NPCSpawnActor->GetActorLocation();
		GoodNPCRotator = NPCSpawnActor->GetActorRotation();
	}
	AActor* TestGoodNPC = World->SpawnActor<AActor>(NPCBPClass, GoodNPCLocation, GoodNPCRotator, SpawnParams);
	AAHNPCVehicleBase* TestGoodAHNPC = Cast<AAHNPCVehicleBase>(TestGoodNPC);
	TestGoodAHNPC->TESTGoodNPCInfoSetting();
	

	FVector BadNPCLocation;
	FRotator BadNPCRotator;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("BadNPC"), BadNPCSpawnLocationActors);
	for (AActor* NPCSpawnActor : BadNPCSpawnLocationActors)
	{
		BadNPCLocation = NPCSpawnActor->GetActorLocation();
		BadNPCRotator = NPCSpawnActor->GetActorRotation();
	}
	AActor* TestBadNPC = World->SpawnActor<AActor>(NPCBPClass, BadNPCLocation, BadNPCRotator, SpawnParams);
	AAHNPCVehicleBase* TestBadAHNPC = Cast<AAHNPCVehicleBase>(TestBadNPC);
	TestBadAHNPC->TESTBadNPCInfoSetting();
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

	for (int32 ix = 0; ix < SpawnLocations.Num(); ++ix)
	{
		AActor* NPCVehicleSpawnActor = World->SpawnActor<AActor>(NPCBPClass, SpawnLocations[ix], SpawnRotations[ix], SpawnParams);
		if(NPCVehicleSpawnActor==nullptr) return;
		OnNPCSpawnEnd.Execute(Cast<AAHNPCVehicleBase>(NPCVehicleSpawnActor));
		
		AAHVehiclePlayerController* SpawnedNPCController = GetWorld()->SpawnActor<AAHVehiclePlayerController>();
		if (SpawnedNPCController)
		{
			SpawnedNPCController->Possess(Cast<APawn>(NPCVehicleSpawnActor));
		}
		
		AAHNPCVehicleBase* NPCActor = Cast<AAHNPCVehicleBase>(NPCVehicleSpawnActor);
		if(NPCActor->GetIsTargetNPC())
		{
			UE_LOG(LogTemp, Log, TEXT("%s NPC is target"), *NPCActor->GetName());
			NPCActor->SetBadInfoWidgetData(NPCNumber);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("%s NPC is Not target"), *NPCActor->GetName());
			NPCActor->SetGoodInfoWidgetData(NPCNumber);
		}

		++NPCNumber;
		SendNPCNumber.Execute(NPCNumber);
	}
}

//사용 안 하는 중
void UAHNPCSpawner::SpecificLocationNPCVehicleSpawn(int32 Index)
{
	UE_LOG(LogTemp, Log, TEXT("Start Spawn"));
	if (GetOuter() == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Outer is invalid"));
		return;
	}
	FSoftObjectPath NPCBPRef(TEXT("/Script/Engine.Blueprint'/Game/VehicleNPC/AH_VehicleAI.AH_VehicleAI'"));
	if (!NPCBPRef.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("NPCBPRef Is not Valid"));
		return;
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

	AActor* NPCVehicleSpawnActor = World->SpawnActor<AActor>(NPCBPClass, SpawnLocations[Index], SpawnRotations[Index], SpawnParams);
	if(NPCVehicleSpawnActor == nullptr) return;
	
	AAHVehiclePlayerController* SpawnedNPCController = GetWorld()->SpawnActor<AAHVehiclePlayerController>();
	if (SpawnedNPCController)
	{
		SpawnedNPCController->Possess(Cast<APawn>(NPCVehicleSpawnActor));
	}
}

void UAHNPCSpawner::SpecificLocationNPCVehicleSpawn(AActor* LocationActor)
{
	UE_LOG(LogTemp, Log, TEXT("Start Spawn"));
	if (GetOuter() == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Outer is invalid"));
		return;
	}
	FSoftObjectPath NPCBPRef(TEXT("/Script/Engine.Blueprint'/Game/VehicleNPC/AH_VehicleAI.AH_VehicleAI'"));
	if (!NPCBPRef.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("NPCBPRef Is not Valid"));
		return;
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

	AActor* NPCVehicleSpawnActor = World->SpawnActor<AActor>(NPCBPClass, LocationActor->GetActorLocation(), LocationActor->GetActorRotation(), SpawnParams);
	if(NPCVehicleSpawnActor == nullptr) return;
	
	AAHVehiclePlayerController* SpawnedNPCController = GetWorld()->SpawnActor<AAHVehiclePlayerController>();
	if (SpawnedNPCController)
	{
		SpawnedNPCController->Possess(Cast<APawn>(NPCVehicleSpawnActor));
	}
}

/*void UAHNPCSpawner::SpecificLocationNPCVehicleSpawn(FVector Location, FRotator Rotation)
{
	UE_LOG(LogTemp, Log, TEXT("Start Spawn"));
	if (GetOuter() == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Outer is invalid"));
		return;
	}
	FSoftObjectPath NPCBPRef(TEXT("/Script/Engine.Blueprint'/Game/VehicleNPC/AH_VehicleAI.AH_VehicleAI'"));
	if (!NPCBPRef.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("NPCBPRef Is not Valid"));
		return;
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

	AActor* NPCVehicleSpawnActor = World->SpawnActor<AActor>(NPCBPClass, Location, Rotation, SpawnParams);
	if(NPCVehicleSpawnActor == nullptr) return;
	
	AAHVehiclePlayerController* SpawnedNPCController = GetWorld()->SpawnActor<AAHVehiclePlayerController>();
	if (SpawnedNPCController)
	{
		SpawnedNPCController->Possess(Cast<APawn>(NPCVehicleSpawnActor));
	}
}*/


UAHNPCSpawner::~UAHNPCSpawner()
{
}
