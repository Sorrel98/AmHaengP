﻿// Fill out your copyright notice in the Description page of Project Settings.


//#include "Game/AHGameMode.h"
#include "AHGameMode.h"
#include "AmHaeng/Gimmick/AHChaseGimmickManager.h"
#include "AmHaeng/Gimmick/BeforeChase/AHSpline.h"
#include "AmHaeng/Gimmick/Chase/AHChase.h"
#include "AmHaeng/Mouse/AHMouseActor.h"
#include "AmHaeng/Player/AHVehiclePlayerController.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"
#include "AmHaeng/Widget/AHStartBtnWidget.h"
#include "AmHaeng/Widget/Gimmick/AHGimmickModeWidget.h"
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
	NPCNumber = 0; //0부터 시작
}

void AAHGameMode::PlayPause(bool IsPause)
{
	if(PlayerController)
	{
		PlayerController->SetPause(IsPause);
	}
}

void AAHGameMode::SetWorldTimer()
{
	WorldTimeOutDelegate.BindUObject(WorldWidget, &UAHWorldWidget::SetWorldTime);
	UE_LOG(LogTemp, Warning, TEXT("SetWorldTimer"));
	GetWorld()->GetTimerManager().SetTimer(WorldTimer, this, &AAHGameMode::WorldTimerTickTok, 1.0f, true);
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

void AAHGameMode::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("GameMode Start"));
	
	//Gimmick Mode Setting
	NowGimmickMode = EGimmickMode::Patrol;
	
	PlayerController = Cast<AAHVehiclePlayerController>(GetGameInstance()->GetFirstLocalPlayerController());
	
	Spawner = NewObject<UAHNPCSpawner>();
	Spawner->SetNPCNumber(NPCNumber); //동기화

	//Chase Gimmick Setting
	ChaseGimmickManager = NewObject<AAHChaseGimmickManager>(this, ChaseGimmickManagerClass);
	ChaseGimmickManager->Rename(TEXT("ChaseGimmick"), this);

	//Mouse
	MouseActorSpawn();

	//Widgets
	//Todo : 위젯만 따로 Setting 하는 클래스 만들어도 될듯 GameModeWidgetSetting
	WorldWidgetOnViewport();
	//GimmickTextOnViewport();
	IsTargetTextOnViewport();
	MinimapOnViewport();

	//Bind Delegate
	BindingDelegates();

	//Spawner Setting
	Spawner->Rename(TEXT("SpawnerOuter"), this);
	Spawner->SetSpawnActorsLocation();

	//Spawn NPC
	InitSpawnNPC();
	Spawner->TestSpawnNPC();

	//TimerSetting
	SetWorldTimer();
	
	MakeSpline();
}
/*void AAHGameMode::GimmickTextOnViewport()
{
	if (IsValid(GimmickModeWidgetClass))
    {
    	GimmickModeWidget = Cast<UAHGimmickModeWidget>(CreateWidget(GetWorld(), GimmickModeWidgetClass));
    	if (IsValid(GimmickModeWidget))
    	{
    		GimmickModeWidget->AddToViewport();
    	}
    }
}*/

void AAHGameMode::IsTargetTextOnViewport()
{
	if (IsValid(NPCIsTargetWidgetClass))
	{
		NPCIsTargetWidget = Cast<UAHNPCIsTargetWidget>(CreateWidget(GetWorld(), NPCIsTargetWidgetClass));
		if (IsValid(NPCIsTargetWidget))
		{
			NPCIsTargetWidget->AddToViewport();
			NPCIsTargetWidget->AllTextInvisible();
		}
	}
}

void AAHGameMode::MinimapOnViewport()
{
	if (IsValid(MinimapWidgetClass))
	{
		MinimapWidget = Cast<UAHMinimapWidget>(CreateWidget(GetWorld(), MinimapWidgetClass));
		if (IsValid(MinimapWidget))
		{
			MinimapWidget->AddToViewport();
		}
	}
}

void AAHGameMode::PlayChaseStartWidgetAnimation_Implementation()
{
}

void AAHGameMode::PlayCrashGlassAnimation_Implementation()
{
}

void AAHGameMode::SetHitVehicleBase(AAHNPCVehicleBase* InHitVehicleBase)
{
	UE_LOG(LogTemp, Warning, TEXT("SetHitVehicleBase"));
	HitVehicleBase = InHitVehicleBase;
}

