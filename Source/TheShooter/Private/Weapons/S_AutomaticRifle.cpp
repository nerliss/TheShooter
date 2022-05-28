// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/S_AutomaticRifle.h"
#include "Utility/Utility.h"

AS_AutomaticRifle::AS_AutomaticRifle()
{
	SetReplicates(true);
}

void AS_AutomaticRifle::Fire()
{
	Super::Fire();
	DEBUGMESSAGE(3.f, FColor::MakeRandomColor(), "Tra-ta-ta!");
}
