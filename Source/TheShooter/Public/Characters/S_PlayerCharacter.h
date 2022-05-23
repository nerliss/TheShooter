// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/S_BaseCharacter.h"
#include "S_PlayerCharacter.generated.h"

class UCameraComponent;
class USkeletalMeshComponent;
class AS_BaseWeapon;

UCLASS()
class THESHOOTER_API AS_PlayerCharacter : public AS_BaseCharacter
{
	GENERATED_BODY()
	
public:

	AS_PlayerCharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPMesh")
	USkeletalMeshComponent* FirstPersonMeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
	AActor* InteractActor;

	/** Current weapon that player is holding */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	AS_BaseWeapon* WeaponReference;

	/** Gamepad turn rate */
	float BaseTurnRate;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void InteractionLinetrace(float InLength, bool bDrawDebugLine, AActor*& OutActor);

protected:

	virtual void BeginPlay() override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);
	
	void Interact();

	void Fire();

	void Reload();

};
