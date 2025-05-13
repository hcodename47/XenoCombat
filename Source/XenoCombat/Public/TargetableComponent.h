// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class XENOCOMBAT_API UTargetableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTargetableComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Targetable")
	bool IsTargetable() const { return bIsTargetable; }

	UFUNCTION(BlueprintCallable, Category = "Targetable")
	void SetTargetable(bool bNewTargetable) { bIsTargetable = bNewTargetable; }

protected:
	virtual void BeginPlay() override;

protected:
	bool bIsTargetable = true;
};
