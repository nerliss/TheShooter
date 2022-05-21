// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/S_GenericGun.h"
#include "Utility/Utility.h"

AS_GenericGun::AS_GenericGun()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AS_GenericGun::Fire()
{
	DEBUGMESSAGE(4.f, "Generic weapon fire function called");
}
