// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/S_BaseWeapon.h"
#include "Utility/Utility.h"
#include "Components/SkeletalMeshComponent.h"

AS_BaseWeapon::AS_BaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

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
	DEBUGMESSAGE(4.f, "Base weapon fire function called");
}

void AS_BaseWeapon::Interact_Implementation(AActor* InteractActor)
{
	DEBUGMESSAGE(3.f, "Interaction successful");
}
