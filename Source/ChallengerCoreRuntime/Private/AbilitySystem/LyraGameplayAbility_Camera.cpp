// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/LyraGameplayAbility_Camera.h"
#include "Character/LyraHeroComponent.h"
#include "Camera/LyraCameraMode.h"

void ULyraGameplayAbility_Camera::SetCameraModeChallenger(TSubclassOf<ULyraCameraMode> CameraMode, TSubclassOf<ULyraCameraMode>& OutCameraMode)
{
    if (ULyraHeroComponent* HeroComponent = GetHeroComponentFromActorInfo())
    {
        // Verifica se ActiveCameraMode � diferente de CameraMode
        if (ActiveCameraMode != CameraMode)
        {
            // Define ActiveCameraMode para CameraMode
            HeroComponent->SetAbilityCameraMode(CameraMode, CurrentSpecHandle);
            ActiveCameraMode = CameraMode;

            // Retorna o valor de CameraMode por meio do par�metro de sa�da
            OutCameraMode = CameraMode;
        }
        else
        {
            // Se ActiveCameraMode j� for igual a CameraMode, n�o faz nada e retorna nullptr
            OutCameraMode = nullptr;
        }
    }
    else
    {
        // Se GetHeroComponentFromActorInfo() retornar nullptr, retorna nullptr
        OutCameraMode = nullptr;
    }
}
