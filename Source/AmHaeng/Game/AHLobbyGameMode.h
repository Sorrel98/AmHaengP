// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AHLobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class AMHAENG_API AAHLobbyGameMode : public AGameMode
{
	GENERATED_BODY()
	AAHLobbyGameMode();

	virtual void BeginPlay() override;

	void LobbyWidgetOnViewport();

	void OpenAHGameLevel();
private:
	TSubclassOf<class UUserWidget> LobbyWidgetClass;
	class UAHLobbyWidget* LobbyWidget;

	FString AHGameLevelName = "AmHaengLevel";

	static bool IsFirstLobby;
};
