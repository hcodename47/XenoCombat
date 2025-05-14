// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "EnemyAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class XENOCOMBAT_API UEnemyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

	UPROPERTY()
	FGameplayAttributeData Health = 100.0f;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, Health)
	
	UPROPERTY()
	FGameplayAttributeData MaxHealth = 100.0f;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, MaxHealth)
};
