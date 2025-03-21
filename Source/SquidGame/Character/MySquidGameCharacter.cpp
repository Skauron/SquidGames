// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/MySquidGameCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Actors/KillerDoll.h"
#include "Kismet/GameplayStatics.h"
#include "General/SquidGameState.h"

// Sets default values
AMySquidGameCharacter::AMySquidGameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;			 // Character moves in the direction of input...
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;							// Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character)
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

// Called when the game starts or when spawned
void AMySquidGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerNumber = FMath::RandRange(1, 456);
	KillerDoll = Cast<AKillerDoll>(UGameplayStatics::GetActorOfClass(GetWorld(), AKillerDoll::StaticClass()));
}

// Called every frame
void AMySquidGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (KillerDoll->GetKillerMode() && !bIsDead && bIsMoving && !bIsSafe)
	{
		SetIsDead();
	}

	if(bFinalSteps){
		Timer += DeltaTime;

		AddMovementInput(FVector(0.0f, -1.0f, 0.0f), 1.0f);
		if(Timer >= MaxTime){
			bFinalSteps = false;
		}
	}
}

// Called to bind functionality to input
void AMySquidGameCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMySquidGameCharacter::Move(FVector2D MovementVector)
{
	if (Controller != nullptr && !bIsDead && !bIsSafe)
	{
		bIsMoving = true;
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMySquidGameCharacter::Stop()
{
	if (Controller != nullptr && !bIsDead)
	{
		bIsMoving = false;
	}
}

void AMySquidGameCharacter::ReachGoal()
{
	if(!bIsSafe){
		bIsSafe = true;
		bReachGoal = true;
		bFinalSteps = true;
		AnnouncePlayerAsWinner();
		ASquidGameState* GameState = Cast<ASquidGameState>(GetWorld()->GetGameState());
		if(GameState){
			GameState->CheckGameState();
		}
	}
}

bool AMySquidGameCharacter::GetReachGoal()
{
	return bReachGoal;
}

bool AMySquidGameCharacter::GetIsDead()
{
	return bIsDead;
}

void AMySquidGameCharacter::SetIsDead()
{
	bIsDead = true;
	GetMesh()->SetSimulatePhysics(true);
	ASquidGameState* GameState = Cast<ASquidGameState>(GetWorld()->GetGameState());
	if(GameState){
		GameState->CheckGameState();
	}
}

int AMySquidGameCharacter::GetPlayerNumber() const
{
	return PlayerNumber;
}