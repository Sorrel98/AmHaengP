// Fill out your copyright notice in the Description page of Project Settings.


//#include "Game/AHGameMode.h"
#include "AHGameMode.h"
#include "AmHaeng/Gimmick/AHChaseGimmickManager.h"
#include "AmHaeng/Gimmick/BeforeChase/AHSpline.h"
#include "AmHaeng/Gimmick/Chase/AHChase.h"
#include "AmHaeng/HUD/AHHUD.h"
#include "AmHaeng/Mouse/AHMouseActor.h"
#include "AmHaeng/Player/AHVehiclePlayerController.h"
#include "AmHaeng/Spawner/AHNPCSpawner.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"
#include "AmHaeng/Widget/Gimmick/AHNPCIsTargetWidget.h"
#include "AmHaeng/Widget/Minimap/AHMinimapWidget.h"
#include "AmHaeng/Widget/World/AHWorldWidget.h"
#include "Kismet/GameplayStatics.h"

EGimmickMode AAHGameMode::NowGimmickMode = EGimmickMode::Patrol;
AAHVehiclePlayerController* AAHGameMode::PlayerController = nullptr;
AAHSpline* AAHGameMode::SplineActor = nullptr;
AAHGameMode::AAHGameMode()
{
	bIsNPCSpawning = false;
	SpawnedNPCNumber = 0; //0부터 시작
}

void AAHGameMode::SetWorldTimer()
{
	if(AHHUD->GetWorldWidget())
	{
		WorldTimeOutDelegate.BindUObject(AHHUD->GetWorldWidget(), &UAHWorldWidget::SetWorldTime);
		UE_LOG(LogTemp, Warning, TEXT("SetWorldTimer"));
		GetWorld()->GetTimerManager().SetTimer(WorldTimer, this, &AAHGameMode::WorldTimerTickTok, 1.0f, true);
	}
}

void AAHGameMode::WorldTimerTickTok()
{
	PastSecond-=1;
	UE_LOG(LogTemp, Log, TEXT("TickTok : %d"), PastSecond);
	//Delegate World Widget에게 알림
	WorldTimeOutDelegate.Execute(PastSecond);
	
	if(PastSecond<=0)
	{
		GetWorld()->GetTimerManager().ClearTimer(WorldTimer);
		OpenLobbyLevel();
	}
}

void AAHGameMode::OpenLobbyLevel()
{
	//OpenLobby
	UGameplayStatics::OpenLevel(this, *LobbyLevelName);
}

void AAHGameMode::CorrectSound_Implementation()
{
}

void AAHGameMode::InCorrectSound_Implementation()
{
}

void AAHGameMode::SetNPCNumber()
{
	SetAllNPCNumber();
	SetBadNPCNumber();
}

void AAHGameMode::InitPlayerController()
{
	PlayerController = Cast<AAHVehiclePlayerController>(GetGameInstance()->GetFirstLocalPlayerController());
	
	PlayerController->SetPlayerPawn();
	PlayerController->GetPlayerPawn()->ChaseMouseDelegateBind();
}

void AAHGameMode::InitChaseGimmickManager()
{
	ChaseGimmickManager = NewObject<AAHChaseGimmickManager>(this, ChaseGimmickManagerClass);
	ChaseGimmickManager->Rename(TEXT("ChaseGimmick"), this);
	if(PlayerController)
	{
		ChaseGimmickManager->Initialize(PlayerController);
	}
}

void AAHGameMode::InitAHHUD()
{
	AHHUD = Cast<AAHHUD>(PlayerController->GetHUD());
	AHHUD->HUDOnViewport(InitReputationValue, PastSecond);
}

void AAHGameMode::CreateSpawner()
{
	if(SpawnerClass)
	{
		Spawner = NewObject<UAHNPCSpawner>(this, SpawnerClass);
		//Spawner Setting
		Spawner->Rename(TEXT("SpawnerOuter"), this);
	}
}

