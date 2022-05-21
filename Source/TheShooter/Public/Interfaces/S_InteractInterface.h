// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "S_InteractInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class US_InteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * An interface for classes that are supposed to be interactable
 */
class THESHOOTER_API IS_InteractInterface
{
	GENERATED_BODY()

public:

	// Interact with an object
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void Interact(AActor* Interactor);

	// Return name of an object
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	FText GetName();

};
