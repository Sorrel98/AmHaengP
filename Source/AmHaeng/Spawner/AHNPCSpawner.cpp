// Fill out your copyright notice in the Description page of Project Settings.


#include "AHNPCSpawner.h"
#include "Engine/Blueprint.h"
#include "AmHaeng/Player/AHVehiclePlayerController.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
//#include "Algo/Sort.h"
#include "Kismet/KismetMathLibrary.h"


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

AActor* UAHNPCSpawner::GetSpawnLocationActor(int32 Index)
{
	if(NPCSpawnLocationActors.Num() > Index && Index >= 0)
	{
		return NPCSpawnLocationActors[Index];
	}
	return nullptr;
}

AActor* UAHNPCSpawner::GetTeleportLocationActor(int32 Index)
{
	if(NPCTeleportLocationActors.Num() > Index && Index >= 0)
	{
		return NPCTeleportLocationActors[Index];
	}
	return nullptr;
}

void UAHNPCSpawner::DecreaseGoodNPC()
{
	UE_LOG(LogTemp, Log, TEXT("DecreaseGoodNPC"));
	NowGoodNPCNumber-=1;
	CheckNPCNumber(false);
}

void UAHNPCSpawner::IncreaseGoodNPC()
{
	UE_LOG(LogTemp, Log, TEXT("IncreaseGoodNPC"));
	NowGoodNPCNumber+=1;
}

void UAHNPCSpawner::DecreaseBadNPC()
{
	UE_LOG(LogTemp, Warning, TEXT("DecreaseBadNPC"));
	NowBadNPCNumber-=1;
	CheckNPCNumber(true);
}

void UAHNPCSpawner::IncreaseBadNPC()
{
	UE_LOG(LogTemp, Warning, TEXT("IncreaseBadNPC"));
	NowBadNPCNumber+=1;
}

void UAHNPCSpawner::CheckNPCNumber(bool IsTarget)
{
	if(NowBadNPCNumber < MaxBadNPCNumber || NowGoodNPCNumber < MaxGoodNPCNumber)
	{
		// spawn 시도
		SpawnNewNPC(IsTarget);
		//3초 뒤에 다시 check
		GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, FTimerDelegate::CreateUObject(this, &UAHNPCSpawner::CheckNPCNumber, IsTarget), 1.f, false);
	}
}

/*void UAHNPCSpawner::TestSpawnNPC()
{
	UWorld* World = GetWorld();
	check(World);

	FVector GoodNPCLocation;
	FRotator GoodNPCRotator;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("GoodNPC"), GoodNPCSpawnLocationActors);
	for (AActor* NPCSpawnActor : GoodNPCSpawnLocationActors)
	{
		GoodNPCLocation = NPCSpawnActor->GetActorLocation();
		GoodNPCRotator = NPCSpawnActor->GetActorRotation();
	}
	AActor* TestGoodNPC = World->SpawnActor<AActor>(MakeNPCBPClass(), GoodNPCLocation, GoodNPCRotator, SpawnParams);
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
	AActor* TestBadNPC = World->SpawnActor<AActor>(MakeNPCBPClass(), BadNPCLocation, BadNPCRotator, SpawnParams);
	AAHNPCVehicleBase* TestBadAHNPC = Cast<AAHNPCVehicleBase>(TestBadNPC);
	TestBadAHNPC->TESTBadNPCInfoSetting();
}*/

void UAHNPCSpawner::ShuffleArray(TArray<int32>& Array)
{
	const int32 LastIndex = Array.Num() - 1;
 
	for (int32 i = 0; i <= LastIndex; i += 1) {
		const int32 Index = UKismetMathLibrary::RandomIntegerInRange(i, LastIndex);
		if (i == Index) {
			continue;
		}
		Array.Swap(i, Index);
	}
}

/*UClass* UAHNPCSpawner::MakeNPCBPClass()
{
	//UE_LOG(LogTemp, Log, TEXT("Start Spawn"));
	if (GetOuter() == nullptr) return nullptr;
	
	FSoftObjectPath NPCBPRef(TEXT("/Script/Engine.Blueprint'/Game/VehicleNPC/AH_VehicleAI.AH_VehicleAI'"));
	if (!NPCBPRef.IsValid()) return nullptr;
	
	UBlueprint* NPCBPObj = Cast<UBlueprint>(NPCBPRef.TryLoad());
	if (NPCBPObj == nullptr) return nullptr;
	
	UClass* NPCBPClass = NPCBPObj->GeneratedClass;
	if (NPCBPClass == nullptr) return nullptr;
	
	return NPCBPClass;
}*/

