// Fill out your copyright notice in the Description page of Project Settings.


//#include "Game/AHGameMode.h"
#include "AHGameMode.h"
#include "AmHaeng/Gimmick/AHChaseGimmickManager.h"
#include "AmHaeng/Gimmick/BeforeChase/AHSpline.h"
#include "AmHaeng/Mouse/AHMouseActor.h"
#include "AmHaeng/Player/AHVehiclePlayerController.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"
#include "AmHaeng/Widget/AHStartBtnWidget.h"
#include "AmHaeng/Widget/Gimmick/AHGimmickModeWidget.h"
#include "AmHaeng/Widget/Gimmick/AHNPCIsTargetWidget.h"
#include "AmHaeng/Widget/Minimap/AHMinimapWidget.h"

EGimmickMode AAHGameMode::NowGimmickMode = EGimmickMode::Patrol;
AAHVehiclePlayerController* AAHGameMode::PlayerController = nullptr;
AAHSpline* AAHGameMode::SplineActor = nullptr;
AAHGameMode::AAHGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT(
		"/Script/Engine.Blueprint'/Game/Player/Player_SportsCar_Pawn.Player_SportsCar_Pawn_C'"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<AAHVehiclePlayerController> PlayerControllerRef(
		TEXT(
			"/Script/Engine.Blueprint'/Game/Player/VehiclePlayerController2.VehiclePlayerController2_C'"));
	if (PlayerControllerRef.Class)
	{
		{
			PlayerControllerClass = PlayerControllerRef.Class;
		}
	}

	


	//Start Button Test
	//위젯 블루프린트 클래스를 받아옴
	static ConstructorHelpers::FClassFinder<UAHStartBtnWidget> StartBtnRef(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_StartBtn.WBP_StartBtn_C'"));

	//TSubclassOf 템플릿 클래스 객체에 블루프린트 클래스를 넣어줌
	if (StartBtnRef.Succeeded())
	{
		StartBtnWidgetClass = StartBtnRef.Class;
	}

	//Gimmick Text Reference
	static ConstructorHelpers::FClassFinder<UAHGimmickModeWidget> GimmickTextRef(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_GimmickText.WBP_GimmickText_C'"));

	//TSubclassOf 템플릿 클래스 객체에 블루프린트 클래스를 넣어줌
	if (GimmickTextRef.Succeeded())
	{
		GimmickModeWidgetClass = GimmickTextRef.Class;
	}

	//IsTargetCorrect Text Reference
	static ConstructorHelpers::FClassFinder<UAHNPCIsTargetWidget> IsTargetTextRef(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_IsTargetNPC.WBP_IsTargetNPC_C'"));

	//TSubclassOf 템플릿 클래스 객체에 블루프린트 클래스를 넣어줌
	if (IsTargetTextRef.Succeeded())
	{
		NPCIsTargetWidgetClass = IsTargetTextRef.Class;
	}

	//Minimap Widget Ref
	static ConstructorHelpers::FClassFinder<UAHMinimapWidget> MinimapWidgetRef(
	TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Minimap/WBP_Minimap.WBP_Minimap_C'"));

	//TSubclassOf 템플릿 클래스 객체에 블루프린트 클래스를 넣어줌
	if (MinimapWidgetRef.Succeeded())
	{
		MinimapWidgetClass = MinimapWidgetRef.Class;
	}

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

void AAHGameMode::BeginPlay()
{
	Super::BeginPlay();

	//Gimmick Mode Setting
	NowGimmickMode = EGimmickMode::Patrol;
	
	PlayerController = Cast<AAHVehiclePlayerController>(GetGameInstance()->GetFirstLocalPlayerController());
	
	Spawner = NewObject<UAHNPCSpawner>();
	//Spawner->Initialize(PlayerController);
	Spawner->SetNPCNumber(NPCNumber); //동기화

	//Chase Gimmick Setting
	ChaseGimmickClass = NewObject<AAHChaseGimmickManager>();
	ChaseGimmickClass->Rename(TEXT("ChaseGimmick"), this);

	//Mouse
	MouseActorSpawn();

	//Widgets
	//Todo : 위젯만 따로 Setting 하는 클래스 만들어도 될듯 GameModeWidgetSetting
	SpawnButtonOnViewport();
	GimmickTextOnViewport();
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

	MakeSpline();
}

//StartButton Widget Viewport에 띄우기
void AAHGameMode::SpawnButtonOnViewport()
{
	if (IsValid(StartBtnWidgetClass))
	{
		SpawnStartButton = Cast<UAHStartBtnWidget>(CreateWidget(GetWorld(), StartBtnWidgetClass));
		if (IsValid(SpawnStartButton))
		{
			SpawnStartButton->AddToViewport();
		}
	}
}

void AAHGameMode::GimmickTextOnViewport()
{
	if (IsValid(GimmickModeWidgetClass))
    	{
    		GimmickModeWidget = Cast<UAHGimmickModeWidget>(CreateWidget(GetWorld(), GimmickModeWidgetClass));
    		if (IsValid(GimmickModeWidget))
    		{
    			GimmickModeWidget->AddToViewport();
    		}
    	}
}

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
	SpawnStartButton->PushedStartButton.AddUFunction(this, FName("SetNPCSpawningState"), bIsNPCSpawning);
	//SpawnStartButton->PushedStartButton.AddUFunction(Spawner, FName("GetDelegateFromWidget"));

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
			ChasedNPC = HitVehicleBase;
			//ChasedNPC->SetMassOne();
			ChasedNPC->SetIsChased(true);
			ChasedNPC->AHDestroyFrontSphere();
			SetGimmickMode(EGimmickMode::Chase);
			AAHVehiclePlayerController::PlayerPawn->Brake();
			//play pause
			PlayPause(true);
			UE_LOG(LogTemp, Log, TEXT("Pause"));
			//Input 막고
			PlayerController->FlushPressedKeys();
			PlayerController->DisableInput(PlayerController);
			//AAHVehiclePlayerController::PlayerPawn->DisableInput(PlayerController);
			
			ChaseGimmickClass->StartChaseGimmick(PlayerController, HitVehicleBase, MinimapWidget);
		}
		NPCIsTargetWidget->SetNPCIsTargetWidget(HitVehicleBase->GetIsTargetNPC());
	}
}

void AAHGameMode::SetGimmickMode(EGimmickMode InGimmickMode)
{
	NowGimmickMode = InGimmickMode;
	if(GimmickChangeDelegate.IsBound())
	{
		GimmickChangeDelegate.Broadcast(InGimmickMode); //Widget Text 바꾸는 기능 밖에 없음 아직
	}
}

const EGimmickMode AAHGameMode::GetGimmickMode()
{
	return NowGimmickMode;
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