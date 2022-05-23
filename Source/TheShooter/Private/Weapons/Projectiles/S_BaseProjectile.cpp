// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Projectiles/S_BaseProjectile.h"

// Sets default values
AS_BaseProjectile::AS_BaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetReplicates(true);

}

// Called when the game starts or when spawned
void AS_BaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AS_BaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

