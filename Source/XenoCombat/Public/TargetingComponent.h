// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetingComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class XENOCOMBAT_API UTargetingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTargetingComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Targeting")
	void PickTarget();

	UFUNCTION(BlueprintCallable, Category = "Targeting")
	AActor* GetCurrentTarget() const { return CurrentTarget; }

	UFUNCTION(BlueprintCallable, Category = "Targeting")
	void SetCurrentTarget(AActor* NewTarget) { CurrentTarget = NewTarget; }

	UFUNCTION(BlueprintCallable, Category = "Targeting")
	void ClearTarget() { CurrentTarget = nullptr; }

	UFUNCTION(BlueprintCallable, Category = "Targeting")
	void OnTargetSelected(AActor* Target);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool HasLineOfSightToTarget(FVector From, AActor* Target) const;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	float TargetingDistance = 1000.0f;

protected:
	AActor* CurrentTarget = nullptr;
};