//Delegate와 Button을 Binding
void AAHGameMode::BindingDelegates()
{
	MouseActor->ClickCPLoadingDelegate.AddUObject(this, &AAHGameMode::CPLoadingFinished);
	if(PlayerController)
	{
		//CP Timer 시작할 때 Scan 중인 Actor 정보 가져옴
		//Timer 실행될 때마다 갈아끼우게 됨
		PlayerController->SendNowClickNPCToGameMode.BindUObject(this, &AAHGameMode::SetHitVehicleBase);
	}
	if(MinimapWidget)
	{
		//spawn 할 때 widget 생성되는 delegate를 미리 바인딩
		MinimapWidget->MinimapSettingEnd();
	}

	if(Spawner)
	{
		Spawner->SendNPCNumber.BindUObject(this, &AAHGameMode::SetNPCNumber);
	}

	/*
	if(WorldWidget)
	{
		if(PlayerController->PlayerPawn)
		{
			PlayerController->PlayerPawn->ReputationChangeDelegate.AddUObject(WorldWidget, &UAHWorldWidget::SetReputation);
			UE_LOG(LogTemp, Log, TEXT("SetReputation Bind"));
		}
	}*/
}

void AAHGameMode::MouseActorSpawn()
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

	FSoftObjectPath MouseBPRef(
		TEXT("/Script/Engine.Blueprint'/Game/Player/Widget/BP_CursorLocation.BP_CursorLocation'"));
	if (!MouseBPRef.IsValid())
	{
		return;
	}
	UBlueprint* MouseBPObj = Cast<UBlueprint>(MouseBPRef.TryLoad());
	if (MouseBPObj == nullptr)
	{
		return;
	}
	UClass* MouseBPClass = MouseBPObj->GeneratedClass;
	if (MouseBPClass == nullptr)
	{
		return;
	}
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	MouseActor = World->SpawnActor<AAHMouseActor>(MouseBPClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
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
	NPCNumber = InNPCNumber;
}

void AAHGameMode::WorldWidgetOnViewport()
{
	if (WorldWidgetClass)
	{
		WorldWidget = Cast<UAHWorldWidget>(CreateWidget(GetWorld(), WorldWidgetClass));
		if (IsValid(WorldWidget))
		{
			WorldWidget->AddToViewport();
			AAHPlayerPawn::Reputation = InitReputationValue;
			WorldWidget->SetReputation(InitReputationValue);
			WorldWidget->SetWorldTime(PastSecond);
			WorldWidget->InvalidateLayoutAndVolatility();
		}
	}
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

			//ChaseMode Setting
			SetGimmickMode(EGimmickMode::Chase);
			AAHVehiclePlayerController::PlayerPawn->Brake();
			
			//play pause
			PlayPause(true);
			UE_LOG(LogTemp, Log, TEXT("Pause"));
			
			//Input 막고
			PlayerController->FlushPressedKeys();
			PlayerController->DisableInput(PlayerController);
			
			//GimmickManagerSetting
			ChaseGimmickManager->StartChaseGimmick(PlayerController, HitVehicleBase, MinimapWidget);
			ChaseGimmickManager->GetChase()->FTimeOutDelegate.AddUObject(this, &AAHGameMode::FinishChase);
		}
		else
		{
			//target이 아니었다면
			//평판 하락
			PlayerController->PlayerPawn->DecreasingReputation();
			WorldWidget->SetReputation(AAHPlayerPawn::Reputation);
			//해당 npc destroy
			HitVehicleBase->Destroy();
			//good npc respawn
			
		}
		NPCIsTargetWidget->SetNPCIsTargetWidget(HitVehicleBase->GetIsTargetNPC());
	}
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
		ChaseGimmickManager->GetChase()->EndChaseTimer();
	}
	else
	{
		PlayerController->PlayerPawn->DecreasingReputation();
	}
	WorldWidget->SetReputation(AAHPlayerPawn::Reputation);
	ChaseGimmickManager->DestroyChaseClasses();
	ChasedNPC->Destroy();
	
	//Respawn
	//todo:Bad NPC Respawn
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
		Spawner->NPCVehicleSpawn();
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
	FSoftObjectPath SplineRef(
		TEXT("/Script/Engine.Blueprint'/Game/Gimmick/ThrowMannequin/AH_BP_MannequinSpline.AH_BP_MannequinSpline'"));
	if (!SplineRef.IsValid())
	{
		return;
	}
	UBlueprint* SplineBP = Cast<UBlueprint>(SplineRef.TryLoad());
	if (SplineBP == nullptr)
	{
		return;
	}
	TSubclassOf<UObject> SplineClass = SplineBP->GeneratedClass;
	if(SplineClass)
	{
		SplineActor = World->SpawnActor<AAHSpline>(SplineClass);
	}
	
}