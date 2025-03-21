// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MySquidGameCharacter.generated.h"

class AKillerDoll;
class ASquidGameCameraActor;
UCLASS()
class SQUIDGAME_API AMySquidGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMySquidGameCharacter();

	bool GetReachGoal();

	bool GetIsDead();

	void SetIsDead();

	UFUNCTION(BlueprintPure)
	int GetPlayerNumber() const;

	UFUNCTION(BlueprintImplementableEvent)
	void AnnouncePlayerAsWinner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(FVector2D MovementVector);

	void Stop();

	void ReachGoal();

private:
	UPROPERTY()
	TObjectPtr<AKillerDoll> KillerDoll;

	bool bIsDead = false;

	bool bIsMoving = false;

	bool bIsSafe = false;

	bool bReachGoal = false;

	bool bFinalSteps = false;

	int PlayerNumber;

	float Timer = 0.0f;

	float MaxTime = 1.0f;
};
