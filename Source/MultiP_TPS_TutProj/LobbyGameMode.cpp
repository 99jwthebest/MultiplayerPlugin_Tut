// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "MultiplayerSessionsSubsystem.h"


ALobbyGameMode::ALobbyGameMode()
{
	// Preserve the network driver across server travel to avoid SteamSockets re-listen conflicts.
	bUseSeamlessTravel = true;
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (GameState)
	{
		int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				1, // 1 is the key for this message, if another message with the same key is added, it will replace the previous one
				60.f, 
				FColor::Yellow, 
				FString::Printf(TEXT("Players in game: %d"), NumberOfPlayers)
			);

			APlayerState* PlayerState = NewPlayer->GetPlayerState<APlayerState>();
			if (PlayerState)
			{
				FString PlayerName = PlayerState->GetPlayerName();
				GEngine->AddOnScreenDebugMessage(
					-1,
					60.f,
					FColor::Cyan,
					FString::Printf(TEXT("%s has joined the game!"), *PlayerName)
				);
			}
		}

		// Update auto-start logic whenever a player joins
		UpdateAutoStartTimer();
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	APlayerState* PlayerState = Exiting->GetPlayerState<APlayerState>();
	if (PlayerState)
	{
		int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();

		GEngine->AddOnScreenDebugMessage(
			1, // 1 is the key for this message, if another message with the same key is added, it will replace the previous one
			60.f,
			FColor::Yellow,
			FString::Printf(TEXT("Players in game: %d"), NumberOfPlayers - 1)
		);

		FString PlayerName = PlayerState->GetPlayerName();
		GEngine->AddOnScreenDebugMessage(
			-1,
			60.f,
			FColor::Red,
			FString::Printf(TEXT("%s has exited the game!"), *PlayerName)
		);
	}

	// Update auto-start logic when players leave
	UpdateAutoStartTimer();
}

void ALobbyGameMode::StartMatchNow()
{
	if (!HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("StartMatchNow called on non-authority. Ignoring."));
		return;
	}

	// Stop the timer if it was running.
	if (bAutoStartTimerActive)
	{
		bAutoStartTimerActive = false;
		GetWorldTimerManager().ClearTimer(AutoStartTimerHandle);
	}

	// Just do the travel here. StartSession will be executed on the gameplay GameMode after load.
	const FString TravelURL = TEXT("/Game/_MyFiles/Levels/Level1?listen");
	UE_LOG(LogTemp, Log, TEXT("StartMatchNow: ServerTravel to %s"), *TravelURL);
	if (GetWorld())
	{
		GetWorld()->ServerTravel(TravelURL);
	}
}

void ALobbyGameMode::OnSubsystemStartSessionComplete(bool bWasSuccessful)
{
	UE_LOG(LogTemp, Log, TEXT("OnSubsystemStartSessionComplete: bWasSuccessful=%s"), bWasSuccessful ? TEXT("true") : TEXT("false"));

	// Unbind to avoid duplicate calls.
	if (UGameInstance* GI = GetGameInstance())
	{
		if (UMultiplayerSessionsSubsystem* MSS = GI->GetSubsystem<UMultiplayerSessionsSubsystem>())
		{
			MSS->MultiplayerOnStartSessionComplete.RemoveDynamic(this, &ALobbyGameMode::OnSubsystemStartSessionComplete);
		}
	}

	if (!bWasSuccessful)
	{
		UE_LOG(LogTemp, Error, TEXT("OnSubsystemStartSessionComplete: Failed to start session."));
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Failed to start session."));
		}
		return;
	}

	const FString TravelURL = TEXT("/Game/_MyFiles/Levels/Level1?listen");
	UE_LOG(LogTemp, Log, TEXT("OnSubsystemStartSessionComplete: Starting match and ServerTravel to %s"), *TravelURL);

	if (GetWorld())
	{
		GetWorld()->ServerTravel(TravelURL);
	}
}

void ALobbyGameMode::AutoStartMatch()
{
	bAutoStartTimerActive = false;

	// Auto-start just defers to the same logic as manual start.
	StartMatchNow();
}

void ALobbyGameMode::UpdateAutoStartTimer()
{
	if (!GameState)
	{
		return;
	}

	const int32 CurrentPlayers = GameState->PlayerArray.Num();

	// If enough players and timer not active, start countdown.
	if (CurrentPlayers >= MinPlayersToStart && !bAutoStartTimerActive)
	{
		bAutoStartTimerActive = true;
		GetWorldTimerManager().SetTimer(AutoStartTimerHandle, this, &ALobbyGameMode::AutoStartMatch, AutoStartDelaySeconds, false);

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, AutoStartDelaySeconds, FColor::Green, TEXT("Auto-start timer started."));
		}
	}
	// If not enough players and timer active, cancel countdown.
	else if (CurrentPlayers < MinPlayersToStart && bAutoStartTimerActive)
	{
		bAutoStartTimerActive = false;
		GetWorldTimerManager().ClearTimer(AutoStartTimerHandle);

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Auto-start timer cancelled (not enough players)."));
		}
	}
}
