// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/S_HealthComponent.h"

US_HealthComponent::US_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100.f;

	bIsDead = false;
}

void US_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

void US_HealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

float US_HealthComponent::GetCurrentHealth()
{
	return CurrentHealth;
}

float US_HealthComponent::GetMaxHealth()
{
	return MaxHealth;
}

