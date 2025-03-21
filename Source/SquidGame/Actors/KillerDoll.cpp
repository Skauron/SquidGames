// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/KillerDoll.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/PointLightComponent.h"
#include "General/SquidGameState.h"

// Sets default values
AKillerDoll::AKillerDoll()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DollMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DollMesh"));
	RootComponent = DollMesh;

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(RootComponent);

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(RootComponent);
}

bool AKillerDoll::GetKillerMode()
{
	return bIsKillerMode;
}

// Called when the game starts or when spawned
void AKillerDoll::BeginPlay()
{
	Super::BeginPlay();

	GameState = Cast<ASquidGameState>(GetWorld()->GetGameState());

	SoundsManager = NewObject<UAudioComponent>(this);
	SoundsManager->SetSound(StartGameSound);
	SoundsManager->Play();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AKillerDoll::MovementTimeGame, DelayStart, false);
}

void AKillerDoll::MovementTimeGame()
{
	if(!GameState->GetGameHasEnd()){
		if(GameState){
			GameState->SetGameHasStarted();
		}
	
		SpotLight->SetLightColor(FColor::Green);
		PointLight->SetLightColor(FColor::Green);
		bIsKillerMode = false;
		DirectionValue = 180.0f;
		SoundsManager->SetSound(GreenLightSounds[FMath::RandRange(0, GreenLightSounds.Num() - 1)]);
		SoundsManager->Play();
		TurnCountBP();
		DelayStart = SoundsManager->Sound->Duration;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AKillerDoll::KillerTimeGame, DelayStart, false);
	}
}

void AKillerDoll::KillerTimeGame()
{
	if(!GameState->GetGameHasEnd()){
		SpotLight->SetLightColor(FColor::Red);
		PointLight->SetLightColor(FColor::Red);
		bIsKillerMode = true;
		DirectionValue = -180.0f;
		TurnKillBP();
		DelayStart = FMath::RandRange(2.0f, 6.0f);
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AKillerDoll::MovementTimeGame, DelayStart, false);
	}
}
