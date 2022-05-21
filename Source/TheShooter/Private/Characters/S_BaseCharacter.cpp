// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/S_BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/S_HealthComponent.h"

AS_BaseCharacter::AS_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Configure movement component
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 360.f, 0);
	GetCharacterMovement()->MaxWalkSpeed = 450.f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 200.f;
	GetCharacterMovement()->AirControl = 0.1f;

	// Health Component
	HealthComp = CreateDefaultSubobject<US_HealthComponent>(TEXT("HealtComp"));

}

void AS_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AS_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AS_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AS_BaseCharacter::StartJumping()
{
	ACharacter::Jump();
}

void AS_BaseCharacter::StopJumping()
{
	ACharacter::StopJumping();
}

void AS_BaseCharacter::StartSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed = 700.f;
}

void AS_BaseCharacter::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed = 450.f;
}

