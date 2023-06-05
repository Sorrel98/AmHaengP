// Fill out your copyright notice in the Description page of Project Settings.


//#include "Game/AHGameMode.h"
#include "AHGameMode.h"
#include "AmHaeng/Spawner/AHNPCSpawner.h"

AAHGameMode::AAHGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Script/Engine.Blueprint'/Game/VehicleTemplate/Blueprints/SportsCar/SportsCar_Pawn.SportsCar_Pawn_C'"));
	if(DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerRef(TEXT("/Script/Engine.Blueprint'/Game/VehicleTemplate/Blueprints/VehiclePlayerController.VehiclePlayerController_C'"));
	if (PlayerControllerRef.Class)
	{
		{
			PlayerControllerClass = PlayerControllerRef.Class;
		}
	}


	//Start Button Test
	//위젯 블루프린트 클래스를 받아옴
	static ConstructorHelpers::FClassFinder<UAHStartBtnWidget> StartBtnRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_StartBtn.WBP_StartBtn_C'"));
	
	//TSubclassOf 템플릿 클래스 객체에 블루프린트 클래스를 넣어줌
	if (StartBtnRef.Succeeded())
	{
		WidgetClass = StartBtnRef.Class;
	}

	bIsNPCSpawning = false;
	//UE_LOG(LogTemp, Log, TEXT("Spawn Function Stated : %u"), bIsNPCSpawning);
}

void AAHGameMode::BeginPlay()
{
	Super::BeginPlay();
	StartButtonOnViewport();
	BindingWithWidgetDelegate();

	
	Spawner->Rename(TEXT("SpawnerOuter"), this);

}

//StartButton Widget Viewport에 띄우기
void AAHGameMode::StartButtonOnViewport()
{
	if (IsValid(WidgetClass))
	{
		SpawnStartButton = Cast<UAHStartBtnWidget>(CreateWidget(GetWorld(), WidgetClass));
		if (IsValid(SpawnStartButton))
		{
			SpawnStartButton->AddToViewport();
		}
	}
}

//Delegate와 Button을 Binding
void AAHGameMode::BindingWithWidgetDelegate()
{
	SpawnStartButton->PushedStartButton.AddUFunction(this, FName("SetNPCSpawningState"), bIsNPCSpawning);

	Spawner = NewObject<UAHNPCSpawner>();
	SpawnStartButton->PushedStartButton.AddUFunction(Spawner, FName("GetDelegateFromWidget"));
}

//Delegate 오면 실행될 함수 (spawning 되고 있는지 mode가 알기 위하여 state 변경)
void AAHGameMode::SetNPCSpawningState(uint8 NowState)
{
	bIsNPCSpawning = !NowState;
	//UE_LOG(LogTemp, Log, TEXT("[GameMode] Spawn Function Stated : %u"), bIsNPCSpawning);
}
