// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/S_MainHUD.h"

void AS_MainHUD::DrawCrosshair(float ScreenWidth, float ScreenHeight)
{
	if (bShowCrosshair && CrosshairTexture)
	{
		DrawTexture(CrosshairTexture, ScreenWidth / 2.f, ScreenHeight / 2.f, 16.f, 16.f, 0.f, 0.f, 1.f, 1.f, FLinearColor::White);
	}
}
