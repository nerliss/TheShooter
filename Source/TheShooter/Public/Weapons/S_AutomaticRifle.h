// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/S_BaseWeapon.h"
#include "S_AutomaticRifle.generated.h"

/**
 * 
 */
UCLASS()
class THESHOOTER_API AS_AutomaticRifle : public AS_BaseWeapon
{
	GENERATED_BODY()
	
public:

	AS_AutomaticRifle();

	virtual void Fire() override;
};
