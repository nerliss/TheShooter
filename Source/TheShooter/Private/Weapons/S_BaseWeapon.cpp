// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/S_BaseWeapon.h"
#include "Utility/Utility.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GamePlayStatics.h"
#include "Characters/S_PlayerCharacter.h"

AS_BaseWeapon::AS_BaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	SetReplicates(true);

	WeaponSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponSkeletalMeshComp"));
	WeaponSkeletalMesh->SetupAttachment(GetRootComponent());

}

void AS_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();

}

void AS_BaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AS_BaseWeapon::Fire()
{
	DEBUGMESSAGE(3.f, FColor::Red, "Base weapon fire function called");
}

void AS_BaseWeapon::Reload()
{
	DEBUGMESSAGE(3.f, FColor::Red, "Base weapon reload");
}

void AS_BaseWeapon::Interact_Implementation(AActor* InteractActor)
{
	AS_PlayerCharacter* PlayerRef = Cast<AS_PlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)); // TODO: Adapt for multiplayer;

	if (PlayerRef)
	{
		if (!PlayerRef->WeaponReference)
		{
			PlayerRef->WeaponReference = this;

			FAttachmentTransformRules ATR(EAttachmentRule::SnapToTarget,
										  EAttachmentRule::SnapToTarget,
										  EAttachmentRule::SnapToTarget, true);

			AttachToComponent(PlayerRef->FirstPersonMeshComp, ATR, "GripSocket");

			WeaponSkeletalMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			DEBUGMESSAGE(3.f, FColor::Green, "Weapon attachment successful");
		}
		else
		{
			DEBUGMESSAGE(3.f, FColor::Red, "Weapon attachment failed because the player has already a weapon in hands");
		}
	}

}
