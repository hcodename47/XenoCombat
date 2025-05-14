#include "PlayerCombatComponent.h"

#include "DrawDebugHelpers.h"

UPlayerCombatComponent::UPlayerCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	HandleAutoAttack(DeltaTime);
}

void UPlayerCombatComponent::StartAttack(AActor* Target)
{
	if(!Target)
	{
		return;
	}

	TargetActor = Target;
}

bool UPlayerCombatComponent::IsInRange() const
{
	if(!TargetActor)
	{
		return false;
	}

	AActor* Owner = GetOwner();
	FVector OwnerLocation = Owner->GetActorLocation();
	FVector TargetLocation = TargetActor->GetActorLocation();

	float Distance = FVector::Dist(OwnerLocation, TargetLocation);
	return Distance >= MinAttackRange && Distance <= MaxAttackRange;
}

void UPlayerCombatComponent::HandleAutoAttack(float DeltaTime)
{
	if(!TargetActor)
	{
		return;
	}

	bIsAutoAttacking = false;

	AutoAttackTimer += DeltaTime;

	if(IsInRange())
	{
		if (AutoAttackTimer >= GetAutoAttackRate())
		{
			if(bEnableDebugging)
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Auto Attack"));

			OnAutoAttack.Broadcast(GetOwner(), TargetActor);
			AutoAttackTimer = 0.0f;
			bIsAutoAttacking = true;
		}

		bOutOfRange = false;
	}
	else
	{
		if(bEnableDebugging && !bOutOfRange)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Out of Range"));

		AutoAttackTimer = 0.0f;
		bOutOfRange = true;
	}	

	if (bEnableDebugging)
	{
		FVector TargetLocation = TargetActor->GetActorLocation() + FVector(0, 0, 50);

		DrawDebugSphere(GetWorld(), TargetLocation, MaxAttackRange, 12, FColor::Green, false, 0.1f);
		DrawDebugSphere(GetWorld(), TargetLocation, MinAttackRange, 12, FColor::Red, false, 0.1f);
	}
}
