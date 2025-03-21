// Fill out your copyright notice in the Description page of Project Settings.

#include "General/SquidPlayerController.h"

#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/MySquidGameCharacter.h"
#include "Kismet/GameplayStatics.h"

void ASquidPlayerController::BeginPlay()
{
    // Get the enhanced input subsystem Player 1
    if (APlayerController *PlayerController = UGameplayStatics::GetPlayerController(this, 0))
    {
        SquidCharacterP1 = Cast<AMySquidGameCharacter>(PlayerController->GetPawn());
        // SquidCharacterP1->SetPlayerIndex(0);
        if (InputSubsystemP1 = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
        {
            // Add the mapping context so we get controls
            InputSubsystemP1->AddMappingContext(SquidGameContextP1, 0);
        }
    }

    // Get the enhanced input subsystem Player 2
    if (APlayerController *PlayerController2 = UGameplayStatics::GetPlayerController(this, 1))
    {
        SquidCharacterP2 = Cast<AMySquidGameCharacter>(PlayerController2->GetPawn());
        // SquidCharacterP2->SetPlayerIndex(1);
        if (InputSubsystemP2 = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
        {
            // Add the mapping context so we get controls
            InputSubsystemP2->AddMappingContext(SquidGameContextP2, 0);
        }
    }
}

void ASquidPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    if (UEnhancedInputComponent *EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInputComponent->BindAction(MovementActionP1, ETriggerEvent::Triggered, this, &ASquidPlayerController::MovementP1);
        EnhancedInputComponent->BindAction(MovementActionP2, ETriggerEvent::Triggered, this, &ASquidPlayerController::MovementP2);
        EnhancedInputComponent->BindAction(MovementActionP1, ETriggerEvent::Completed, this, &ASquidPlayerController::StopP1);
        EnhancedInputComponent->BindAction(MovementActionP2, ETriggerEvent::Completed, this, &ASquidPlayerController::StopP2);
    }
}

void ASquidPlayerController::MovementP1(const FInputActionValue &Value)
{
    // input is a Vector2D
    FVector2D MovementVector = Value.Get<FVector2D>();
    if (SquidCharacterP1)
    {
        SquidCharacterP1->Move(MovementVector);
    }
}

void ASquidPlayerController::MovementP2(const FInputActionValue &Value)
{
    // input is a Vector2D
    FVector2D MovementVector = Value.Get<FVector2D>();
    if (SquidCharacterP2)
    {
        SquidCharacterP2->Move(MovementVector);
    }
}

void ASquidPlayerController::StopP1()
{
    if (SquidCharacterP1)
    {
        SquidCharacterP1->Stop();
    }
}

void ASquidPlayerController::StopP2()
{
    if (SquidCharacterP2)
    {
        SquidCharacterP2->Stop();
    }
}

void ASquidPlayerController::RestartLevel()
{
    if (GetWorld())
    {
        UGameplayStatics::OpenLevel(GetWorld(), "GreenLightRedLight", false);
    }
}

void ASquidPlayerController::GameHasEnded(class AActor *EndGameFocus, bool bIsWinner)
{
    if (EndGameFocus == nullptr)
    {
        if (bIsWinner)
        {
            AnnounceBothPlayersAsWinner();
        }
        else
        {
            BothPlayersDie();
            GetWorldTimerManager().SetTimer(RestartTimer, this, &ASquidPlayerController::RestartLevel, RestartDelay);
        }
    }
    else
    {
        BothPlayersDie();
        GetWorldTimerManager().SetTimer(RestartTimer, this, &ASquidPlayerController::RestartLevel, RestartDelay);
    }
}
