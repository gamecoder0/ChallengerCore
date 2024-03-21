// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LyraCharacterMovementComponent.h"
#include "ChallengerMovementComponent.generated.h"

// Make sure to include the following section in the DefaultEngine.ini file, below [/Script/Engine.CollisionProfile]:
// This section defines the default responses for the game trace collision channels (GameTraceChannel6, GameTraceChannel7, and GameTraceChannel8)
// that are used for cover detection in the game.
//+DefaultChannelResponses = (Channel = ECC_GameTraceChannel6, DefaultResponse = ECR_Ignore, bTraceType = True, bStaticObject = False, Name = "TraceChannel_CoverLeft")
//+DefaultChannelResponses = (Channel = ECC_GameTraceChannel7, DefaultResponse = ECR_Ignore, bTraceType = True, bStaticObject = False, Name = "TraceChannel_CoverRight")
//+DefaultChannelResponses = (Channel = ECC_GameTraceChannel8, DefaultResponse = ECR_Ignore, bTraceType = True, bStaticObject = False, Name = "TraceChannel_CoverCollision")

#define TraceChannel_CoverLeft					ECC_GameTraceChannel6
#define TraceChannel_CoverRight					ECC_GameTraceChannel7
#define TraceChannel_CoverCollision				ECC_GameTraceChannel8

UENUM(BlueprintType)
enum class FLyraLocomotionsTypes : uint8
{
	Default,
	ForwardSpin,
	BackwardSidestep,
	BackwardSidestepReverse,
	BackwardSidestepCoverLeft,
	BackwardSidestepCoverRight
};

UENUM(BlueprintType)
enum class FLyraCardinalDirection : uint8
{
	Default,
	Forward,
	Backward,
	Left,
	Right
};

USTRUCT(BlueprintType)
struct FLyraLocomotionsTypesPayload
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
		FLyraLocomotionsTypes LyraLocomotionsTypes;
	UPROPERTY(BlueprintReadWrite)
		FLyraCardinalDirection LyraCoverType;
};

UCLASS(Config = Game)
class CHALLENGERCORERUNTIME_API UChallengerMovementComponent : public ULyraCharacterMovementComponent
{
	GENERATED_BODY()

public:

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void PerformLineTrace(FHitResult& HitResult);
	UFUNCTION(BlueprintPure)
	FLyraCardinalDirection GetInputCardinalDirection();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "LocomotionType")
	FLyraLocomotionsTypes LocomotionType;

	UPROPERTY(BlueprintReadOnly, category = "CoverDetected")
	bool bCoverSphereTrace;
	UPROPERTY(BlueprintReadOnly, category = "CoverDetected")
	bool bCoverSphereTraceDebug;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "CoverDetected")
	float CoverSphereRadius = 40.0f;
	UPROPERTY(BlueprintReadOnly, category = "CoverDetected")
	FLyraCardinalDirection CoverType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoverDetected")
	TEnumAsByte<ECollisionChannel> CoverCollisionChannel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoverDetected")
	TEnumAsByte<ECollisionChannel> CoverLeftCollisionChannel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CoverDetected")
	TEnumAsByte<ECollisionChannel> CoverRightCollisionChannel;
	
};