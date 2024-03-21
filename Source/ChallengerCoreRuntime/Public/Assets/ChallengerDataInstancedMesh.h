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


UCLASS()
class CHALLENGERCORERUNTIME_API UChallengerDataInstancedMesh : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	void AddAssetBoxDataComponent(int32 NumLayer, FVector BoxBaseLocation, FBuildingComponentsNames ComponentType, UStaticMesh* TypeMesh, FTransform Instance, FVector BaseLength, FName KeyMap, bool bUseAActor, TSubclassOf<AActor> TypeActor);

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SaveData")
	TMap<int32, FBoxDataLayer> MapBaseBox;

public:

	UFUNCTION(BlueprintCallable, Category = "SaveData")
	void CleanBaseBox();
};
