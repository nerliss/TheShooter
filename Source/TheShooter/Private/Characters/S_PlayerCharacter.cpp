// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/S_PlayerCharacter.h"
#include "Interfaces/S_InteractInterface.h"

AS_PlayerCharacter::AS_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;



}

void AS_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AS_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AS_PlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		// Setup action bindings
		PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AS_BaseCharacter::StartJumping);
		PlayerInputComponent->BindAction("Jump", IE_Released, this, &AS_BaseCharacter::StopJumping);
		PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AS_BaseCharacter::StartSprinting);
		PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AS_BaseCharacter::StopSprinting);
		PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AS_PlayerCharacter::Interact);

		// Setup axis bindings
		PlayerInputComponent->BindAxis("MoveForward", this, &AS_PlayerCharacter::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &AS_PlayerCharacter::MoveRight);

		PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
		PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	}
}

void AS_PlayerCharacter::MoveForward(float Value)
{
	if (Controller && Value != 0.f)
	{
		APawn::AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AS_PlayerCharacter::MoveRight(float Value)
{
	if (Controller && Value != 0.f)
	{
		APawn::AddMovementInput(GetActorRightVector(), Value);
	}
}

void AS_PlayerCharacter::Interact()
{
	if (InteractActor && InteractActor->GetClass()->ImplementsInterface(US_InteractInterface::StaticClass()))
	{
		IS_InteractInterface::Execute_Interact(InteractActor, this);
	}
}

