// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Assets/ChallengerDataInstancedMesh.h"
#include "Templates/SharedPointer.h"
#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ChallengerBoxDeviceAssets.generated.h"

UENUM(BlueprintType)
enum class EBoxComponentsTags : uint8
{
	Default UMETA(DisplayName = "Default"),
	BoxSelected UMETA(DisplayName = "BoxSelected"),
	NorthSelected UMETA(DisplayName = "NorthSelected"),
	SouthSelected UMETA(DisplayName = "SouthSelected"),
	EastSelected UMETA(DisplayName = "EastSelected"),
	WestSelected UMETA(DisplayName = "WestSelected"),
	CenterSelected UMETA(DisplayName = "CenterSelected"),
	DownComponent UMETA(DisplayName = "DownComponent"),
	DownNorthComponent UMETA(DisplayName = "DownNorthComponent"),
	DownEastComponent UMETA(DisplayName = "DownEastComponent"),
	DownSouthComponent UMETA(DisplayName = "DownSouthComponent"),
	DownWestComponent UMETA(DisplayName = "DownWestComponent"),
	DownNorthLeftComponent UMETA(DisplayName = "DownNorthLeftComponent"),
	DownEastLeftComponent UMETA(DisplayName = "DownEastLeftComponent"),
	DownSouthLeftComponent UMETA(DisplayName = "DownSouthLeftComponent"),
	DownWestLeftComponent UMETA(DisplayName = "DownWestLeftComponent"),
	DownNorthRightComponent UMETA(DisplayName = "DownNorthRightComponent"),
	DownEastRightComponent UMETA(DisplayName = "DownEastRightComponent"),
	DownSouthRightComponent UMETA(DisplayName = "DownSouthRightComponent"),
	DownWestRightComponent UMETA(DisplayName = "DownWestRightComponent"),
	TopComponent UMETA(DisplayName = "TopComponent"),
	TopNorthComponent UMETA(DisplayName = "TopNorthComponent"),
	TopEastComponent UMETA(DisplayName = "TopEastComponent"),
	TopSouthComponent UMETA(DisplayName = "TopSouthComponent"),
	TopWestComponent UMETA(DisplayName = "TopWestComponent"),
	TopNorthLeftComponent UMETA(DisplayName = "TopNorthLeftComponent"),
	TopEastLeftComponent UMETA(DisplayName = "TopEastLeftComponent"),
	TopSouthLeftComponent UMETA(DisplayName = "TopSouthLeftComponent"),
	TopWestLeftComponent UMETA(DisplayName = "TopWestLeftComponent"),
	TopNorthRightComponent UMETA(DisplayName = "TopNorthRightComponent"),
	TopEastRightComponent UMETA(DisplayName = "TopEastRightComponent"),
	TopSouthRightComponent UMETA(DisplayName = "TopSouthRightComponent"),
	TopWestRightComponent UMETA(DisplayName = "TopWestRightComponent"),
};

USTRUCT(BlueprintType)
struct FBoxAssetsAdjustments
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector Location;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator Rotation;
};

