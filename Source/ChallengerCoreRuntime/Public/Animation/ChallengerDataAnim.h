// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ChallengerDataAnim.generated.h"

class UAimOffsetBlendSpace;

USTRUCT(BlueprintType)
struct FLyraCardinalsDirections
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        UAnimSequence* Forward;

    // Animação para trás
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        UAnimSequence* Backward;

    // Animação para a esquerda
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        UAnimSequence* Left;

    // Animação para a direita
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        UAnimSequence* Right;
};

UCLASS()
class CHALLENGERCORERUNTIME_API UChallengerDataAnim : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Idle")
        UAnimSequence* Idle_Walk;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Idle")
        UAnimSequence* Idle_Hipfire;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Idle")
        TArray<UAnimSequence*> Idle_Breaks;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Idle")
        UAnimSequence* Crouch_Idle;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Idle")
        UAnimSequence* Crouch_Idle_Entry;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Idle")
        UAnimSequence* Crouch_Idle_Exit;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Idle")
        UAnimSequence* LeftHandPose_Override;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Idle")
        FRotator Idle_RotationLeft;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Idle")
        FRotator Idle_RotationRight;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|TurnInPlace")
        UAnimSequence* TurnInPlace_Left;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|TurnInPlace")
        UAnimSequence* TurnInPlace_Right;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|TurnInPlace")
        UAnimSequence* Crouch_TurnInPlace_Left;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|TurnInPlace")
        UAnimSequence* Crouch_TurnInPlace_Right;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Jump")
        UAnimSequence* Jump_Start;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Jump")
        UAnimSequence* Jump_Apex;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Jump")
        UAnimSequence* Jump_FallLand;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Jump")
        UAnimSequence* Jump_RecoveryAdditive;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Jump")
        UAnimSequence* Jump_StartLoop;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Jump")
        UAnimSequence* Jump_FallLoop;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Jump")
        FRotator Jump_RotationLeft;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Jump")
        FRotator Jump_RotationRight;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Aiming")
        UAnimSequence* Aim_HipFirePose;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Aiming")
        UAnimSequence* Aim_HipFirePose_Crouch;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Aiming")
        UAimOffsetBlendSpace* IdleAimOffset;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Aiming")
        UAimOffsetBlendSpace* RelaxedAimOffset;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Starts")
        FLyraCardinalsDirections Jog_Start_Cardinals;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Starts")
        FLyraCardinalsDirections Walk_Start_Cardinals;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Starts")
        FLyraCardinalsDirections Crouch_Start_Cardinals;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Starts")
        FRotator Starts_RotationLeft;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Starts")
        FRotator Starts_RotationRight;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Stops")
        FLyraCardinalsDirections Jog_Stop_Cardinals;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Stops")
        FLyraCardinalsDirections Walk_Stop_Cardinals;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Stops")
        FLyraCardinalsDirections Crouch_Stop_Cardinals;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Stops")
        FRotator Stops_RotationLeft;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Stops")
        FRotator Stops_RotationRight;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Pivots")
        FLyraCardinalsDirections Jog_Pivot_Cardinals;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Pivots")
        FLyraCardinalsDirections Walk_Pivot_Cardinals;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Pivots")
        FLyraCardinalsDirections Crouch_Pivot_Cardinals;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Pivots")
        FRotator Pivots_RotationLeft;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Pivots")
        FRotator Pivots_RotationRight;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Move")
        FLyraCardinalsDirections Jog_Cardinals;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Move")
        FLyraCardinalsDirections Walk_Cardinals;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Move")
        FLyraCardinalsDirections Crouch_Walk_Cardinals;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Move")
        FRotator Move_RotationLeft;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Lyra|AnimSet|Move")
        FRotator Move_RotationRight;
};
