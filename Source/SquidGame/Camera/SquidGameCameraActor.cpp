// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera/SquidGameCameraActor.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Character/MySquidGameCharacter.h"

// Sets default values
ASquidGameCameraActor::ASquidGameCameraActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	RootComponent = Camera;
}

// Called when the game starts or when spawned
void ASquidGameCameraActor::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	PlayerController->SetViewTargetWithBlend(this, 1.0f);
	CurrentLocation = GetActorLocation();

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ASquidGameCameraActor::InitTargets, DelayStart, false);
}

// Called every frame
void ASquidGameCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ViewTargets.Num() != 0)
	{
		NearTarget = CheckDistanceTargets();
		FVector TargetLocation = ViewTargets[NearTarget]->GetActorLocation();
		SetActorLocation(FVector(CurrentLocation.X, TargetLocation.Y + CustomOffsetY, CurrentLocation.Z));
	}
}

void ASquidGameCameraActor::InitTargets()
{
	TArray<AActor *> TempViewActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMySquidGameCharacter::StaticClass(), TempViewActors);
	for (AActor *TempViewActor : TempViewActors)
	{
		ViewTargets.Add(Cast<AMySquidGameCharacter>(TempViewActor));
	}
}

int ASquidGameCameraActor::CheckDistanceTargets()
{
	int NearIndex = 0;
	float MinDistance = TNumericLimits<float>::Max();
	
	for (int i = 0; i < ViewTargets.Num(); i++)
	{
		if (!ViewTargets[i]->GetIsDead())
		{
			float Distance = FVector::Dist(GetActorLocation(), ViewTargets[i]->GetActorLocation());
			if (Distance < MinDistance)
			{
				MinDistance = Distance;
				NearIndex = i;
			}
		}
	}
	return NearIndex;
}
