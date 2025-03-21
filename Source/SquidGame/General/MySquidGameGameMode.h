// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MySquidGameGameMode.generated.h"

/**
 *
 */
UCLASS()
class SQUIDGAME_API AMySquidGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	FString Error1 = FString(TEXT("Error"));

	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName) override;
};
