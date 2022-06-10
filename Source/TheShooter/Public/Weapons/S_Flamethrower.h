// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/S_BaseWeapon.h"
#include "S_Flamethrower.generated.h"

/**
 * 
 */
UCLASS()
class THESHOOTER_API AS_Flamethrower : public AS_BaseWeapon
{
	GENERATED_BODY()
	
public:

	AS_Flamethrower();

	virtual void StartFiring() override;

	virtual void StopFiring() override;

};
