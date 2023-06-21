// Fill out your copyright notice in the Description page of Project Settings.


//#include "Game/AHGameMode.h"
#include "AHGameMode.h"
#include "AmHaeng/Mouse/AHMouseActor.h"
#include "AmHaeng/Player/AHVehiclePlayerController.h"
#include "AmHaeng/Spawner/AHNPCSpawner.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"
#include "AmHaeng/Widget/AHStartBtnWidget.h"
#include "AmHaeng/Widget/AHGimmickModeWidget.h"
#include "AmHaeng/Widget/AHNPCIsTargetWidget.h"

AAHGameMode::AAHGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT(
		"/Script/Engine.Blueprint'/Game/Player/Player_SportsCar_Pawn.Player_SportsCar_Pawn_C'"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerRef(
		TEXT(
			"/Script/Engine.Blueprint'/Game/Player/VehiclePlayerController.VehiclePlayerController_C'"));
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


	

	bIsNPCSpawning = false;


	//Gimmick Mode Setting
	NowGimmickMode = EGimmickMode::Patrol;
}

void AAHGameMode::BeginPlay()
{
	Super::BeginPlay();

	Spawner = NewObject<UAHNPCSpawner>();
	
	MouseActorSpawn();
	SpawnButtonOnViewport();
	GimmickTextOnViewport();
	IsTargetTextOnViewport();
	BindingDelegates();
	Spawner->Rename(TEXT("SpawnerOuter"), this);
	Spawner->GetSpawnActorsLocation();
	InitSpawnNPC();
	Spawner->TestSpawnNPC();
	
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
	APlayerController* pp = GetGameInstance()->GetFirstLocalPlayerController();
    if(pp)
	{
		PlayerController = Cast<AAHVehiclePlayerController>(pp);
	}
	
	if(PlayerController)
	{
		//CP Timer 시작할 때 Scan 중인 Actor 정보 가져옴
		//Timer 실행될 때마다 갈아끼우게 됨
		PlayerController->SendNowClickNPCToGameMode.BindUObject(this, &AAHGameMode::SetHitVehicleBase);
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

void AAHGameMode::CPLoadingFinished()
{
	UE_LOG(LogTemp, Log, TEXT("CP Loading Finished"));
	
	if(NowGimmickMode == EGimmickMode::Chase)
	{
		SetGimmickMode(EGimmickMode::Patrol);
	}
	else if(NowGimmickMode == EGimmickMode::Patrol)
	{
		SetGimmickMode(EGimmickMode::Chase);
	}

	//CP가 끝났을 때
	if(HitVehicleBase==nullptr)
	{
		return;
	}
	NPCIsTargetWidget->SetNPCIsTargetWidget(HitVehicleBase->GetIsTargetNPC());
}

void AAHGameMode::SetGimmickMode(EGimmickMode InGimmickMode)
{
	NowGimmickMode = InGimmickMode;
	if(GimmickChangeDelegate.IsBound())
	{
		GimmickChangeDelegate.Broadcast(InGimmickMode); //Widget Text 바꾸는 기능 밖에 없음 아직
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
		Spawner->NPCVehicleSpawn();
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Spawner is invalid"));
	}
}
