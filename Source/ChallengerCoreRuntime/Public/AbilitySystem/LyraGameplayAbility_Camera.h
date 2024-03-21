// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Abilities/GameplayAbility.h"
#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/LyraGameplayAbility.h"
#include "LyraGameplayAbility_Camera.generated.h"


UCLASS()
class CHALLENGERCORERUNTIME_API ULyraGameplayAbility_Camera : public ULyraGameplayAbility
{
	GENERATED_BODY()

public:

	// Sets the ability's camera mode.
	UFUNCTION(BlueprintCallable, Category = "Lyra|Ability")
	void SetCameraModeChallenger(TSubclassOf<ULyraCameraMode> CameraMode, TSubclassOf<ULyraCameraMode>& OutCameraMode);
	
};
