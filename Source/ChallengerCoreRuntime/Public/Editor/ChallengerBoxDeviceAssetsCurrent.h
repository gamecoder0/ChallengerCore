// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Editor/ChallengerBoxDeviceAssets.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ChallengerBoxDeviceAssetsCurrent.generated.h"

class UEditorUtilityWidget;

USTRUCT(BlueprintType)
struct FBoxDataCurrentValues
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FBoxDeviceComponentData ComponentData;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FBoxDeviceAssetsData AssetsData;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FBoxAssetsAdjustments Adjustments;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FTransform CurrentTransform;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsEmpty = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 KeyNumAsset;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 KeyNumAdditional;

public:

	bool IsEmpty() const
	{
		return bIsEmpty;
	}
};

USTRUCT(BlueprintType)
struct FBoxDataDevice
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FName, FName> MapComponentKey;
};

USTRUCT(BlueprintType)
struct FBoxDataLayersList
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<int32, FBoxDataDevice> MapNumBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsEmpty = false;

public:

	void AddItem(int32 NumBox, FName ComponentTag, FName KeyMap)
	{
		IsEmpty = false;
		FBoxDataDevice DataDevice = MapNumBox.FindOrAdd(NumBox);
		DataDevice.MapComponentKey.Add(ComponentTag, KeyMap);
		MapNumBox.Add(NumBox, DataDevice);
	}
};

USTRUCT(BlueprintType)
struct FBoxDataLayers
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FBoxDataLayersList> LayersList;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 MaxListByLayer = 30;
	UPROPERTY()
	int32 UseUndo = 0;
public:

	void RemoveLast()
	{
		if (LayersList.Num() > MaxListByLayer)
		{
			LayersList.Pop();
		}
	}
	void AddFirst(FBoxDataLayersList List)
	{
		LayersList.Insert(List, 0);
	}
	FBoxDataLayersList GetFirst()
	{
		if(LayersList.Num() != 0)
		{
			return LayersList[0];
		}
		FBoxDataLayersList List;
		List.IsEmpty = true;
		return List;
	}
	void Undo()
	{
		if (LayersList.Num() != 0 && UseUndo < LayersList.Num())
		{
			FBoxDataLayersList First = LayersList[0];
			LayersList.RemoveAt(0);
			LayersList.Add(First);
			UseUndo = FMath::Clamp((UseUndo + 1), 0, MaxListByLayer);
		}
	}
	void Redo()
	{

		if (LayersList.Num() != 0 && UseUndo > 0)
		{
			FBoxDataLayersList Last = LayersList.Last();
			LayersList.RemoveAt(LayersList.Num() -1 );
			LayersList.Insert(Last, 0);
			UseUndo = FMath::Clamp((UseUndo - 1), 0, MaxListByLayer);
		}
	}
};

USTRUCT(BlueprintType)
struct FBoxDataBuilding
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<int32, FBoxDataLayers> MapDataLayers;
	
public:

	bool IsEmpty()
	{
		if (MapDataLayers.Num() == 0)
		{
			return true;
		}
		return false;
	}
};

UCLASS()
class CHALLENGERCORERUNTIME_API UChallengerBoxDeviceAssetsCurrent : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	virtual void PostLoad();

public:

	UFUNCTION(CallInEditor, Category = "DeviceAssets")
	void UpdateData();

public:

	static FName GenerateKeyMapCurrentValues(FName ComponentTag, int32 NumAsset, int32 NumAdditional);
	static FName ConvertCompotentTagOfKeyMap(FName KeyMap);

public:
	FVector GetBaseLength();
	FBoxDataCurrentValues FindCurrentValuesDataSelection(FName ComponentTag, int32 NumAsset, int32 NumAdditional);
	FBoxDataCurrentValues FindCurrentValuesData(FName ComponentTag, int32 NumAsset, int32 NumAdditional);
	FBoxDataCurrentValues FindCurrentValuesData(FName KeyMap);
	void UpdateDataBuildingClipboard(FName ComponentTag, FName KeyMap, int32 NumLayer, int32 NumBox);
	void UpdateDataBuildingClipboard(TMap<FName, FName> MapComponentKey, int32 NumLayer, int32 NumBox);
	void UpdateSave(int32 NumLayer, FVector BasePosition, FName KeyMap);
	TArray<FName> GetMapLoad(int32 Numlayer, FVector BasePosition);
	void SetClipboard(bool Undo, int32 NumLayer);
	FBoxDataLayersList FindDataBuildingCurrentByLayer(int32 NumLayer);
	void ClearDataLayersList(int32 NumLayer);
	void ClearDataBuilding();
	void AddDataLayersList(int32 NumLayer, int32 NumBox, FName ComponentTag, FName KeyMap);

public:

	UPROPERTY(EditAnywhere, Category = "DeviceAssets")
	UChallengerBoxDeviceAssets* DeviceAsset;
	UPROPERTY(EditAnywhere, Category = "DeviceAssets")
	UChallengerBoxDeviceAssets* DeviceAssetSelection;
	UPROPERTY(VisibleAnywhere , Category = "DeviceAssets")
	TMap<FName, FBoxDataCurrentValues> MappingBaseAssetsSelected;
	UPROPERTY(VisibleAnywhere, Category = "DeviceAssets")
	TMap<FName, FBoxDataCurrentValues> MappingBaseAssets;
	UPROPERTY(VisibleAnywhere, Category = "EditorUtilityWidget")
	int32 AmountWidgetsToGenerate;
	UPROPERTY(EditAnywhere, Category = "EditorUtilityWidget")
	TSubclassOf<UEditorUtilityWidget> SelectMeshUtilityClass;
	UPROPERTY(EditAnywhere, Category = "SaveDeviceAssets")
	UChallengerDataInstancedMesh* SaveDeviceAssets;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FName, FName> CurrentMapComponentKey;

private:

	UPROPERTY(VisibleAnywhere, Category = "DataBuilding")
	FBoxDataBuilding DataBuilding;

private:

	void UpdateBoxCurrentDataSelection();
	void UpdateBoxCurrentData();
};
