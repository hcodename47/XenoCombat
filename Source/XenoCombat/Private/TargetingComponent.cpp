// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "TargetableComponent.h"

#include "DrawDebugHelpers.h"

UTargetingComponent::UTargetingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTargetingComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTargetingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UTargetingComponent::HasLineOfSightToTarget(FVector From, AActor* Target) const
{
	if (!Target)
	{
		return false;
	}

	FVector End = Target->GetActorLocation();

	FVector Direction = End - From;
	Direction.Normalize();

	End += Direction * 100.0f; // Extend the line a bit to ensure we hit the target

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	FHitResult HitResult;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, From, End, ECC_Camera, CollisionParams);

	if(bEnableDebugging)
		DrawDebugLine(GetWorld(), From, End, FColor::Red, false, 1.0f);

	if (bHit)
	{
		return HitResult.GetActor() == Target;
	}

	return false;
}

void UTargetingComponent::PickTarget()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors); //

	if (FoundActors.Num() > 0)
	{
		AActor* parent = GetOwner();
		FVector ThisForwardVector = parent->GetActorForwardVector();
		FVector CameraLocation = parent->GetActorLocation();
		if(UCameraComponent* Camera = parent->FindComponentByClass<UCameraComponent>())
		{
			ThisForwardVector = Camera->GetForwardVector();
			CameraLocation = Camera->GetComponentLocation();
		}

		FVector MyLocation = parent->GetActorLocation();

		AActor* TargetActor = nullptr;
		float ClosestDotProduct = -1.0f;

		for (AActor* Actor : FoundActors)
		{
			if(Actor == parent )
			{
				continue; // Skip self
			}

			if(UTargetableComponent* targetableComp = Actor->FindComponentByClass<UTargetableComponent>())
			{
				if(!targetableComp->IsTargetable())
				{
					continue; // Skip actors that are not targetable
				}
			}
			else
			{
				continue; // Skip actors that are not targetable or is it self
			}

			float Distance = FVector::Dist(GetOwner()->GetActorLocation(), Actor->GetActorLocation());

			if(Distance > TargetingDistance)
			{
				continue; // Skip actors that are out of range
			}

			if(!HasLineOfSightToTarget(CameraLocation, Actor))
			{
				continue; // Skip actors that are not in line of sight
			}

			FVector ActorLocation = Actor->GetActorLocation();
			FVector Direction = ActorLocation - MyLocation;
			Direction.Normalize();

			float dp = FVector::DotProduct(ThisForwardVector, Direction);

			// dot product: [-1;1] -> x < 0 = behind. 1 perfectly in front

			if(dp < 0.5f)
			{
				continue; // Skip actors that are not in front of the player
			}

			// find the actor that is most in front of us
			if (dp > ClosestDotProduct)
			{
				ClosestDotProduct = dp;
				TargetActor = Actor;
			}
		}

		if (TargetActor)
		{
			if(bEnableDebugging)
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Target acquired: ") + TargetActor->GetName());	
				
			OnTargetSelected(TargetActor);
			return;
		}
	}

	if(bEnableDebugging)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Nothing to target"));

	OnTargetSelected(nullptr);
}

void UTargetingComponent::OnTargetSelected(AActor* Target)
{
	CurrentTarget = Target;
}