USTRUCT(BlueprintType)
struct FBoxDeviceAssetsData
{

	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FName AssetName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FBuildingComponentsNames BuildingComponentName;
	/** Boolean variable to determine whether we will use a pure UStaticMesh or an AActor in the level. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bUseAActor;
	/** TSubclassOf<AActor> that will be visible and editable only if bUseAActor is true. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bUseAActor"))
	TSubclassOf<AActor> TypeActor;
	/** UStaticMesh that will be visible and editable only if bUseAActor is false. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "!bUseAActor"))
	UStaticMesh* TypeMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture* TextureThumbnail;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterialInstance* MaterialToViewer;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterialInstance* MaterialToViewerEnd;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FBoxAssetsAdjustments> TransformAdjustments;
};

USTRUCT(BlueprintType)
struct FBoxDeviceComponentData
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FName BoxComponentTag;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FBoxPositions Positions;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FAssetCardinalDirections CardinalDirection;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FTransform BaseTransform;
	/**
	 * When this variable is marked as true, the data contained in the Assets array will be equalized between the structures that have the same option marked.
	 *
	 * For example, if the structures are named DownNorthComponent, DownEastComponent, DownSouthComponent, DownWestComponent, and all of them have the variable bool GenDataToCardinals marked as true,
	 * then the values will be equalized for the names that contain "NORTH" in the name, within the Assets array. This means that the values of South, East, and West will also be equalized with the values of North.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool GenDataToCardinal;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName> Assets;
};


USTRUCT(BlueprintType)
struct FBoxDeviceAssetsDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AssetParameters")
	TMap<FName, FBoxDeviceAssetsData> ParametersDeviceAssets;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AssetParameters")
	TMap<EBoxComponentsTags, FBoxDeviceComponentData> MapComponentData;
};

UCLASS()
class CHALLENGERCORERUNTIME_API UChallengerBoxDeviceAssets : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:

	UChallengerBoxDeviceAssets();
	virtual void PostLoad();

public:

	/**
	 * BaseLength is an FVector that defines the height, width, and length of the Box.
	 * Each layer can receive a different configuration for Box dimensions,
	 * and the assets of each layer may have different dimensions.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AssetParameters")
	FVector BaseLength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AssetParameters")
	TMap<FName, FBoxDeviceAssetsData> ParametersDeviceAssets;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AssetParameters")
	TMap<EBoxComponentsTags, FBoxDeviceComponentData> MapComponentData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataTable")
	UDataTable* BoxDeviceAssetsDataTable;
	/**
	* The ReadDataTable(); and WriteDataTable(); functions only work if the bButtonsEnable variable is set to true. 
	* Make sure to enable this variable to use these functions successfully.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataTable")
	bool bButtonsEnable;

public:

	UFUNCTION(CallInEditor, Category = "AssetParameters")
	void UpdateAssets();
	/**
	* The WriteDataTable() button is a powerful and sometimes dangerous tool.
	* Its function is to write the data defined in the DataAsset derived from UChallengerBoxDeviceAssets to the DataTable file.
	* However, its use requires extreme caution, especially if the maps are empty, as it can result in the complete replacement of existing data in the DataTable, leading to the terrible loss of information.
	* It is strongly recommended to make a detailed and complete backup of the data before daring to execute this function, to avoid possible disruptions.
	* The ReadDataTable(); and WriteDataTable(); functions only work if the bButtonsEnable variable is set to true. 
	* Make sure to enable this variable to use these functions successfully.
	*/
	UFUNCTION(CallInEditor, Category = "DataTable", meta = (EditCondition = "bButtonsEnable"))
	void WriteDataTable();
	/**
	* The ReadDataTable() button is designed to read data from the DataTable and write it to the DataAsset derived from UChallengerBoxDeviceAssets.
	* It's important to note that if the DataTable is empty, executing this function can lead to the clearing of current data in the DataAsset, resulting in significant data loss.
	* Therefore, caution is advised when using this button, and it's recommended to always make a backup before usage, ensuring that the DataTable contains the necessary data before executing the function to prevent unwanted losses."
	* The ReadDataTable(); and WriteDataTable(); functions only work if the bButtonsEnable variable is set to true. 
	* Make sure to enable this variable to use these functions successfully.
	*/
	UFUNCTION(CallInEditor, Category = "DataTable", meta = (EditCondition = "bButtonsEnable"))
	void ReadDataTable();

	static FTransform GenerateTransforElement(FAssetCardinalDirections Direction, FTransform BaseTransform, FBoxAssetsAdjustments TransformAdjustments, FVector BaseLength);
	static TArray<EBoxComponentsTags> GetComponentsTagsByDirection(FAssetCardinalDirections Direction);

private:

	void UpdateAssetName();
	void UpdateComponentData(EBoxComponentsTags ComponentEnum);
	void UpdateComponentsData();
	TArray<FName> GetNameAsstes(EBoxComponentsTags ComponentEnum);
	void UpdateTransformAdjustments();
};