void AAHGameMode::BeginPlay()
{
	Super::BeginPlay();

	SetNPCNumber();
	
	//Gimmick Mode Setting
	SetGimmickMode(EGimmickMode::Patrol);
	
	InitPlayerController();
	
	CreateSpawner();
	
	//Widgets
	InitAHHUD();
	
	//Chase Gimmick Setting
	InitChaseGimmickManager();
	
	//Mouse
	MouseActorSpawn();
	
	//Bind Delegate
	BindingDelegates();
	
	Spawner->SetSpawnActorsLocation();
	
	//Spawn NPC
	InitSpawnNPCs();
	
	//TimerSetting
	SetWorldTimer();
	
	MakeSpline();
}

void AAHGameMode::SetHitVehicleBase(AAHNPCVehicleBase* InHitVehicleBase)
{
	HitVehicleBase = InHitVehicleBase;
}

//Delegate와 Button을 Binding
void AAHGameMode::BindingDelegates()
{
	if(MouseActor) MouseActor->ClickCPLoadingDelegate.AddUObject(this, &AAHGameMode::CPLoadingFinished);
	if(PlayerController) PlayerController->SendNowClickNPCToGameMode.BindUObject(this, &AAHGameMode::SetHitVehicleBase);
	//if(AHHUD && AHHUD->GetMinimap()) AHHUD->GetMinimap()->MinimapSettingEnd();
	if(Spawner)
	{
		Spawner->SendNPCNumber.BindUObject(this, &AAHGameMode::SetNPCNumber);
		Spawner->OnNPCSpawnEnd.BindUObject(AHHUD->GetMinimap(), &UAHMinimapWidget::CallAddNPCIcon);
	}
}

void AAHGameMode::MouseActorSpawn()
{
	UWorld* World = GetWorld();
	if(World && MouseActorClass)
	{
		MouseActor = World->SpawnActor<AAHMouseActor>(MouseActorClass, FVector::ZeroVector, FRotator::ZeroRotator);
	}
}

UAHNPCSpawner* AAHGameMode::GetSpawner()
{
	return Spawner;
}

void AAHGameMode::SetNPCNumber(int32 InNPCNumber)
{
	SpawnedNPCNumber = InNPCNumber;
}

void AAHGameMode::SettingChasedNPC()
{
	ChasedNPC = HitVehicleBase;
	ChasedNPC->SetIsChased(true);
	ChasedNPC->AHDestroyFrontSphere();
	ChasedNPC->NPCArrestedDelegate.AddUObject(this, &AAHGameMode::FinishChase);
}

void AAHGameMode::PlayerInputEnabled()
{
	PlayerController->FlushPressedKeys();
	PlayerController->DisableInput(PlayerController);
}

void AAHGameMode::DecreaseReputation()
{
	PlayerController->PlayerPawn->DecreasingReputation();
	if(AHHUD->GetWorldWidget())
	{
		AHHUD->GetWorldWidget()->SetReputation(AAHPlayerPawn::Reputation);
	}
}

void AAHGameMode::ChaseStartPlayerSetting()
{
	//Input 막고
	PlayerInputEnabled();
	AAHVehiclePlayerController::PlayerPawn->Brake();
	//타이머 돌려서 플레이어가 멈추면 SetPause
	IsPlayerSpeedZero();
}

void AAHGameMode::RemoveGoodNPC()
{
	//해당 npc destroy
	HitVehicleBase->Destroy();
	//good npc respawn
	Spawner->DecreaseGoodNPC();
}

