// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "S_BaseCharacter.generated.h"

class US_HealthComponent;

UCLASS()
class THESHOOTER_API AS_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AS_BaseCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void StartJumping();

	void StopJumping();

	void StartSprinting();

	void StopSprinting();

	void StartCrouching();

	void StopCrouching();

protected:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Health")
	US_HealthComponent* HealthComp;

	virtual void BeginPlay() override;

};
