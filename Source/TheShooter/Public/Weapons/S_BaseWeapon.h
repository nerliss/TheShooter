// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/S_InteractInterface.h"
#include "S_BaseWeapon.generated.h"

UCLASS()
class THESHOOTER_API AS_BaseWeapon : public AActor, public IS_InteractInterface
{
	GENERATED_BODY()
	
public:	

	AS_BaseWeapon();

	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation(AActor* InteractActor) override;

protected:

	virtual void BeginPlay() override;

};
