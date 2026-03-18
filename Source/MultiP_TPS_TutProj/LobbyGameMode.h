// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MULTIP_TPS_TUTPROJ_API ALobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ALobbyGameMode(); // <-- added constructor

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	// Allows host (on a listen server) to immediately start the match.
	UFUNCTION(BlueprintCallable)
	void StartMatchNow();

protected:
	// Called when the subsystem informs us StartSession completed.
	UFUNCTION()
	void OnSubsystemStartSessionComplete(bool bWasSuccessful);

private:
	// Start the match due to the auto-start timer expiring.
	void AutoStartMatch();

	// Check and start/cancel the auto-start timer based on player count.
	void UpdateAutoStartTimer();

	// Config
	int32 MinPlayersToStart{ 2 };
	float AutoStartDelaySeconds{ 20.0f };

	FTimerHandle AutoStartTimerHandle;
	bool bAutoStartTimerActive{ false };

};
