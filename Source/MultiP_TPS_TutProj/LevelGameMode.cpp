// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelGameMode.h"
#include "MultiplayerSessionsSubsystem.h"
#include "Kismet/GameplayStatics.h"

void ALevelGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Only the server should call StartSession
	if (!HasAuthority())
	{
		return;
	}

	UGameInstance* GI = GetGameInstance();
	if (!GI)
	{
		UE_LOG(LogTemp, Error, TEXT("LevelGameMode::BeginPlay - No GameInstance"));
		return;
	}

	// With seamless travel enabled we can safely start the online session here.
	if (UMultiplayerSessionsSubsystem* MSS = GI->GetSubsystem<UMultiplayerSessionsSubsystem>())
	{
		UE_LOG(LogTemp, Log, TEXT("LevelGameMode::BeginPlay - calling MSS->StartSession()"));
		MSS->StartSession();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("LevelGameMode::BeginPlay - MultiplayerSessionsSubsystem not found"));
	}
}
