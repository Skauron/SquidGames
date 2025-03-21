// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SquidGameCameraActor.generated.h"

class UCameraComponent;
class AMySquidGameCharacter;
UCLASS()
class SQUIDGAME_API ASquidGameCameraActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASquidGameCameraActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ViewTarget)
	TArray<TObjectPtr<AMySquidGameCharacter>> ViewTargets;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Controller)
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float CustomOffsetY = 500.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void InitTargets();

	int CheckDistanceTargets();

	FVector CurrentLocation;

	int NearTarget = 0;

	// Timers variable
	UPROPERTY(EditAnywhere, Category = Timer)
	float DelayStart = 0.1f;

	FTimerHandle TimerHandle;
};
