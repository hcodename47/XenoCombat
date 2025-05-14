// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerCombatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
  FOnAutoAttack, // Name of the structure that will be generated
  // Parameters of the delegate (Type, Name):
  AActor*, Instigator,
  AActor*, Target
);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class XENOCOMBAT_API UPlayerCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerCombatComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable, Category = "Combat")
	float GetAutoAttackRate() const { return AutoAttackRate; };

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetAutoAttackRate(float NewAttackRate) { AutoAttackRate = NewAttackRate; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void StartAttack(AActor* Target);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool IsInRange() const;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool IsAutoAttacking() const { return bIsAutoAttacking; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
	AActor* GetTargetActor() const { return TargetActor; }

	UPROPERTY(BlueprintAssignable)
  	FOnAutoAttack OnAutoAttack;

private:
	void HandleAutoAttack(float DeltaTime);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float MinAttackRange = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float MaxAttackRange = 1000.0f;

	AActor* TargetActor = nullptr;
	float AutoAttackTimer = 0.0f;
	float AutoAttackRate = 1.0f;

	bool bOutOfRange = false;

	bool bIsAutoAttacking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bEnableDebugging = false;
};
