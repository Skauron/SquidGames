// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Goal.h"
#include "Components/BoxComponent.h"
#include "Character/MySquidGameCharacter.h"

// Sets default values
AGoal::AGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GoalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GoalMesh"));
	RootComponent = GoalMesh;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGoal::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AGoal::OverlapBegin);
}

// Called every frame
void AGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGoal::OverlapBegin(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(AMySquidGameCharacter::StaticClass()))
	{
		AMySquidGameCharacter* Player = Cast<AMySquidGameCharacter>(OtherActor);
		if(!Player->GetIsDead()){
			Player->ReachGoal();
		}
	}
}