// Fill out your copyright notice in the Description page of Project Settings.


#include "AHBeforeChase.h"

#include "AmHaeng/Gimmick/BeforeChase/AHMannequin.h"
#include "AmHaeng/Player/AHPlayerPawn.h"
#include "AmHaeng/Player/AHVehiclePlayerController.h"
#include "AmHaeng/VehicleNPC/AHNPCVehicleBase.h"
#include "AmHaeng/Widget/Gimmick/BeforeChase/AHChaseStartWidget.h"
#include "AmHaeng/Widget/Gimmick/BeforeChase/AHScreenCrashWidget.h"

void AAHBeforeChase::BeforeChaseProcess(AAHVehiclePlayerController* InPC, AAHNPCVehicleBase* InTargetNPC)
{
	if(InPC->GetPlayerPawn())
	{
		InPC->GetPlayerPawn()->MannequinDetect.BindUObject(this, &AAHBeforeChase::PlayCrashWidget);
	}
	PlayerController = InPC;
	ChasedNPC = InTargetNPC;
}

void AAHBeforeChase::PlayChaseStartAnim()
{
	if(ChaseStartWidget)
	{
		ChaseStartWidget->PlayAnims();
	}
}

void AAHBeforeChase::SettingChaseStartWidget()
{
	if(ChaseStartWidgetClass)
	{
		if(GetWorld())
		{
			ChaseStartWidget = Cast<UAHChaseStartWidget>(CreateWidget(GetWorld(), ChaseStartWidgetClass));
			if(IsValid(ChaseStartWidget))
			{
				ChaseStartWidget->SendToBeforeChaseClass.BindUObject(this, &AAHBeforeChase::FinishChaseStartWidget);
				ChaseStartWidget->AddToViewport();
			}
		}
		
	}
}

void AAHBeforeChase::FinishChaseStartWidget()
{
	UE_LOG(LogTemp, Log, TEXT("Finish Chase Start Widget Anim"));
	if(PlayerController)
	{
		UE_LOG(LogTemp, Log, TEXT("UnPause"));
		PlayerController->SetPause(false);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Player Controller 가 없습니다"));
	}
	//Throw Mannequin
	ThrowMannequin();
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
	if(MannequinClass)
	{
		Mannequin = World->SpawnActor<AAHMannequin>(MannequinClass, ChasedNPC->GetActorLocation(), ChasedNPC->GetActorRotation());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MannequinClass Is not Valid"));
	}
	
}

void AAHBeforeChase::ThrowMannequin()
{
	RagdollMannequinSpawn();
	
	//여기서 마네킹 던집니다.
	if(ChasedNPC && AAHVehiclePlayerController::PlayerPawn && Mannequin)
	{
		Mannequin->SetSplineRoute(ChasedNPC->GetActorLocation(), AAHVehiclePlayerController::PlayerPawn->GetMannequinTarget()->GetComponentLocation());
	}
	if(!ChasedNPC)
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
	if(PlayerController)
	{
		if(CameraCrashClass)
		{
			PlayerController->ClientStartCameraShake(CameraShakeClass, 1000000.0);
		}
	}
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

