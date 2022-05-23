// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/S_InteractInterface.h"
#include "S_BaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class THESHOOTER_API AS_BaseWeapon : public AActor, public IS_InteractInterface
{
	GENERATED_BODY()
	
public:	

	AS_BaseWeapon();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponMesh")
	USkeletalMeshComponent* WeaponSkeletalMesh;

	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation(AActor* InteractActor) override;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void Fire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void Reload();

protected:

	virtual void BeginPlay() override;

};
