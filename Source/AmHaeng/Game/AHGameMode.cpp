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

void AAHGameMode::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("GameMode Start"));

	SetAllNPCNumber();
	SetBadNPCNumber();
	
	
	//Gimmick Mode Setting
	NowGimmickMode = EGimmickMode::Patrol;
	
	PlayerController = Cast<AAHVehiclePlayerController>(GetGameInstance()->GetFirstLocalPlayerController());
	
	PlayerController->SetPlayerPawn();
	PlayerController->GetPlayerPawn()->ChaseMouseDelegateBind();

	if(SpawnerClass)
	{
		Spawner = NewObject<UAHNPCSpawner>(this, SpawnerClass);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("SpawnerClass null"));
	}
	

	//Widgets
	AHHUD = Cast<AAHHUD>(PlayerController->GetHUD());
	AHHUD->HUDOnViewport(InitReputationValue, PastSecond);
	
	//Chase Gimmick Setting
	ChaseGimmickManager = NewObject<AAHChaseGimmickManager>(this, ChaseGimmickManagerClass);
	ChaseGimmickManager->Rename(TEXT("ChaseGimmick"), this);
	if(PlayerController)
	{
		ChaseGimmickManager->Initialize(PlayerController);
	}
	
	//Mouse
	MouseActorSpawn();
	//Bind Delegate
	BindingDelegates();

	//Spawner Setting
	Spawner->Rename(TEXT("SpawnerOuter"), this);
	Spawner->SetSpawnActorsLocation();

	//Spawn NPC
	InitSpawnNPC();
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
	if(MouseActor)
	{
		MouseActor->ClickCPLoadingDelegate.AddUObject(this, &AAHGameMode::CPLoadingFinished);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Mouse Actor 없음"));
	}
	
	if(PlayerController)
	{
		//CP Timer 시작할 때 Scan 중인 Actor 정보 가져옴
		//Timer 실행될 때마다 갈아끼우게 됨
		PlayerController->SendNowClickNPCToGameMode.BindUObject(this, &AAHGameMode::SetHitVehicleBase);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("PlayerController 없음"));
	}
	if(AHHUD)
	{
		if(AHHUD->GetMinimap())
		{
			//spawn 할 때 widget 생성되는 delegate를 미리 바인딩
			AHHUD->GetMinimap()->MinimapSettingEnd();
		}
	}else
	{
		UE_LOG(LogTemp, Log, TEXT("AHHUD 없음"));
	}

	if(Spawner)
	{
		Spawner->SendNPCNumber.BindUObject(this, &AAHGameMode::SetNPCNumber);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Spawner 없음"));
	}
}

void AAHGameMode::MouseActorSpawn()
{
	UWorld* World = GetWorld();
	if(World)
	{
		if(MouseActorClass)
		{
			MouseActor = World->SpawnActor<AAHMouseActor>(MouseActorClass, FVector::ZeroVector, FRotator::ZeroRotator);
			if(MouseActor)
			{
				UE_LOG(LogTemp, Log, TEXT("mouse Actor 스폰완료"));
			}
		}
	}
}

UAHNPCSpawner* AAHGameMode::GetSpawner()
{
	if(Spawner)
	{
		return Spawner;
	}
	return nullptr;
}

void AAHGameMode::SetNPCNumber(int32 InNPCNumber)
{
	SpawnedNPCNumber = InNPCNumber;
}

void AAHGameMode::CPLoadingFinished()
{
	UE_LOG(LogTemp, Log, TEXT("CP Loading Finished"));

	
	//CP가 끝났을 때
	if(HitVehicleBase==nullptr)
	{
		return;
	}
	if(NowGimmickMode ==EGimmickMode::Patrol)
	{
		//Chase
		if(HitVehicleBase->GetIsTargetNPC())
		{
			//ChasedNPC Setting
			ChasedNPC = HitVehicleBase;
			ChasedNPC->SetIsChased(true);
			ChasedNPC->AHDestroyFrontSphere();
			ChasedNPC->NPCArrestedDelegate.AddUObject(this, &AAHGameMode::FinishChase);

			//Input 막고
			PlayerController->FlushPressedKeys();
			PlayerController->DisableInput(PlayerController);
			
			//ChaseMode Setting
			SetGimmickMode(EGimmickMode::Chase);
			AAHVehiclePlayerController::PlayerPawn->Brake();
			UE_LOG(LogTemp, Log, TEXT("Player Pawn Speed : "));
			//타이머 돌려서 플레이어가 멈추면 SetPause
			IsPlayerSpeedZero();
		}
		else
		{
			InCorrectSound();
			//target이 아니었다면
			//평판 하락
			PlayerController->PlayerPawn->DecreasingReputation();
			if(AHHUD->GetWorldWidget())
			{
				AHHUD->GetWorldWidget()->SetReputation(AAHPlayerPawn::Reputation);
			}
			//해당 npc destroy
			HitVehicleBase->Destroy();
			//good npc respawn
			Spawner->DecreaseGoodNPC();
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
	ChasedNPC->Destroy();
	
	//Respawn
	Spawner->DecreaseBadNPC();
}

void AAHGameMode::IsPlayerSpeedZero()
{
	PlayerController->GetPlayerPawn()->SetNowSpeedFromBP();
	if(PlayerController->GetPlayerPawn()->GetNowSpeed() < 5)
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

void AAHGameMode::InitSpawnNPC()
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