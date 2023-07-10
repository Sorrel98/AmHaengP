// Fill out your copyright notice in the Description page of Project Settings.


#include "AHBeforeChase.h"

#include "AmHaeng/Gimmick/BeforeChase/AHMannequin.h"
#include "AmHaeng/Player/AHPlayerPawn.h"
#include "AmHaeng/Player/AHVehiclePlayerController.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"
#include "AmHaeng/Widget/Gimmick/BeforeChase/AHChaseStartWidget.h"
#include "AmHaeng/Widget/Gimmick/BeforeChase/AHScreenCrashWidget.h"

AAHBeforeChase::AAHBeforeChase()
{
	static ConstructorHelpers::FClassFinder<UAHChaseStartWidget> ChaseStartRef(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_ChaseStartCutscene.WBP_ChaseStartCutscene_C'"));
	if (ChaseStartRef.Succeeded())
	{
		ChaseStartWidgetClass = ChaseStartRef.Class;
	}

	static  ConstructorHelpers::FClassFinder<UCameraShakeBase> CameraShakeRef(
		TEXT("/Script/Engine.Blueprint'/Game/Gimmick/CameraShake/BP_CrashCameraShake.BP_CrashCameraShake_C'"));
	if(CameraShakeRef.Succeeded())
	{
		CameraShakeClass = CameraShakeRef.Class;
	}
	static  ConstructorHelpers::FClassFinder<UAHScreenCrashWidget> CameraCrashRef(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_CrashGlass.WBP_CrashGlass_C'"));
	if(CameraCrashRef.Succeeded())
	{
		UE_LOG(LogTemp, Log, TEXT("CameraCrashClass is OK"));
		CameraCrashClass = CameraCrashRef.Class;
	}
	
	
}


void AAHBeforeChase::BeforeChaseProcess(AAHVehiclePlayerController* InPC, AAHNPCVehicleBase* InTargetNPC)
{
	UE_LOG(LogTemp, Log, TEXT("Before Chase Class"));
	AAHVehiclePlayerController::PlayerPawn->MannequinDetect.BindUObject(this, &AAHBeforeChase::PlayCrashWidget);
	PC = InPC;
	TargetNPC = InTargetNPC;
	//ThrowManager = NewObject<AAHThrowMannequin>();
	if(ChaseStartWidgetClass)
	{
		PlayChaseStartWidget();
	}
}

void AAHBeforeChase::PlayChaseStartWidget()
{
	if(ChaseStartWidgetClass)
	{
		UE_LOG(LogTemp, Log, TEXT("ChaseStartWidgetClass Is Valid"));
		if(GetWorld())
		{
			UE_LOG(LogTemp, Log, TEXT("GetWorld Is Valid"));
			ChaseStartWidget = Cast<UAHChaseStartWidget>(CreateWidget(GetWorld(), ChaseStartWidgetClass));
			if(IsValid(ChaseStartWidget))
			{
				ChaseStartWidget->SendToBeforeChaseClass.BindUObject(this, &AAHBeforeChase::FinishChaseStartWidget);
				ChaseStartWidget->AddToViewport();
				ChaseStartWidget->PlayAnims();
			}
		}
		
	}
}

void AAHBeforeChase::FinishChaseStartWidget()
{
	UE_LOG(LogTemp, Log, TEXT("ReStart"));
	SetPause(false);
	//Throw Mannequin
	ThrowMannequin();
}

void AAHBeforeChase::SetPause(bool InPause)
{
	PC->SetPause(InPause);
}

void AAHBeforeChase::RagdollMannequinSpawn()
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

	FSoftObjectPath RagdollMannequinBPRef(
		TEXT("/Script/Engine.Blueprint'/Game/Gimmick/ThrowMannequin/RagdollMannequin.RagdollMannequin'"));
	if (!RagdollMannequinBPRef.IsValid())
	{
		return;
	}
	UBlueprint* RagdollMannequinBP = Cast<UBlueprint>(RagdollMannequinBPRef.TryLoad());
	if (RagdollMannequinBP == nullptr)
	{
		return;
	}
	UClass* RagdollMannequinClass;
	RagdollMannequinClass = RagdollMannequinBP->GeneratedClass;
	if (RagdollMannequinClass == nullptr)
	{
		return;
	}
	Mannequin = World->SpawnActor<AAHMannequin>(RagdollMannequinClass, TargetNPC->GetActorLocation(), TargetNPC->GetActorRotation());
}

void AAHBeforeChase::ThrowMannequin()
{
	RagdollMannequinSpawn();
	
	//여기서 마네킹 던집니다.
	if(TargetNPC && AAHVehiclePlayerController::PlayerPawn && Mannequin)
	{
		Mannequin->SetSplineRoute(TargetNPC->GetActorLocation(), AAHVehiclePlayerController::PlayerPawn->GetMannequinTarget()->GetComponentLocation());
	}
	if(!TargetNPC)
	{
		UE_LOG(LogTemp, Log, TEXT("!TargetNPC"));
	}
	if(!AAHVehiclePlayerController::PlayerPawn)
	{
		UE_LOG(LogTemp, Log, TEXT("!PlayerPawn"));
	}
	if(!Mannequin)
	{
		UE_LOG(LogTemp, Log, TEXT("!Mannequin"));
	}
	Mannequin->Throw();
	
	//하자마자 Delegate로 Chase 시작 알림
	StartChaseDelegate.Execute();
}

void AAHBeforeChase::CameraShake()
{
	UE_LOG(LogTemp, Warning, TEXT("Camera Shake Start"));
	PC->ClientStartCameraShake(CameraShakeClass, 1000000.0);
}

void AAHBeforeChase::PlayCrashWidget()
{
	UE_LOG(LogTemp, Warning, TEXT("PlayCrashWidget Start"));
	CameraShake();
	if(CameraCrashClass)
	{
		CameraCrashWidget = Cast<UAHScreenCrashWidget>(CreateWidget(GetWorld(), CameraCrashClass));
		if(IsValid(CameraCrashWidget))
		{
			CameraCrashWidget->PlayAnims();
		}
	}
	
}
