// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KillerDoll.generated.h"

class USpotLightComponent;
class UPointLightComponent;
class ASquidGameState;
UCLASS()
class SQUIDGAME_API AKillerDoll : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AKillerDoll();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<USkeletalMeshComponent> DollMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Light)
	TObjectPtr<USpotLightComponent> SpotLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Light)
	TObjectPtr<UPointLightComponent> PointLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	TObjectPtr<UAudioComponent> SoundsManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	TArray<TObjectPtr<USoundBase>> GreenLightSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	TObjectPtr<USoundBase> StartGameSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	TObjectPtr<USoundBase> EndGameSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float DirectionValue = 90.0f;
	
	UFUNCTION(BlueprintImplementableEvent)
	void TurnKillBP();

	UFUNCTION(BlueprintImplementableEvent)
	void TurnCountBP();

	bool GetKillerMode();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	TObjectPtr<ASquidGameState> GameState;

	void MovementTimeGame();

	void KillerTimeGame();

	bool bIsKillerMode = false;

	// Timers variable
	UPROPERTY(EditAnywhere, Category = Gameplay)
	float DelayStart = 7.0f;

	FTimerHandle TimerHandle;
};
