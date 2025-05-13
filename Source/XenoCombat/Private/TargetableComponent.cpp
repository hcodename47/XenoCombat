// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetableComponent.h"

UTargetableComponent::UTargetableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTargetableComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTargetableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

