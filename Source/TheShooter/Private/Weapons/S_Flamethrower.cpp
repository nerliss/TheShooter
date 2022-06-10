// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/S_Flamethrower.h"
#include "Utility/Utility.h"

AS_Flamethrower::AS_Flamethrower()
{
	PrimaryActorTick.bCanEverTick = false;
	SetReplicates(true);


}

void AS_Flamethrower::StartFiring()
{
	DEBUGMESSAGE(3.f, FColor::Green, "Yo shit's on fire!");
	return;
}

void AS_Flamethrower::StopFiring()
{
	DEBUGMESSAGE(3.f, FColor::Green, "No more fire :(");
	return;
}