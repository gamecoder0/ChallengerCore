// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Editor/ChallengerBoxLayerDeviceManager.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChallengerBoxLayeringDevice.generated.h"

class AChallengerBoxLayerDeviceManager;
class AChallengerBoxDevice;
class UEditorUtilityWidget;

UCLASS()
class CHALLENGERCORERUNTIME_API AChallengerBoxLayeringDevice : public AActor
{
	GENERATED_BODY()
	
public:	

	AChallengerBoxLayeringDevice();

public:

	void LayerSpawn();
	void LayerUpdate();
	void SetStartValuesLayerDeviceManager(AChallengerBoxLayerDeviceManager* DeviceManager, TSubclassOf<AChallengerBoxDevice> BoxClass, bool bLayerSelected, int32 NumChannel, int32 NumLayer, int32 DimensionsX, int32 DimensionsY, int32 DimensionsZ);
	FVector GetPositionsBoxSelected();
	void RemoveBuildingBoxes();
	void SetNumLayeringDevice(int32 NumLayer);
	int32 GetNumChannelDevice();
	int32 GetNumLayerDevice();
	void SetPositionsBoxSelected(FVector Position);
	void UpdateBoxSelectedAndHide();
	void HideAllBox();
	void SetDirectionSelected(FAssetCardinalDirections Direction);
	void UpdateBoxSelected();
	void BoxSpawn(FVector Position, int32 BoxNum);
	void BoxUpdate(AChallengerBoxDevice* BoxDevice);
	TArray<UEditorUtilityWidget*> GetSelectMeshUtilityWidget();
	UChallengerBoxDeviceAssetsCurrent* GetDeviceAssetsCurrent();
	void UpdateMeshInBox(FName ComponentName, int32 NumAsset, int32 NumAdditional);
	void SetClipboard(bool Undo);
	void UpdateSave();
	void UpdateLoad();
	void UpdateBake();
	void MarkInsertedAssetsInBoxSelected();
	void MarkInsertedAssetsInLayer();
	void ClearMarkInsertedAssetsInBoxSelected();
	
private:

	TArray<FVector> GetBuildingPositions(int32 RoomsBuildingX, int32 RoomsBuildingY, int32 RoomsBuildingZ);
	FVector GenerateDimensions(FVector BoxPosition);
	FVector GetBuildingPositionsUnits(int32 RoomsBuildingX, int32 RoomsBuildingY, int32 RoomsBuildingZ);
	void GeneratedBuildingBoxes();
	void UpdateBuildingBoxes();
	void GeneratedEditorUtilityWidget();
	AChallengerBoxDevice* FindBoxDeviceSelected();

public:

	UPROPERTY(EditAnywhere, Category = "LayeringDevice")
	int32 AmountLayersByChannel;
	
private:

	UPROPERTY(VisibleAnywhere, Category = "LayeringDevice")
	int32 NumChannelDevice;
	UPROPERTY(VisibleAnywhere, Category = "LayeringDevice")
	int32 NumLayeringDevice;
	UPROPERTY(EditAnywhere, Category = "LayeringDevice")
	FString PathSpawnMesh;
	UPROPERTY(EditAnywhere, Category = "LayeringDevice")
	UChallengerBoxDeviceAssetsCurrent* DeviceAssetsCurrent;
	UPROPERTY(VisibleAnywhere, Category = "EditorUtilityWidget")
	TArray<UEditorUtilityWidget*> SelectMeshUtilityWidget;

private:

	UPROPERTY()
	AChallengerBoxLayerDeviceManager* LayerDeviceManager;
	UPROPERTY()
	TSubclassOf<AChallengerBoxDevice> BoxDeviceClass;
	UPROPERTY()
	bool bIsLayerSelected;
	UPROPERTY()
	int32 NumRoomsBuildingX;
	UPROPERTY()
	int32 NumRoomsBuildingY;
	UPROPERTY()
	int32 NumRoomsBuildingZ;
	UPROPERTY()
	FVector PositionsBoxSelected;
	UPROPERTY()
	TMap<FVector, AChallengerBoxDevice*> MapPositionsBoxDevice;
	UPROPERTY()
	TArray<AChallengerBoxDevice*> AllBoxDevice;
};
