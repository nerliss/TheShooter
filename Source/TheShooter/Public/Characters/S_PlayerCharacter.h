// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/S_BaseCharacter.h"
#include "S_PlayerCharacter.generated.h"

class UCameraComponent;
class USkeletalMeshComponent;
class AS_BaseWeapon;

/** Test delegate signatures */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnActorKilled, AActor*, VictimActor, AActor*, KillerActor, AController*, KillerController);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFireStartDelegate);
DECLARE_DYNAMIC_DELEGATE_RetVal(bool, FAllowFireDelegate);

/**
* Character armed status:
* @param Disarmed - player is not carrying any weapon in hands right now
* @param Melee - player is carrying a knife or something melee right now
* @param Primary Weapon - player is carrying a rifle or something similar right now
* @param Secondary Weapon - player is carrying a pistol or something similar right now
* @param Special - player is carrying a bomb or something similar right now
*/
UENUM(Blueprintable)
enum ECharacterArmedStatus
{
	EArmedStatus_Disarmed			UMETA(DisplayName = "Disarmed"),
	EArmedStatus_Melee				UMETA(DisplayName = "Melee"),
	EArmedStatus_PrimaryWeapon		UMETA(DisplayName = "Primary Weapon"),
	EArmedStatus_SecondaryWeapon	UMETA(DisplayName = "Secondary Weapon"),
	EArmedStatus_Special			UMETA(DisplayName = "Special")
};

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

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
	AActor* InteractActor;

	/** Should be changed every time a player changes active weapon */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	TEnumAsByte<ECharacterArmedStatus> ArmedStatus;

	/** Current weapon that player is holding */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	AS_BaseWeapon* WeaponReference;

	/** Gamepad turn rate */
	float BaseTurnRate;

	UPROPERTY(Replicated, VisibleDefaultsOnly, BlueprintReadOnly, Category = "Linetrace")
	FVector LinetraceStartLocation;

	UPROPERTY(Replicated, VisibleDefaultsOnly, BlueprintReadOnly, Category = "Linetrace")
	FVector LinetraceEndLocation;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void InteractionLinetrace(float InLength, bool bDrawDebugLine, AActor*& OutActor);

	UFUNCTION(Server, Reliable)
	void ServerInteractionLinetrace(float InLength, bool bDrawDebugLine);

	/** Is required for proper interaction linetrace 
	* (allows clients to actually return an object they are looking at, rather than an object in front of their eyes) 
	*/
	UFUNCTION()
	void UpdateCameraRotation(FRotator NewRotation);

	UFUNCTION(NetMulticast, Unreliable, BlueprintCallable, Category = "Camera")
	void NetMulticastUpdateCameraRotation(FRotator NewRotation);

	/** Test delegates */
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Delegates")
	FOnActorKilled OnActorKilled;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Delegates")
	FOnFireStartDelegate OnFireStarted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Delegates")
	FAllowFireDelegate OnFireAllowed;

protected:

	virtual void BeginPlay() override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);
	
	void Interact();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerInteract();

	void Fire();

	void Reload();

	void DropWeapon();

};
