// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void MenuSetup();

protected:

	virtual	bool Initialize() override;

private:

	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;

	UFUNCTION()
	void HostButtonClicked();
	UFUNCTION()
	void JoinButtonClicked();

	// The subsystem designed to handle all online session functionality. 
	// This is the class that Menu will call to create, find, join, etc sessions. 
	// The subsystem will then handle the delegate calls for each of these functionalities and forward them to the Menu class.
	class UMultiplayerSessionsSubsystem* MultiplayerSessionsSubsystem;

};
