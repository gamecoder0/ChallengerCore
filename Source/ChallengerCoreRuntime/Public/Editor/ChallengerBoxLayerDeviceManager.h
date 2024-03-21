// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Assets/ChallengerDataInstancedMesh.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChallengerBoxLayerDeviceManager.generated.h"

class AChallengerBoxDevice;
class AChallengerBoxLayeringDevice;
class UChallengerBoxDeviceAssets;
class UChallengerBoxDeviceAssetsCurrent;
class UEditorUtilityWidget;

USTRUCT(BlueprintType)
struct FBoxLayeringDeviceAndChannel
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly);
	int32 LayerValue;
	UPROPERTY(BlueprintReadOnly);
	AChallengerBoxLayeringDevice* BoxLayeringDevice;

};
USTRUCT(BlueprintType)
struct FBoxLayeringDevice
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly);
	TArray<FBoxLayeringDeviceAndChannel> LayeringDeviceAndChannel;
};

UCLASS()
class CHALLENGERCORERUNTIME_API AChallengerBoxLayerDeviceManager : public AActor
{
	GENERATED_BODY()
	
public:	

	AChallengerBoxLayerDeviceManager();

public:

	UFUNCTION(BlueprintCallable, Category = "Generate")
	void StartBuildingLayers();
	UFUNCTION(BlueprintCallable, Category = "Generate")
	void UpdateBuildingLayers();
	UFUNCTION(BlueprintCallable, Category = "Generate")
	void RemoveBuildingLayers();
	UFUNCTION(BlueprintCallable, Category = "SetMoveBox")
	void SetBoxMoveForwardDeviceManager();
	UFUNCTION(BlueprintCallable, Category = "SetMoveBox")
	void SetBoxMoveBackwardDeviceManager();
	UFUNCTION(BlueprintCallable, Category = "SetMoveBox")
	void SetBoxMoveLeftDeviceManager();
	UFUNCTION(BlueprintCallable, Category = "SetMoveBox")
	void SetBoxMoveRightDeviceManager();
	UFUNCTION(BlueprintCallable, Category = "SetMoveBox")
	void SetBoxMoveUpDeviceManager();
	UFUNCTION(BlueprintCallable, Category = "SetMoveBox")
	void SetBoxMoveDownDeviceManager();
	UFUNCTION(BlueprintPure, Category = "SetMoveBox")
	TMap<int32, int32> GetMapWithKeyChannels();
	UFUNCTION(BlueprintPure, Category = "SetMoveBox")
	TMap<int32, int32> GetMapWithKeyLayers();
	UFUNCTION(BlueprintPure, Category = "SetMoveBox")
	bool CheckChannelIsSelected(int32 Value);
	UFUNCTION(BlueprintPure, Category = "SetMoveBox")
	bool CheckLayerIsSelected(int32 Value);
	UFUNCTION(BlueprintCallable, Category = "AssetsChoice")
	void UpdateAssetsChoice(FAssetCardinalDirections Direction);
	UFUNCTION(BlueprintCallable, Category = "Channel")
	void SetNumChannelSelected(int32 Value);
	UFUNCTION(BlueprintCallable, Category = "Layer")
	void SetNumLayerSelected(int32 Value);
	UFUNCTION(BlueprintCallable, Category = "Layer")
	TArray<UEditorUtilityWidget*> GetListWidgetsOfLayerSelected();
	UFUNCTION(BlueprintCallable, Category = "CardinalDirectionChannel")
	void SwitchCardinalDirectionChannel(FAssetCardinalDirections Direction, TArray<FBoxDataCurrentValues>& ArrayCurrentValues);
	UFUNCTION(BlueprintCallable, Category = "CardinalDirectionChannel")
	void UpdateSwapCardinalDirectionChannel(FAssetCardinalDirections Direction);
	UFUNCTION(BlueprintPure, Category = "CardinalDirectionChannel")
	bool GetSwapCardinalDirectionChannel();
	UFUNCTION(BlueprintCallable, Category = "Layer")
	void UpdateMeshInBox(FName ComponentName, int32 NumAsset, int32 NumAdditional);
	UFUNCTION(BlueprintCallable, Category = "SwapNum")
	int32 SwapNumAdditional(int32 NumAdditional, int32 NumAdditionalLength, bool Increase);
	UFUNCTION(BlueprintCallable, Category = "Clipboard")
	void SetClipboard(bool Undo);
	UFUNCTION(BlueprintCallable, Category = "SaveLoad")
	void UpdateSave();
	UFUNCTION(BlueprintCallable, Category = "SaveLoad")
	void UpdateLoad();
	UFUNCTION(BlueprintCallable, Category = "SaveLoad")
	void UpdateBake();
	UFUNCTION(BlueprintCallable, Category = "SaveLoad")
	int32 SwitchMarkInsertedAssets();

public:

	UPROPERTY(EditAnywhere, Category = "LayeringDevices")
	TArray<TSubclassOf<AChallengerBoxLayeringDevice>> ChannelsDevicesClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
	TSubclassOf<AChallengerBoxDevice> BoxDeviceClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BuildingDimensions", meta = (ClampMin = "1.0", UIMin = "1.0"))
	int32 NumRoomsBuildingX;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BuildingDimensions", meta = (ClampMin = "1.0", UIMin = "1.0"))
	int32 NumRoomsBuildingY;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BuildingDimensions", meta = (ClampMin = "1.0", UIMin = "1.0"))
	int32 NumRoomsBuildingZ;
	
private:

	UPROPERTY(VisibleAnywhere, Category = "LayeringDevices")
	int32 NumLayerSelected;
	UPROPERTY(VisibleAnywhere, Category = "LayeringDevices")
	int32 NumChannelSelected;
	UPROPERTY(VisibleAnywhere, Category = "LayeringDevices")
	int32 NumSwitchMarkAssets;

private:

	UPROPERTY()
	FAssetCardinalDirections DirectionChoiceSelected;
	UPROPERTY()
	TMap<int32, AChallengerBoxLayeringDevice*> MapLayeringDevices;
	UPROPERTY()
	TArray<AChallengerBoxLayeringDevice*> LayeringDevices;
	UPROPERTY()
	TMap<int32, FBoxLayeringDevice> MapLayeringDevicesByChannel;
	UPROPERTY()
	bool CheckUpdateHideAllBox;
	UPROPERTY()
	int32 CardinalDirectionChannel;
	UPROPERTY()
	bool SwapCardinalDirectionChannel;
	UPROPERTY()
	bool SwitchCardinalChannelInverse;
	UPROPERTY()
	bool SwitchCardinalChannelValueUpdate;
	
private:

	void LayerSpawn(int32 NumChannel, int32 NumLayer, TSubclassOf<AChallengerBoxLayeringDevice> Layer);
	void LayerUpdate(int32 NumChannel, int32 NumLayer, AChallengerBoxLayeringDevice* Layer);
	void UpdateLayeringDevicesByChannel();
	void HideAlllayers();
	void UpdateLayerAndBoxSelected();
	AChallengerBoxLayeringDevice* GetLayerSelected();
	void UpdateSwitchMarkInsertedAssets();
};
