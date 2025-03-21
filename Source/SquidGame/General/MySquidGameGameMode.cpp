// Fill out your copyright notice in the Description page of Project Settings.

#include "General/MySquidGameGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

void AMySquidGameGameMode::BeginPlay()
{
    Super::BeginPlay();
    // Get the GameInstance to create the local player
    UGameInstance *GameInstance = GetGameInstance();
    if (GameInstance)
    {
        GameInstance->CreateLocalPlayer(1, Error1, true);
    }
}

AActor *AMySquidGameGameMode::FindPlayerStart_Implementation(AController *Player, const FString &IncomingName)
{
    Super::FindPlayerStart_Implementation(Player, IncomingName);
    TArray<AActor *> PlayerStarts;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);

    if (PlayerStarts.Num() == 0)
        return nullptr;

    // Determinate the player index
    int32 PlayerIndex = UGameplayStatics::GetPlayerControllerID(Cast<APlayerController>(Player));

    // Choose a different PlayerStart according to the players index
    if (PlayerIndex >= 0 && PlayerIndex < PlayerStarts.Num())
    {
        return PlayerStarts[PlayerIndex];
    }

    return PlayerStarts[0];
}
