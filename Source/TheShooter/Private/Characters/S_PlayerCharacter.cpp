// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/S_PlayerCharacter.h"
#include "Interfaces/S_InteractInterface.h"
#include "DrawDebugHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"

AS_PlayerCharacter::AS_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set up camera component
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(GetRootComponent());
	CameraComp->bUsePawnControlRotation = true;

	// Set up First Person Mesh component
	FirstPersonMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPMeshComp"));
	FirstPersonMeshComp->SetupAttachment(CameraComp);
	FirstPersonMeshComp->CanCharacterStepUpOn = ECB_Yes;
	FirstPersonMeshComp->SetCollisionProfileName("CharacterMesh");
	FirstPersonMeshComp->CastShadow = false;
	FirstPersonMeshComp->bOnlyOwnerSee = true;

}

void AS_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AS_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InteractionLinetrace(600.f, false, InteractActor);
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
		PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AS_BaseCharacter::StartCrouching);
		PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AS_BaseCharacter::StopCrouching);
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

void AS_PlayerCharacter::InteractionLinetrace(float InLength, bool bDrawDebugLine, AActor*& OutActor)
{
	FVector StartLocation = CameraComp->GetComponentLocation();
	FVector EndLocation = StartLocation + (CameraComp->GetForwardVector() * InLength); 

	FHitResult HitResult;

	FCollisionQueryParams CQP;
	CQP.AddIgnoredActor(this);

	bool bHitResult = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_WorldDynamic, CQP);

	if (bHitResult)
	{
		if (bDrawDebugLine)
		{
			DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 5.f, 0, 2.f);
		}

		OutActor = HitResult.GetActor();
		InteractActor = OutActor;
	}
	else
	{
		OutActor = nullptr;
		InteractActor = nullptr;
	}
}

