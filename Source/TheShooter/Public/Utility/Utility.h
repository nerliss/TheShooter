// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
* Print debug message to screen
* @param x - message visibility duration
* @param y - message text color
* @param z - message text itself
*/
#define DEBUGMESSAGE(x, y, z,...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, x, y, FString::Printf(TEXT(z), __VA_ARGS__));}

/**
 * Contains different useful macros, etc.
 */
class THESHOOTER_API Utility
{
public:
	Utility();
	~Utility();
};
