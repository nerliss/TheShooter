// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/S_BaseWeapon.h"

AS_BaseWeapon::AS_BaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AS_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AS_BaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

