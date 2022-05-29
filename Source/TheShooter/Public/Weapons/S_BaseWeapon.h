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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon|Ammo")
	int32 CurrentAmmo;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon|Ammo")
	int32 MaxAmmo;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon|Ammo")
	int32 ClipAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Mesh")
	USkeletalMeshComponent* WeaponSkeletalMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Effects")
	UParticleSystem* ShotVFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Effects")
	USoundBase* ShotSFX;

	/** Reference to a player character. Should be set upon picking up a weapon once this project is configured for multiplayer */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon|PlayerReference")
	AS_PlayerCharacter* PlayerRef;

	virtual void Tick(float DeltaTime) override;

	/** Interface function implementation */
	void Interact_Implementation(AActor* Interactor) override;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void Fire();

	UFUNCTION(Server, Reliable, WithValidation, Category = "Weapon|Server")
	virtual void ServerFire();

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