void AAHGameMode::CPLoadingFinished()
{
	//CP가 끝났을 때
	if(HitVehicleBase == nullptr) return;
	if(NowGimmickMode ==EGimmickMode::Patrol)
	{
		//Chase
		if(HitVehicleBase->GetIsTargetNPC())
		{
			//ChaseMode Setting
			SetGimmickMode(EGimmickMode::Chase);
			//ChasedNPC Setting
			SettingChasedNPC();
			ChaseStartPlayerSetting();
		}
		else
		{
			//target이 아니었다면
			InCorrectSound();
			//평판 하락
			DecreaseReputation();
			RemoveGoodNPC();
		}
		if(AHHUD->GetIsTargetWidget())
		{
			AHHUD->GetIsTargetWidget()->SetNPCIsTargetWidget(HitVehicleBase->GetIsTargetNPC());
		}
	}
}

void AAHGameMode::SetAllNPCNumber()
{
	TArray<AActor*> NPCSpawnLocationActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("NPCSpawnLocation"), NPCSpawnLocationActors);
	InitAllNPCNumber = NPCSpawnLocationActors.Num();
}

void AAHGameMode::SetBadNPCNumber()
{
	BadNPCNumber = InitAllNPCNumber/3;
}

void AAHGameMode::SetGimmickMode(EGimmickMode InGimmickMode)
{
	NowGimmickMode = InGimmickMode;
	GimmickChangeDelegate.Broadcast(InGimmickMode); //Widget Text 바꾸는 기능 밖에 없음 아직
}

const EGimmickMode AAHGameMode::GetGimmickMode()
{
	return NowGimmickMode;
}

void AAHGameMode::RemoveBadNPC()
{
	ChasedNPC->Destroy();
	//Respawn
	Spawner->DecreaseBadNPC();
}

void AAHGameMode::FinishChase(bool IsChaseSuccess)
{
	UE_LOG(LogTemp, Log, TEXT("Chase 결과 : %d"), IsChaseSuccess);
	if(IsChaseSuccess)
	{
		CorrectSound();
	}
	//Chase Mode 변경
	SetGimmickMode(EGimmickMode::Patrol);
	//IMC 변경
	PlayerController->SetPatrolIMC();
	PlayerController->PlayerPawn->SetChickenVisible(false);
	if(IsChaseSuccess)
	{
		//평판 update
		PlayerController->PlayerPawn->RaisingReputation();
		//chase 제한 시간 timer clear
		//ChaseGimmickManager->GetChase()->EndChaseTimer();
	}
	else
	{
		PlayerController->PlayerPawn->DecreasingReputation();
	}
	if(AHHUD->GetWorldWidget())
	{
		AHHUD->GetWorldWidget()->SetReputation(AAHPlayerPawn::Reputation);
	}
	RemoveBadNPC();
}

void AAHGameMode::IsPlayerSpeedZero()
{
	PlayerController->GetPlayerPawn()->SetNowSpeedFromBP();
	if(PlayerController->GetPlayerPawn()->GetNowSpeed() < 1)
	{
		//play pause
		PlayerController->SetPause(true);
		UE_LOG(LogTemp, Log, TEXT("Pause"));
			
		//GimmickManagerSetting
		ChaseGimmickManager->StartChaseGimmick(HitVehicleBase);
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(PlayerSpeedZeroTimer, FTimerDelegate::CreateUObject(this, &AAHGameMode::IsPlayerSpeedZero), 0.1f, false);
	}
}


//Delegate 오면 실행될 함수 (spawning 되고 있는지 mode가 알기 위하여 state 변경)
void AAHGameMode::SetNPCSpawningState(uint8 NowState)
{
	bIsNPCSpawning = !NowState;
}

void AAHGameMode::InitSpawnNPCs()
{
	if(Spawner!=nullptr)
	{
		Spawner->InitNPCSpawn(BadNPCNumber);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Spawner is invalid"));
	}
}

void AAHGameMode::MakeSpline()
{
	if (GetOuter() == nullptr)
	{
		return;
	}
	UWorld* World = GetWorld();
	if (World == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("World Is not Valid"));
		return;
	}
	
	if(SplineClass)
	{
		SplineActor = World->SpawnActor<AAHSpline>(SplineClass);
	}
	
}