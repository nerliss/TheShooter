// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/S_BaseWeapon.h"
#include "Weapons/Projectiles/S_BaseProjectile.h"
#include "S_GenericGun.generated.h"

/**
 * 
 */
UCLASS()
class THESHOOTER_API AS_GenericGun : public AS_BaseWeapon
{
	GENERATED_BODY()
	
public:

	AS_GenericGun();

	/** Set this reference in BP */
	UPROPERTY(EditAnywhere, Category = "GenericGun")
	TSubclassOf<AS_BaseProjectile> ProjectileClass;

	virtual void Fire() override;

};
