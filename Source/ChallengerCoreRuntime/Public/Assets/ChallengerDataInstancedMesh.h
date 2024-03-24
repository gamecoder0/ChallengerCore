// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ChallengerDataInstancedMesh.generated.h"

class AChallengerBoxAsset;

UENUM(BlueprintType)
enum class FBoxPositions : uint8
{
	Default,
	Down,
	DownNorth,
	DownNorthLeft,
	DownNorthRight,
	DownEast,
	DownEastLeft,
	DownEastRight,
	DownSouth,
	DownSouthLeft,
	DownSouthRight,
	DownWest,
	DownWestLeft,
	DownWestRight,
	Top,
	TopNorth,
	TopNorthLeft,
	TopNorthRight,
	TopEast,
	TopEastLeft,
	TopEastRight,
	TopSouth,
	TopSouthLeft,
	TopSouthRight,
	TopWest,
	TopWestLeft,
	TopWestRight,
};

UENUM(BlueprintType)
enum class FAssetCardinalDirections : uint8
{
	Default,
	North,
	NorthLeft,
	NorthRight,
	South,
	SouthLeft,
	SouthRight,
	East,
	EastLeft,
	EastRight,
	West,
	WestLeft,
	WestRight,
	Center,
};

UENUM(BlueprintType)
enum class FBuildingComponentsNames : uint8
{
	Default UMETA(DisplayName = "Default"),
	FloorComponent UMETA(DisplayName = "FloorComponent"),
	RampComponent UMETA(DisplayName = "RampComponent"),
	FloorConnectComponent UMETA(DisplayName = "FloorConnectComponent"),
	FloorTileComponent UMETA(DisplayName = "FloorTileComponent"),
	RoofComponent UMETA(DisplayName = "RoofComponent"),
	RoofConnectComponent UMETA(DisplayName = "RoofConnectComponent"),
	RoofTileComponent UMETA(DisplayName = "RoofTileComponent"),
	WallComponent UMETA(DisplayName = "WallComponent"),
	WallClosedCornerLeftComponent UMETA(DisplayName = "WallClosedCornerLeftComponent"),
	WallClosedCornerRightComponent UMETA(DisplayName = "WallClosedCornerRightComponent"),
	WallOpenCornerLeftComponent UMETA(DisplayName = "WallOpenCornerLeftComponent"),
	WallOpenCornerRightComponent UMETA(DisplayName = "WallOpenCornerRightComponent"),
	WallEdgeConnect UMETA(DisplayName = "WallEdgeConnect"),
	WallHorizontalConnect UMETA(DisplayName = "WallHorizontalConnect"),
	WallShortConnect UMETA(DisplayName = "WallShortConnect"),
	WallTile UMETA(DisplayName = "WallTile"),
	WallVerticalConnect UMETA(DisplayName = "WallVerticalConnect"),
};

USTRUCT(BlueprintType)
struct FBoxAssetDataComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FTransform> Instances;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName> KeyToLoad;

public:

	void AddNewInstance(FVector BoxLocation, FTransform Instance, FVector BaseLength)
	{
		FTransform InstanceTransform = Instance;
		FVector InstanceLocation;
		InstanceLocation.X = Instance.GetLocation().X + (BoxLocation.X * BaseLength.X);
		InstanceLocation.Y = Instance.GetLocation().Y + (BoxLocation.Y * BaseLength.Y);
		InstanceLocation.Z = Instance.GetLocation().Z + (BoxLocation.Z * BaseLength.Z);
		InstanceTransform.SetLocation(InstanceLocation);
		Instances.Add(InstanceTransform);
	}
};


USTRUCT(BlueprintType)
struct FBoxDataComponent
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bUseAActor;
	/** TSubclassOf<AActor> that will be visible and editable only if bUseAActor is true. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bUseAActor"))
	TSubclassOf<AActor> TypeActor;
	/** UStaticMesh that will be visible and editable only if bUseAActor is false. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "!bUseAActor"))
	UStaticMesh* TypeMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FVector, FBoxAssetDataComponent> MapDataComponent;
};

USTRUCT(BlueprintType)
struct FBoxDataLayer
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FBuildingComponentsNames, FBoxDataComponent> MapBoxDataComponent;
};

USTRUCT(BlueprintType)
struct FDataInstancedMesh : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<int32, FBoxDataLayer> MapBaseBox;
};


UCLASS()
class CHALLENGERCORERUNTIME_API UChallengerDataInstancedMesh : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	void AddAssetBoxDataComponent(int32 NumLayer, FVector BoxBaseLocation, FBuildingComponentsNames ComponentType, UStaticMesh* TypeMesh, FTransform Instance, FVector BaseLength, FName KeyMap, bool bUseAActor, TSubclassOf<AActor> TypeActor);

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SaveData")
	TMap<int32, FBoxDataLayer> MapBaseBox;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataTable")
	UDataTable* DataTableInstancedMesh;
	/**
	* The ReadDataTable(); and WriteDataTable(); functions only work if the bButtonsEnable variable is set to true.
	* Make sure to enable this variable to use these functions successfully.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataTable")
	bool bButtonsEnable;

public:

	UFUNCTION(BlueprintCallable, Category = "SaveData")
	void CleanBaseBox();
	/**
	* The WriteDataTable() button is a powerful and sometimes dangerous tool.
	* Its function is to write the data defined in the DataAsset derived from UChallengerDataInstancedMesh to the DataTable file.
	* However, its use requires extreme caution, especially if the maps are empty, as it can result in the complete replacement of existing data in the DataTable, leading to the terrible loss of information.
	* It is strongly recommended to make a detailed and complete backup of the data before daring to execute this function, to avoid possible disruptions.
	* The ReadDataTable(); and WriteDataTable(); functions only work if the bButtonsEnable variable is set to true.
	* Make sure to enable this variable to use these functions successfully.
	*/
	UFUNCTION(CallInEditor, Category = "DataTable", meta = (EditCondition = "bButtonsEnable"))
	void WriteDataTable();
	/**
	* The ReadDataTable() button is designed to read data from the DataTable and write it to the DataAsset derived from UChallengerDataInstancedMesh.
	* It's important to note that if the DataTable is empty, executing this function can lead to the clearing of current data in the DataAsset, resulting in significant data loss.
	* Therefore, caution is advised when using this button, and it's recommended to always make a backup before usage, ensuring that the DataTable contains the necessary data before executing the function to prevent unwanted losses."
	* The ReadDataTable(); and WriteDataTable(); functions only work if the bButtonsEnable variable is set to true.
	* Make sure to enable this variable to use these functions successfully.
	*/
	UFUNCTION(CallInEditor, Category = "DataTable", meta = (EditCondition = "bButtonsEnable"))
	void ReadDataTable();
};
