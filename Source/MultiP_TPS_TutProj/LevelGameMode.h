// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LevelGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MULTIP_TPS_TUTPROJ_API ALevelGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

};