void UAHNPCSpawner::SetTargetNPCIndex(int32 BadNPCNumber)
{
	TargetNPCIndex.SetNum(BadNPCNumber);
	RandomIndex.SetNum(SpawnLocations.Num());
	//여기서 어떤 인덱스의 NPC가 Bad일지 Good일지 선택합니다.
	for(int32 i = 0; i<SpawnLocations.Num(); ++i)
	{
		RandomIndex[i] = i;
	}
	ShuffleArray(RandomIndex);
	for(int32 i = 0; i<BadNPCNumber; ++i)
	{
		TargetNPCIndex[i] = RandomIndex[i];
	}
}

bool UAHNPCSpawner::IsTargetNPCIndex(uint32 NPCIndex)
{
	for(int i = 0; i<TargetNPCIndex.Num(); ++i)
	{
		if(TargetNPCIndex[i]==NPCIndex) return true;
	}
	return false;
}

//최초 Spawn location에 npc Spawn
void UAHNPCSpawner::InitNPCSpawn(uint32 BadNPCNumber)
{
	MaxBadNPCNumber = BadNPCNumber;
	SetTargetNPCIndex(BadNPCNumber);
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	UWorld* World = GetWorld();
	if (World == nullptr) return;
	
	for (int32 ix = 0; ix < SpawnLocations.Num(); ++ix)
	{
		AAHNPCVehicleBase* NPCVehicleSpawnActor = nullptr;
		if(NPCClass)
		{
			NPCVehicleSpawnActor = World->SpawnActor<AAHNPCVehicleBase>(NPCClass, SpawnLocations[ix], SpawnRotations[ix], SpawnParams);
		}
		
		if(NPCVehicleSpawnActor == nullptr) return;
		//Minimap Icon
		OnNPCSpawnEnd.Execute(NPCVehicleSpawnActor);
		
		PossessController(NPCVehicleSpawnActor);
		//여기서 해당 NPC가 Bad일지 Good일지 저장됩니다.
		const bool bIsNPCTarget = IsTargetNPCIndex(ix);
		NPCVehicleSpawnActor->SetIsTargetNPC(bIsNPCTarget);
		bIsNPCTarget ? NPCVehicleSpawnActor->OnNPCRemoved.AddDynamic(this,&UAHNPCSpawner::DecreaseBadNPC)
			: NPCVehicleSpawnActor->OnNPCRemoved.AddDynamic(this,&UAHNPCSpawner::DecreaseGoodNPC);
		NPCVehicleSpawnActor->SetNPCStatAndInfoWidget(NPCNumber);

		++NPCNumber;
		SendNPCNumber.Execute(NPCNumber);
	}
	
	MaxGoodNPCNumber = NPCNumber - BadNPCNumber;
	NowBadNPCNumber = MaxBadNPCNumber;
	NowGoodNPCNumber = MaxGoodNPCNumber;
}

void UAHNPCSpawner::PossessController(AActor* NPCVehicleSpawnActor)
{
	AAHVehiclePlayerController* SpawnedNPCController = GetWorld()->SpawnActor<AAHVehiclePlayerController>();
	if (SpawnedNPCController)
	{
		SpawnedNPCController->Possess(Cast<APawn>(NPCVehicleSpawnActor));
	}
}

void UAHNPCSpawner::SpecificLocationNPCVehicleSpawn(int32 Index, bool IsTarget)
{
	UWorld* World = GetWorld();
	if (World == nullptr) return;

	AActor* NPCVehicleSpawnActor = World->SpawnActor<AActor>(NPCClass, SpawnLocations[Index], SpawnRotations[Index], SpawnParams);
	if(NPCVehicleSpawnActor == nullptr) return;
	PostSpawnNPC(IsTarget, NPCVehicleSpawnActor);
	SetNPCNumber(IsTarget);
}

