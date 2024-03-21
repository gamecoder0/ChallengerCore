// Fill out your copyright notice in the Description page of Project Settings.


#include "Editor/ChallengerReimpotAnimations.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "EditorReimportHandler.h"
#include "UObject/UnrealType.h"

void UChallengerReimpotAnimations::ReimportAnimation()
{
    for (FChallengerAnimReimport& AnimReimport : AnimationsData)
    {
        if (AnimReimport.AnimationData)
        {
            FReimportManager::Instance()->UpdateReimportPath(
                AnimReimport.AnimationData,
                AnimReimport.PathReimportWithKey + ".FBX",
                INDEX_NONE);

            if (FReimportManager::Instance()->Reimport(AnimReimport.AnimationData, false, true, FString(), nullptr, INDEX_NONE, false))
            {
                //UE_LOG(LogTemp, Warning, TEXT("Reimport successful for %s"), *AnimReimport.NameWithKey);
            }
            else
            {
                //UE_LOG(LogTemp, Warning, TEXT("Failed to reimport for %s"), *AnimReimport.NameWithKey);
            }
        }
    }
}

void UChallengerReimpotAnimations::UpdateListAnimation()
{
    AddAnimationsData();
}

void UChallengerReimpotAnimations::UpdateFindPath()
{
    if (AnimationToFindPath)
    {
        FString AnimationPath = FPaths::GetPath(AnimationToFindPath->GetPathName());
        PathOfTheAnimations = AnimationPath + "/";
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AnimationToFindPath is null. Unable to update PathOfTheAnimations."));
    }
}

void UChallengerReimpotAnimations::AddAnimationsData()
{
    FString assetPath = PathOfTheAnimations;
    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    FARFilter AssetFilter;
    AssetFilter.PackagePaths.Add(*assetPath);
    TArray<FAssetData> AssetData;
    AssetRegistryModule.Get().GetAssets(AssetFilter, AssetData);

    TSet<FString> UniqueAssetNames;

    for (const FAssetData& Asset : AssetData)
    {
        FString AssetName = FPaths::GetCleanFilename(Asset.PackageName.ToString());
        AssetName.RemoveFromEnd(FPaths::GetExtension(AssetName));
        AssetName.ReplaceInline(TEXT("."), TEXT(""));

        if (!AssetName.IsEmpty() && Asset.GetClass()->IsChildOf(UAnimSequenceBase::StaticClass()))
        {
            FString NameWithKey = KeyNameAnimation + AssetName;
            FString PathReimportWithKey = ReimportPath + NameWithKey;
            UniqueAssetNames.Add(AssetName);
            UE_LOG(LogTemp, Warning, TEXT("Asset Name: %s"), *AssetName);
            FChallengerAnimReimport AnimReimport;
            AnimReimport.AnimationData = Cast<UAnimSequenceBase>(Asset.GetAsset());
            AnimReimport.NameWithKey = NameWithKey;
            AnimReimport.PathReimportWithKey = PathReimportWithKey;
            AnimationsData.Add(AnimReimport);
        }
    }
}