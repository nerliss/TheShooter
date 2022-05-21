// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Print string on screen macro
#define DEBUGMESSAGE(x, y, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, x, FColor::Red, FString::Printf(TEXT(y), __VA_ARGS__));}

/**
 * Contains differet useful macros, etc.
 */
class THESHOOTER_API Utility
{
public:
	Utility();
	~Utility();
};