void UAHNPCSpawner::SetNPCNumber(bool IsTarget)
{
	++NPCNumber;
	SendNPCNumber.Execute(NPCNumber);
	IsTarget? ++NowBadNPCNumber : ++NowGoodNPCNumber;
}

void UAHNPCSpawner::SpecificLocationNPCVehicleSpawn(AActor* LocationActor, bool IsTarget)
{
	UWorld* World = GetWorld();
	if (World == nullptr) return;

	AActor* NPCVehicleSpawnActor = World->SpawnActor<AActor>(NPCClass, LocationActor->GetActorLocation(), LocationActor->GetActorRotation(), SpawnParams);
	if(NPCVehicleSpawnActor == nullptr) return;
	PostSpawnNPC(IsTarget, NPCVehicleSpawnActor);
	SetNPCNumber(IsTarget);
}

void UAHNPCSpawner::PostSpawnNPC(bool IsTarget, AActor* NPCVehicleSpawnActor)
{
	AAHNPCVehicleBase* NPCActor = Cast<AAHNPCVehicleBase>(NPCVehicleSpawnActor);
	if(NPCActor)
	{
		OnNPCSpawnEnd.Execute(NPCActor);
		PossessController(NPCVehicleSpawnActor);
		NPCActor->SetIsTargetNPC(IsTarget);
		IsTarget ? NPCActor->OnNPCRemoved.AddDynamic(this,&UAHNPCSpawner::DecreaseBadNPC)
			: NPCActor->OnNPCRemoved.AddDynamic(this,&UAHNPCSpawner::DecreaseGoodNPC);
		NPCActor->SetNPCStatAndInfoWidget(NPCNumber);
	}
}

void UAHNPCSpawner::SpecificLocationNPCVehicleSpawn(FVector Location, FRotator Rotation, bool IsTarget)
{
	UWorld* World = GetWorld();
	if (World == nullptr) return;
	
	AActor* NPCVehicleSpawnActor = World->SpawnActor<AActor>(NPCClass, Location, Rotation, SpawnParams);
	PostSpawnNPC(IsTarget, NPCVehicleSpawnActor);
	SetNPCNumber(IsTarget);
}

int32 UAHNPCSpawner::RandomSpawnIndex()
{
	int32 TempIndex = FMath::RandRange(0, GetSpawnLocationNumber()-1);
	return TempIndex;
}

void UAHNPCSpawner::SpawnNewNPC(bool IsTarget)
{
	//Spawn될 지역 Index
	int32 SpawnLocationIndex = RandomSpawnIndex();
	if(!IsHitActorOnSpawnActor(SpawnLocationIndex))
	{
		UE_LOG(LogTemp, Log, TEXT("Spawn 가능한 위치입니다"));
		SpecificLocationNPCVehicleSpawn(GetSpawnLocationActor(SpawnLocationIndex), IsTarget);
	}
}

//해당 index teleport 위치에 무엇인가 올려져 있는지 판별
bool UAHNPCSpawner::IsHitActorOnSpawnActor(int32 InSpawnIndex)
{
	AActor* SpawnActor = this->GetSpawnLocationActor(InSpawnIndex);
	TArray<UActorComponent*> Components = SpawnActor->GetComponentsByTag(UActorComponent::StaticClass(), FName(TEXT("NPCCollision")));
	
	UBoxComponent* SpawnActorCollision = nullptr;
	bool bResult = false;
	if(!Components.IsEmpty())
	{
		SpawnActorCollision = Cast<UBoxComponent>(Components[0]);
		if(GetWorld() && SpawnActorCollision)
		{
			FHitResult OutHitResult;
			FVector Start = SpawnActorCollision->GetComponentLocation();
			FCollisionShape Box = FCollisionShape::MakeBox(SpawnActorCollision->GetScaledBoxExtent()/2);
			FVector End = Start;
			bResult = GetWorld()->SweepSingleByProfile(OutHitResult, Start, End, SpawnActorCollision->GetComponentRotation().Quaternion(), FName(TEXT("NPCBody")), Box);
			//DrawDebugBox(GetWorld(), Start, SpawnActorCollision->GetScaledBoxExtent(), bResult ? FColor::Red : FColor::Yellow, false, 1.f);
			//무엇인가 있었다면 true
		}
	}
	//없었다면 false
	return bResult;
}