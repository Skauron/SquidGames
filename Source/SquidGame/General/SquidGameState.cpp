// Fill out your copyright notice in the Description page of Project Settings.

#include "General/SquidGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Character/MySquidGameCharacter.h"

ASquidGameState::ASquidGameState()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

void ASquidGameState::SetGameHasStarted()
{
    GameHasStart = true;
}

bool ASquidGameState::GetGameHasEnd()
{
    return GameHasEnd;
}

void ASquidGameState::BeginPlay()
{
    TArray<AActor *> TempPlayersActor;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMySquidGameCharacter::StaticClass(), TempPlayersActor);
    for (AActor *TempPlayerActor : TempPlayersActor)
    {
        Players.Add(Cast<AMySquidGameCharacter>(TempPlayerActor));
    }

    PlayerController = GetWorld()->GetFirstPlayerController();
}

void ASquidGameState::Tick(float DeltaTime)
{
    if (!GameHasEnd && GameHasStart)
    {
        Countdown -= DeltaTime;
        if (Countdown <= 0)
        {
            GameHasEnd = true;
            KillAllPlayers();
        }
    }
}

void ASquidGameState::CheckGameState()
{
    check(PlayerController);

    int PlayersWithGoal = 0;
    int DeadPlayers = 0;

    for (AMySquidGameCharacter *Player : Players)
    {
        if (Player)
        {
            if (Player->GetIsDead())
            {
                DeadPlayers++;
            }
            else
            {
                if (Player->GetReachGoal())
                {
                    PlayersWithGoal++;
                }
            }
        }
    }

    // Case 1: ALL PLAYER WINS
    if (DeadPlayers == 0 && PlayersWithGoal == Players.Num())
    {
        PlayerController->GameHasEnded(nullptr, true);
    }
    // Case 2: ALL PLAYER DIES
    else if (DeadPlayers == Players.Num())
    {
        PlayerController->GameHasEnded(nullptr, false);
    }
    // Case 3: ONE PLAYER WIN AND THE OTHER DIES
    else if ((PlayersWithGoal + DeadPlayers) == Players.Num())
    {
        APawn *PlayerPawn = PlayerController->GetPawn();
        PlayerController->GameHasEnded(PlayerPawn, true);
    }
}

void ASquidGameState::KillAllPlayers()
{
    for (AMySquidGameCharacter *Player : Players)
    {
        if (Player)
        {
            Player->SetIsDead();
        }
    }
}

int ASquidGameState::GetCountdown() const
{
    return Countdown;
}
