// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/S_GenericGun.h"
#include "Utility/Utility.h"
#include "Weapons/Projectiles/S_BaseProjectile.h"
#include "Characters/S_PlayerCharacter.h"
#include "Camera/CameraComponent.h"

AS_GenericGun::AS_GenericGun()
{
	PrimaryActorTick.bCanEverTick = false;
	SetReplicates(true);
}

void AS_GenericGun::Fire()
{
	Super::Fire();

	AS_PlayerCharacter* MyOwner = Cast<AS_PlayerCharacter>(GetAttachParentActor());

	if (MyOwner && ProjectileClass)
	{
		FRotator SpawnRotation = MyOwner->CameraComp->GetComponentRotation();

		FVector MuzzleLocation = WeaponSkeletalMesh->GetSocketLocation("MuzzleSocket");

		FActorSpawnParameters ASP;
		ASP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, SpawnRotation, ASP);
	}
	else
	{
		DEBUGMESSAGE(3.f, FColor::Red, "Projectile NOT spawned");
	}
}
