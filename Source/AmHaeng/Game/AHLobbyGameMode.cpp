// Fill out your copyright notice in the Description page of Project Settings.


#include "AHLobbyGameMode.h"

#include "AmHaeng/Player/AHPlayerPawn.h"
#include "AmHaeng/Widget/Lobby/AHLobbyWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

bool AAHLobbyGameMode::IsFirstLobby = true;

AAHLobbyGameMode::AAHLobbyGameMode()
{
	static ConstructorHelpers::FClassFinder<APlayerController> LobbyControllerRef(
	TEXT(
		"/Script/Engine.Blueprint'/Game/GameManager/Lobby/PC_Lobby.PC_Lobby_C'"));
	if (LobbyControllerRef.Class)
	{
		{
			PlayerControllerClass = LobbyControllerRef.Class;
		}
	}
	
	static ConstructorHelpers::FClassFinder<UUserWidget> LobbyWidgetRef(TEXT(
		"/Script/UMGEditor.WidgetBlueprint'/Game/UI/Lobby/WBP_LobbyWidget.WBP_LobbyWidget_C'"));
	if (LobbyWidgetRef.Succeeded())
	{
		LobbyWidgetClass = LobbyWidgetRef.Class;
	}
}

void AAHLobbyGameMode::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Lobby BeginPlay"));
	Super::BeginPlay();
	LobbyWidgetOnViewport();
	
	UE_LOG(LogTemp, Log, TEXT("Final Reputation : %d"), AAHPlayerPawn::Reputation);
	LobbyWidget->StartBtnClickedDelegate.BindUObject(this, &AAHLobbyGameMode::OpenAHGameLevel);
}

void AAHLobbyGameMode::LobbyWidgetOnViewport()
{
	if (IsValid(LobbyWidgetClass))
	{
		LobbyWidget = Cast<UAHLobbyWidget>(CreateWidget(GetWorld(), LobbyWidgetClass));
		if (IsValid(LobbyWidget))
		{
			LobbyWidget->SetReputationTextValue(AAHPlayerPawn::Reputation);
			LobbyWidget->AddToViewport();
			if(IsFirstLobby)
			{
				LobbyWidget->InVisibleReputation();
				IsFirstLobby = false;
			}
			else
			{
				LobbyWidget->VisibleReputation();
			}
		}
	}
}

void AAHLobbyGameMode::OpenAHGameLevel()
{
	UGameplayStatics::OpenLevel(this, *AHGameLevelName);
}
