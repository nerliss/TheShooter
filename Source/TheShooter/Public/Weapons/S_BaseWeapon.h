// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/S_InteractInterface.h"
#include "S_BaseWeapon.generated.h"

class USkeletalMeshComponent;
class AS_PlayerCharacter;
class UParticleSystem;
class USoundBase;

UCLASS()
class THESHOOTER_API AS_BaseWeapon : public AActor, public IS_InteractInterface
{
	GENERATED_BODY()
	
public:	

	AS_BaseWeapon();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponMesh")
	USkeletalMeshComponent* WeaponSkeletalMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UParticleSystem* ShotVFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	USoundBase* ShotSFX;

	/** Reference to a player character. Should be set upon picking up a weapon once this project is configured for multiplayer */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PlayerReference")
	AS_PlayerCharacter* PlayerRef;

	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation(AActor* InteractActor) override;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void Fire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void Reload();

	/** 
	* Drops current weapon on the ground
	* @param - bDeleteWeaponReference Use only when a weapon needs to be thrown away and not replaced by an another
	*/
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void DropWeapon(bool bDeleteWeaponReference);

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon")
	void OnWeaponPickedUp();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	bool bCanBeDropped;
};
