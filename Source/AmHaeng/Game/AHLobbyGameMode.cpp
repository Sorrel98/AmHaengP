// Fill out your copyright notice in the Description page of Project Settings.


#include "AHLobbyGameMode.h"

#include "AmHaeng/Player/AHPlayerPawn.h"
#include "AmHaeng/Widget/Lobby/AHLobbyWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

bool AAHLobbyGameMode::IsFirstLobby = true;

AAHLobbyGameMode::AAHLobbyGameMode()
{
}

void AAHLobbyGameMode::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Lobby BeginPlay"));
	UE_LOG(LogTemp, Log, TEXT("IsFirstLobby : %d"), IsFirstLobby);
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
				UE_LOG(LogTemp, Log, TEXT("IsFirstLobby"));
				LobbyWidget->InVisibleReputation();
				IsFirstLobby = false;
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("IsNotFirstLobby"));
				LobbyWidget->VisibleReputation();
			}
		}
	}
}

void AAHLobbyGameMode::OpenAHGameLevel()
{
	UGameplayStatics::OpenLevel(this, *AHGameLevelName);
}
