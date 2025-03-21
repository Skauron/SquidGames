// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "SquidPlayerController.generated.h"

class UEnhancedInputLocalPlayerSubsystem;
class UInputMappingContext;
class UInputAction;
class AMySquidGameCharacter;
UCLASS()
class SQUIDGAME_API ASquidPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	TObjectPtr<AMySquidGameCharacter> SquidCharacterP1;

	TObjectPtr<AMySquidGameCharacter> SquidCharacterP2;

	virtual void GameHasEnded(class AActor *EndGameFocus = nullptr, bool bIsWinner = false) override;

	UFUNCTION(BlueprintImplementableEvent)
	void AnnounceBothPlayersAsWinner();

	UFUNCTION(BlueprintImplementableEvent)
	void BothPlayersDie();

	UFUNCTION(BlueprintImplementableEvent)
	void OnlyOnePlayersLives();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Variables for the Input Enhanced System
	UPROPERTY()
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSubsystemP1;

	UPROPERTY()
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSubsystemP2;

	// Variables for the Input Actions
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> SquidGameContextP1;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> SquidGameContextP2;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MovementActionP1;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MovementActionP2;

	// Called to bind functionality to input
	void SetupInputComponent();

private:
	// Functions for the Input Actions for the players
	void MovementP1(const FInputActionValue &Value);

	void MovementP2(const FInputActionValue &Value);

	void StopP1();

	void StopP2();

	void RestartLevel();

	UPROPERTY(EditAnywhere)
	float RestartDelay = 3.0f;

	FTimerHandle RestartTimer;
};
