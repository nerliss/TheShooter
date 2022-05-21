// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "S_MainHUD.generated.h"

/**
 * A HUD class that is usually used in game 
 */
UCLASS()
class THESHOOTER_API AS_MainHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crosshair")
	bool bShowCrosshair = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crosshair")
	UTexture* CrosshairTexture;

	UFUNCTION(BlueprintCallable, Category = "Crosshair")
	void DrawCrosshair(float ScreenWidth, float ScreenHeight);

};
