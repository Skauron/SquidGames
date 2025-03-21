// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SquidGameState.generated.h"

class AMySquidGameCharacter;
UCLASS()
class SQUIDGAME_API ASquidGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ASquidGameState();

	TArray<TObjectPtr<AMySquidGameCharacter>> Players;

	void SetGameHasStarted();

	bool GetGameHasEnd();

	void CheckGameState();

	void KillAllPlayers();

	UFUNCTION(BlueprintPure)
	int GetCountdown() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool GameHasStart = false;

	bool GameHasEnd = false;

	float Countdown = 60.0f;
};
