// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/S_BaseWeapon.h"
#include "Utility/Utility.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GamePlayStatics.h"
#include "Characters/S_PlayerCharacter.h"
#include "PlayerControllers/S_PlayerControllerMain.h"
#include "Net/UnrealNetwork.h"

AS_BaseWeapon::AS_BaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	SetReplicates(true);

	WeaponSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponSkeletalMeshComp"));
	WeaponSkeletalMesh->SetupAttachment(GetRootComponent());
	WeaponSkeletalMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	WeaponSkeletalMesh->SetCollisionProfileName("BlockAll");

	MaxAmmo = 60;
	ClipAmmo = 20;

	bCanBeDropped = true;
}

void AS_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = ClipAmmo;

	// Set player reference
	PlayerRef = Cast<AS_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)); // TODO: Adapt for multiplayer
}

void AS_BaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AS_BaseWeapon::Fire()
{
	// Spawn effects at muzzle location
	if (ShotSFX)
	{
		UGameplayStatics::SpawnSoundAttached(ShotSFX, WeaponSkeletalMesh, "MuzzleSocket");
	}

	if (ShotVFX)
	{
		UGameplayStatics::SpawnEmitterAttached(ShotVFX, WeaponSkeletalMesh, "MuzzleSocket");
	}
}

void AS_BaseWeapon::ServerFire_Implementation()
{
	Fire();
}

bool AS_BaseWeapon::ServerFire_Validate()
{
	return true;
}

void AS_BaseWeapon::Reload()
{
	DEBUGMESSAGE(3.f, FColor::Yellow, "Base weapon reload");
}

void AS_BaseWeapon::DropWeapon(bool bDeleteWeaponReference)
{
	// Check if this weapon is actually attached to some other actor and can be dropped
	if (this->GetAttachParentActor() && bCanBeDropped)
	{
		// Detach the weapon and enable its collision
		FDetachmentTransformRules DetachParams(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, true);
		DetachFromActor(DetachParams);
		WeaponSkeletalMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		// Clear reference in player class if chosen
		if (bDeleteWeaponReference)
		{
			PlayerRef->WeaponReference = nullptr;
			PlayerRef->ArmedStatus = EArmedStatus_Disarmed;
		}
	}
}

void AS_BaseWeapon::Interact_Implementation(AActor* Interactor)
{
	// Set reference to a player that interacted with
	PlayerRef = Cast<AS_PlayerCharacter>(Interactor);

	if (PlayerRef)
	{
		AS_BaseWeapon* PlayerWeaponRef = PlayerRef->WeaponReference;
		 
		// Attachment parameters for weapon
		FAttachmentTransformRules AttachParams(EAttachmentRule::SnapToTarget,
											   EAttachmentRule::SnapToTarget,
											   EAttachmentRule::SnapToTarget, true);

		// If player doesn't have any weapon - they take it from the ground
		if (!PlayerWeaponRef)
		{
			// Set reference to this weapon in player's class
			PlayerRef->WeaponReference = this;
			PlayerRef->ArmedStatus = EArmedStatus_PrimaryWeapon;

			// Attach this weapon to FirstPersonArms
			AttachToComponent(PlayerRef->FirstPersonMeshComp, AttachParams, "GripSocket");

			// Disable collision for this weapon
			WeaponSkeletalMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			// Call BP event
			OnWeaponPickedUp();
		}
		// If player already has a weapon in they hands - swap it with the one they are looking at
		else 
		{
			// This will only work if we already have a weapon and are looking at another weapon
			AActor* NewWeapon = PlayerRef->InteractActor;

			// If new weapon is not of the same class - swap it
			if (NewWeapon && (NewWeapon->GetClass() != PlayerWeaponRef->GetClass()))
			{
				// Drop current weapon
				PlayerWeaponRef->DropWeapon(false); // I don't know why the hell must I call it this way and not just straightly via DropWeapon()
				
				// Get transform data from the weapon we are looking at, but leave scale the same
				FVector NewWeaponLocation = NewWeapon->GetActorLocation();
				FRotator NewWeaponRotation = NewWeapon->GetActorRotation();
				FVector OldWeaponScale = PlayerWeaponRef->GetActorScale();
				FTransform NewWeaponTransform(NewWeaponRotation, NewWeaponLocation, OldWeaponScale);

				// Move dropped weapon to NewWeapon's place
				PlayerWeaponRef->SetActorTransform(NewWeaponTransform);

				// Enable collision for it
				PlayerWeaponRef->WeaponSkeletalMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

				// Change weapon reference in player class
				PlayerRef->WeaponReference = Cast<AS_BaseWeapon>(NewWeapon);
				// Should be overriden in other weapon classes that are not of Primary Weapon type
				PlayerRef->ArmedStatus = EArmedStatus_PrimaryWeapon;

				// Attach new weapon to FirstPersonArms
				NewWeapon->AttachToComponent(PlayerRef->FirstPersonMeshComp, AttachParams, "GripSocket");

				// Since we reassign player's weapon reference we also need to rewrite player reference itself
				// and then set weapon's collision to disabled
				PlayerRef = Cast<AS_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
				PlayerRef->WeaponReference->WeaponSkeletalMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

				// Call BP event
				OnWeaponPickedUp();
			}
			else
			{
				// TODO: Get ammo from weapon of the same class
				DEBUGMESSAGE(3.f, FColor::Red, "You already have this weapon");
			}
		}
	}
}
