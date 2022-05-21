// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/S_BaseCharacter.h"
#include "S_PlayerCharacter.generated.h"

UCLASS()
class THESHOOTER_API AS_PlayerCharacter : public AS_BaseCharacter
{
	GENERATED_BODY()
	
public:

	AS_PlayerCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	AActor* InteractActor;

protected:

	virtual void BeginPlay() override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void Interact();

};
