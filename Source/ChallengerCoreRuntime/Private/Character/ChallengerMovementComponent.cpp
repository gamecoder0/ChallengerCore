// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ChallengerMovementComponent.h"


void UChallengerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    FHitResult HitResult;
    PerformLineTrace(HitResult);
}

void UChallengerMovementComponent::PerformLineTrace(FHitResult& HitResult)
{
    FVector TraceDirection = GetOwner()->GetActorRotation().Vector();
    FVector CharacterLocation = GetOwner()->GetActorLocation();
    FVector StartLocation = CharacterLocation + TraceDirection;
    FCollisionQueryParams TraceParams(FName(TEXT("SphereTrace")), false, GetOwner());
    TraceParams.AddIgnoredActor(GetOwner());

    if (GetWorld()->SweepSingleByChannel(HitResult, StartLocation, StartLocation, FQuat::Identity, CoverCollisionChannel, FCollisionShape::MakeSphere(CoverSphereRadius), TraceParams))
    {
        
        bCoverSphereTrace = true;

        ECollisionResponse DefaultResponseLeft = HitResult.GetComponent()->GetCollisionResponseToChannel(CoverLeftCollisionChannel);
        ECollisionResponse DefaultResponseRight = HitResult.GetComponent()->GetCollisionResponseToChannel(CoverRightCollisionChannel);

        if (DefaultResponseLeft != ECR_Ignore)
        {
            CoverType = FLyraCardinalDirection::Left;
            if (bCoverSphereTraceDebug)
            {
                DrawDebugSphere(GetWorld(), StartLocation, CoverSphereRadius, 12, FColor::Blue, false, -1.0f);
            }
        }
        else if (DefaultResponseRight != ECR_Ignore)
        {
            CoverType = FLyraCardinalDirection::Right;
            if (bCoverSphereTraceDebug)
            {
                DrawDebugSphere(GetWorld(), StartLocation, CoverSphereRadius, 12, FColor::Emerald, false, -1.0f);
            }
        }
        else
        {
            CoverType = FLyraCardinalDirection::Default;
            if (bCoverSphereTraceDebug)
            {
                DrawDebugSphere(GetWorld(), StartLocation, CoverSphereRadius, 12, FColor::Magenta, false, -1.0f);
            }
        }
    }
    else
    {
        bCoverSphereTrace = false;
        CoverType = FLyraCardinalDirection::Default;
    }
}

FLyraCardinalDirection UChallengerMovementComponent::GetInputCardinalDirection()
{
    FVector InputVector = GetLastInputVector();
    FVector ForwardVector = GetOwner()->GetActorForwardVector();
    FVector RightVector = GetOwner()->GetActorRightVector();

    float DotForward = FVector::DotProduct(InputVector, ForwardVector);
    float DotRight = FVector::DotProduct(InputVector, RightVector);
    float Tolerance = 0.5f;

    if (DotForward > Tolerance)
    {
        return FLyraCardinalDirection::Forward;
    }
    else if (DotRight > Tolerance)
    {
        return FLyraCardinalDirection::Right;
    }
    else if (DotForward < -Tolerance)
    {
        return FLyraCardinalDirection::Backward;
    }
    else if (DotRight < -Tolerance)
    {
        return FLyraCardinalDirection::Left;
    }
    else
    {
        return FLyraCardinalDirection::Default;
    }
    return FLyraCardinalDirection::Default;
}