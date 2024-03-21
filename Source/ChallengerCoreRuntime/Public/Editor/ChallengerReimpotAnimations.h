// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/ChallengerDataAnim.h"
#include "Animation/AnimSequence.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ChallengerReimpotAnimations.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FChallengerAnimReimport
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimSequenceBase* AnimationData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString NameWithKey;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString PathReimportWithKey;
};


UCLASS()
class CHALLENGERCORERUNTIME_API UChallengerReimpotAnimations : public UDataAsset
{
	GENERATED_BODY()

public:

	UFUNCTION(CallInEditor, Category = "ReimportAnimaitons3stStep")
	void ReimportAnimation();
	UFUNCTION(CallInEditor, Category = "ReimportAnimaitons2stStep")
	void UpdateListAnimation();
	UFUNCTION(CallInEditor, Category = "ReimportAnimaitons1stStep")
	void UpdateFindPath();

public:

	/**
	 * Variable AnimationToFindPath:
	 * This variable is exclusively used in the Editor to locate the folder where animations are stored.
	 * Its sole purpose is to serve as a guide for generating the animation list. By configuring this variable,
	 * the creation of the Data Asset in a different directory is allowed, facilitating the editing of
	 * the properties of this animation file.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ReimportAnimaitons1stStep|FindAnimations")
	UAnimSequenceBase* AnimationToFindPath;
	/**
	* Variable PathOfTheAnimations:
	* This variable stores the complete path to the folder where animations are located. Configured exclusively
	* for the Editor, it serves as a guide to search for other animations and generate the desired list.
	* Ensure that the path is correct and up-to-date to ensure an effective search for animations in your project.
	*
	* Example of use:
	* FString PathOfTheAnimations = "C:\\Documents\\Game\\Characters\\Heroes\\Mannequin\\Animations\\Locomotion\\Unarmed\\";
	*
	* Additional note:
	* This path is automatically filled in as soon as the UpdateFindPath function is executed.
	* The UpdateFindPath function is responsible for dynamically updating the path, ensuring that
	* it is always aligned with the actual location of animations. This provides a more efficient
	* experience and avoids the need for constant manual adjustments by the developer.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ReimportAnimaitons1stStep|FindAnimations")
	FString PathOfTheAnimations = "D:\\Documents\\UE_5.3\\UnrealAnimarions\\UnarmedOriginal\\Left\\";


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ReimportAnimaitons2stStep|ReimportSettings")
	FString KeyNameAnimation = "BSCL_";
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ReimportAnimaitons2stStep|ReimportSettings")
	FString ReimportPath = "D:\\Documents\\UE_5.3\\UnrealAnimarions\\UnarmedOriginal\\Left\\";
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ReimportAnimaitons2stStep|AnimationDataList")
	TArray<FChallengerAnimReimport> AnimationsData;

protected:

	void AddAnimationsData();
};
