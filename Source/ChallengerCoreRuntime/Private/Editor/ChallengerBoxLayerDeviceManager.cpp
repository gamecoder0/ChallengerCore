// Fill out your copyright notice in the Description page of Project Settings.


#include "Editor/ChallengerBoxLayerDeviceManager.h"
#include "Editor/ChallengerBoxLayeringDevice.h"
#include "Editor/ChallengerBoxDeviceAssetsCurrent.h"

AChallengerBoxLayerDeviceManager::AChallengerBoxLayerDeviceManager()
{
	PrimaryActorTick.bCanEverTick = false;
	DirectionChoiceSelected = FAssetCardinalDirections::Default;
	CardinalDirectionChannel = 0;
	SwapCardinalDirectionChannel = true;
	SwitchCardinalChannelValueUpdate = false;
	NumSwitchMarkAssets = 0;
}

void AChallengerBoxLayerDeviceManager::StartBuildingLayers()
{
	RemoveBuildingLayers();
	MapLayeringDevices.Empty();
	LayeringDevices.Empty();
	int32 NumChannel = 0;
	int32 NumLayer = 0;
	for (TSubclassOf<AChallengerBoxLayeringDevice> Channel : ChannelsDevicesClass)
	{
		UClass* LayerClass = Channel.Get();
		if (LayerClass)
		{
			AChallengerBoxLayeringDevice* DefaultLayer = Cast<AChallengerBoxLayeringDevice>(LayerClass->GetDefaultObject());
			if (DefaultLayer)
			{
				int32 Amount = DefaultLayer->AmountLayersByChannel + 1;
				for (int32 Num = 1; Num < Amount; Num++)
				{
					UE_LOG(LogTemp, Warning, TEXT("Antes (Num Channel : %d) (Num Layer : %d) (Amount Layers %d)"), NumChannel, NumLayer, Amount);
					LayerSpawn(NumChannel, NumLayer, Channel);
					NumLayer++;
				}
				NumChannel++;
			}
		}
	}
	UpdateLayeringDevicesByChannel();
	HideAlllayers();
	UpdateLayerAndBoxSelected();
}

void AChallengerBoxLayerDeviceManager::UpdateBuildingLayers()
{
	TArray<AActor*> ChildActors;
	GetAttachedActors(ChildActors);

	if(ChildActors.Num() == 0)
	{
		StartBuildingLayers();
	}
	else
	{
		bool FoundLayer;
		MapLayeringDevices.Empty();
		LayeringDevices.Empty();
		int32 NumChannel = 0;
		int32 NumLayer = 0;
		TArray<AChallengerBoxLayeringDevice*> ChildsLayers;
		for (TSubclassOf<AChallengerBoxLayeringDevice> Channel : ChannelsDevicesClass)
		{
			UClass* LayerClass = Channel.Get();
			if (LayerClass)
			{
				FoundLayer = false;
				for (AActor* ChildActor : ChildActors)
				{
					AChallengerBoxLayeringDevice* ChildLayer = Cast<AChallengerBoxLayeringDevice>(ChildActor);
					if (ChildLayer && LayerClass == ChildLayer->GetClass())
					{
						NumChannel = ChildLayer->GetNumChannelDevice();
						NumLayer = ChildLayer->GetNumLayerDevice();
						FoundLayer = true;
						LayerUpdate(NumChannel, NumLayer, ChildLayer);
					}
				}
				if (!FoundLayer)
				{
					AChallengerBoxLayeringDevice* DefaultLayer = Cast<AChallengerBoxLayeringDevice>(LayerClass->GetDefaultObject());
					if (DefaultLayer)
					{
						NumChannel++;
						for (int32 Num = 1; Num < (DefaultLayer->AmountLayersByChannel + 1); Num++)
						{
							NumLayer++;
							LayerSpawn(NumChannel, NumLayer, Channel);
						}
					}
				}
			}
		}

		UpdateLayeringDevicesByChannel();
		HideAlllayers();
		UpdateLayerAndBoxSelected();
	}
}

void AChallengerBoxLayerDeviceManager::RemoveBuildingLayers()
{
	TArray<AActor*> ChildActors;
	GetAttachedActors(ChildActors);

	for (AActor* ChildActor : ChildActors)
	{
		AChallengerBoxLayeringDevice* ChildLayer = Cast<AChallengerBoxLayeringDevice>(ChildActor);
		if(ChildLayer && ChildLayer->IsValidLowLevelFast(true))
		{
			ChildLayer->RemoveBuildingBoxes();
			ChildLayer->Destroy();
		}
	}
}

void AChallengerBoxLayerDeviceManager::SetBoxMoveForwardDeviceManager()
{
	FBoxLayeringDevice FoundLayeringDevice = MapLayeringDevicesByChannel.FindOrAdd(NumChannelSelected);
	bool Calculate = true;
	int32 Selected, Box;
	FVector Position;
	for (FBoxLayeringDeviceAndChannel LayeringDevice : FoundLayeringDevice.LayeringDeviceAndChannel)
	{
		AChallengerBoxLayeringDevice* Device = LayeringDevice.BoxLayeringDevice;
		if (Device)
		{
			if (Calculate)
			{
				Position = Device->GetPositionsBoxSelected();
				Box = (Device->GetPositionsBoxSelected().Y) - 1;
				Selected = (Box + NumRoomsBuildingY) % (NumRoomsBuildingY);
				Position.Y = Selected;
				Calculate = false;
			}
			Device->SetPositionsBoxSelected(Position);
			Device->HideAllBox();
		}
	}
	UpdateLayerAndBoxSelected();
	UpdateSwitchMarkInsertedAssets();
}

void AChallengerBoxLayerDeviceManager::SetBoxMoveBackwardDeviceManager()
{
	FBoxLayeringDevice FoundLayeringDevice = MapLayeringDevicesByChannel.FindOrAdd(NumChannelSelected);
	bool Calculate = true;
	int32 Selected, Box;
	FVector Position;
	for (FBoxLayeringDeviceAndChannel LayeringDevice : FoundLayeringDevice.LayeringDeviceAndChannel)
	{
		AChallengerBoxLayeringDevice* Device = LayeringDevice.BoxLayeringDevice;
		if (Device)
		{
			if (Calculate)
			{
				Position = Device->GetPositionsBoxSelected();
				Box = (Device->GetPositionsBoxSelected().Y) + 1;
				Selected = (Box + NumRoomsBuildingY) % (NumRoomsBuildingY);
				Position.Y = Selected;
				Calculate = false;
			}
			Device->SetPositionsBoxSelected(Position);
			Device->HideAllBox();
		}
	}
	UpdateLayerAndBoxSelected();
	UpdateSwitchMarkInsertedAssets();
}

void AChallengerBoxLayerDeviceManager::SetBoxMoveLeftDeviceManager()
{
	FBoxLayeringDevice FoundLayeringDevice = MapLayeringDevicesByChannel.FindOrAdd(NumChannelSelected);
	bool Calculate = true;
	int32 Selected, Box;
	FVector Position;
	for (FBoxLayeringDeviceAndChannel LayeringDevice : FoundLayeringDevice.LayeringDeviceAndChannel)
	{
		AChallengerBoxLayeringDevice* Device = LayeringDevice.BoxLayeringDevice;
		if (Device)
		{
			if (Calculate)
			{
				Position = Device->GetPositionsBoxSelected();
				Box = (Device->GetPositionsBoxSelected().X) - 1;
				Selected = (Box + NumRoomsBuildingX) % (NumRoomsBuildingX);
				Position.X = Selected;
				Calculate = false;
			}
			Device->SetPositionsBoxSelected(Position);
			Device->HideAllBox();
		}
	}
	UpdateLayerAndBoxSelected();
	UpdateSwitchMarkInsertedAssets();
}

void AChallengerBoxLayerDeviceManager::SetBoxMoveRightDeviceManager()
{
	FBoxLayeringDevice FoundLayeringDevice = MapLayeringDevicesByChannel.FindOrAdd(NumChannelSelected);
	bool Calculate = true;
	int32 Selected, Box;
	FVector Position;
	for (FBoxLayeringDeviceAndChannel LayeringDevice : FoundLayeringDevice.LayeringDeviceAndChannel)
	{
		AChallengerBoxLayeringDevice* Device = LayeringDevice.BoxLayeringDevice;
		if(Device)
		{
			if (Calculate)
			{
				Position = Device->GetPositionsBoxSelected();
				Box = (Device->GetPositionsBoxSelected().X) + 1;
				Selected = (Box + NumRoomsBuildingX) % (NumRoomsBuildingX);
				Position.X = Selected;
				Calculate = false;
			}
			Device->SetPositionsBoxSelected(Position);
			Device->HideAllBox();
		}
	}
	UpdateLayerAndBoxSelected();
	UpdateSwitchMarkInsertedAssets();
}

void AChallengerBoxLayerDeviceManager::SetBoxMoveUpDeviceManager()
{
	FBoxLayeringDevice FoundLayeringDevice = MapLayeringDevicesByChannel.FindOrAdd(NumChannelSelected);
	bool Calculate = true;
	int32 Selected, Box;
	FVector Position;
	for (FBoxLayeringDeviceAndChannel LayeringDevice : FoundLayeringDevice.LayeringDeviceAndChannel)
	{
		AChallengerBoxLayeringDevice* Device = LayeringDevice.BoxLayeringDevice;
		if (Device)
		{
			if (Calculate)
			{
				Position = Device->GetPositionsBoxSelected();
				Box = (Device->GetPositionsBoxSelected().Z) + 1;
				Selected = (Box + NumRoomsBuildingZ) % (NumRoomsBuildingZ);
				Position.Z = Selected;
				Calculate = false;
			}
			Device->SetPositionsBoxSelected(Position);
			Device->HideAllBox();
		}
	}
	UpdateLayerAndBoxSelected();
	UpdateSwitchMarkInsertedAssets();
}

void AChallengerBoxLayerDeviceManager::SetBoxMoveDownDeviceManager()
{
	FBoxLayeringDevice FoundLayeringDevice = MapLayeringDevicesByChannel.FindOrAdd(NumChannelSelected);
	bool Calculate = true;
	int32 Selected, Box;
	FVector Position;
	for (FBoxLayeringDeviceAndChannel LayeringDevice : FoundLayeringDevice.LayeringDeviceAndChannel)
	{
		AChallengerBoxLayeringDevice* Device = LayeringDevice.BoxLayeringDevice;
		if (Device)
		{
			if (Calculate)
			{
				Position = Device->GetPositionsBoxSelected();
				Box = (Device->GetPositionsBoxSelected().Z) - 1;
				Selected = (Box + NumRoomsBuildingZ) % (NumRoomsBuildingZ);
				Position.Z = Selected;
				Calculate = false;
			}
			Device->SetPositionsBoxSelected(Position);
			Device->HideAllBox();
		}
	}
	UpdateLayerAndBoxSelected();
	UpdateSwitchMarkInsertedAssets();
}

void AChallengerBoxLayerDeviceManager::SetNumChannelSelected(int32 Value)
{
	if (Value != NumChannelSelected)
	{
		NumChannelSelected = Value;
		HideAlllayers();
		UpdateLayerAndBoxSelected();
	}
}

void AChallengerBoxLayerDeviceManager::SetNumLayerSelected(int32 Value)
{
	if(Value != NumLayerSelected)
	{
		NumLayerSelected = Value;
		HideAlllayers();
		UpdateLayerAndBoxSelected();
		UpdateAssetsChoice(DirectionChoiceSelected);
		UpdateSwitchMarkInsertedAssets();

	}
}

TArray<UEditorUtilityWidget*> AChallengerBoxLayerDeviceManager::GetListWidgetsOfLayerSelected()
{
	AChallengerBoxLayeringDevice* LayeringDevice = GetLayerSelected();
	if (LayeringDevice)
	{
		return LayeringDevice->GetSelectMeshUtilityWidget();
	}
	return TArray<UEditorUtilityWidget*>();
}

void AChallengerBoxLayerDeviceManager::SwitchCardinalDirectionChannel(FAssetCardinalDirections Direction, TArray<FBoxDataCurrentValues>& ArrayCurrentValues)
{
	AChallengerBoxLayeringDevice* LayeringDevice = GetLayerSelected();
	UChallengerBoxDeviceAssetsCurrent* DeviceAssetsCurrent;
	TArray<EBoxComponentsTags> EnumComponentsTags = UChallengerBoxDeviceAssets::GetComponentsTagsByDirection(Direction);
	int32 EnumLenght = EnumComponentsTags.Num();
	FName ComponentName;
	
	if (DirectionChoiceSelected == Direction)
	{
		CardinalDirectionChannel = ((CardinalDirectionChannel + EnumLenght)) % (EnumLenght);
		if (SwapCardinalDirectionChannel)
		{
			if (SwitchCardinalChannelInverse)
			{
				SwitchCardinalChannelInverse = false;
				CardinalDirectionChannel = ((CardinalDirectionChannel + EnumLenght) + 1) % (EnumLenght);

			}
			if (LayeringDevice && LayeringDevice->GetDeviceAssetsCurrent())
			{
				DeviceAssetsCurrent = LayeringDevice->GetDeviceAssetsCurrent();
				if(DeviceAssetsCurrent)
				{
					ComponentName = FName(*UEnum::GetDisplayValueAsText(EnumComponentsTags[CardinalDirectionChannel]).ToString());
					FBoxDataCurrentValues FirstCurrentValues = DeviceAssetsCurrent->FindCurrentValuesData(ComponentName, 0, 0);
					UE_LOG(LogTemp, Warning, TEXT("(Component Name : %s)(Cardial Direction Channel : %d)"), *UEnum::GetDisplayValueAsText(EnumComponentsTags[CardinalDirectionChannel]).ToString(), CardinalDirectionChannel);
					int32 LenMeshes = FirstCurrentValues.ComponentData.Assets.Num();
					if(!FirstCurrentValues.IsEmpty())
					{
						for(int Asset = 0; Asset < LenMeshes; Asset++)
						{
							FBoxDataCurrentValues CurrentValues = DeviceAssetsCurrent->FindCurrentValuesData(ComponentName, Asset, 0);
							ArrayCurrentValues.Add(CurrentValues);
						}
					}
				}
			}
			CardinalDirectionChannel = ((CardinalDirectionChannel + EnumLenght) + 1) % (EnumLenght);
			SwitchCardinalChannelValueUpdate = true;
		}
		else
		{
			if (SwitchCardinalChannelInverse)
			{
				SwitchCardinalChannelInverse = false;
				CardinalDirectionChannel = ((CardinalDirectionChannel + EnumLenght) - 1) % (EnumLenght);

			}
			if (LayeringDevice && LayeringDevice->GetDeviceAssetsCurrent())
			{
				DeviceAssetsCurrent = LayeringDevice->GetDeviceAssetsCurrent();
				if (DeviceAssetsCurrent)
				{
					ComponentName = FName(*UEnum::GetDisplayValueAsText(EnumComponentsTags[CardinalDirectionChannel]).ToString());
					FBoxDataCurrentValues FirstCurrentValues = DeviceAssetsCurrent->FindCurrentValuesData(ComponentName, 0, 0);
					int32 LenMeshes = FirstCurrentValues.ComponentData.Assets.Num();
					if (!FirstCurrentValues.IsEmpty())
					{
						for (int Asset = 0; Asset < LenMeshes; Asset++)
						{
							FBoxDataCurrentValues CurrentValues = DeviceAssetsCurrent->FindCurrentValuesData(ComponentName, Asset, 0);
							ArrayCurrentValues.Add(CurrentValues);
						}
					}
				}
			}
			CardinalDirectionChannel = ((CardinalDirectionChannel + EnumLenght) - 1) % (EnumLenght);
			SwitchCardinalChannelValueUpdate = true;
		}
	}
	else
	{
		if (SwapCardinalDirectionChannel)
		{
			if (SwitchCardinalChannelValueUpdate)
			{
				CardinalDirectionChannel = ((CardinalDirectionChannel + EnumLenght) - 1) % (EnumLenght);
			}
		}
		else
		{
			if (SwitchCardinalChannelValueUpdate)
			{
				CardinalDirectionChannel = ((CardinalDirectionChannel + EnumLenght) + 1) % (EnumLenght);
			}
		}
		CardinalDirectionChannel = (CardinalDirectionChannel + EnumLenght) % (EnumLenght);
		if (LayeringDevice && LayeringDevice->GetDeviceAssetsCurrent())
		{
			DeviceAssetsCurrent = LayeringDevice->GetDeviceAssetsCurrent();
			if (DeviceAssetsCurrent)
			{
				ComponentName = FName(*UEnum::GetDisplayValueAsText(EnumComponentsTags[CardinalDirectionChannel]).ToString());
				FBoxDataCurrentValues FirstCurrentValues = DeviceAssetsCurrent->FindCurrentValuesData(ComponentName, 0, 0);
				int32 LenMeshes = FirstCurrentValues.ComponentData.Assets.Num();
				if (!FirstCurrentValues.IsEmpty())
				{
					for (int Asset = 0; Asset < LenMeshes; Asset++)
					{
						FBoxDataCurrentValues CurrentValues = DeviceAssetsCurrent->FindCurrentValuesData(ComponentName, Asset, 0);
						ArrayCurrentValues.Add(CurrentValues);
					}
				}
			}
		}
		SwitchCardinalChannelInverse = true;
		SwitchCardinalChannelValueUpdate = false;
	}
	UpdateAssetsChoice(Direction);
}

void AChallengerBoxLayerDeviceManager::UpdateSwapCardinalDirectionChannel(FAssetCardinalDirections Direction)
{
	if (DirectionChoiceSelected == Direction)
	{
		if (SwapCardinalDirectionChannel)
		{
			SwapCardinalDirectionChannel = false;
			CardinalDirectionChannel = CardinalDirectionChannel - 2;
		}
		else
		{
			SwapCardinalDirectionChannel = true;
			CardinalDirectionChannel = CardinalDirectionChannel + 2;
		}
	}
	else
	{
		if (SwapCardinalDirectionChannel)
		{
			SwapCardinalDirectionChannel = false;
			CardinalDirectionChannel = CardinalDirectionChannel + 1;
		}
		else
		{
			SwapCardinalDirectionChannel = true;
			CardinalDirectionChannel = CardinalDirectionChannel - 1;
		}
	}
}
bool AChallengerBoxLayerDeviceManager::GetSwapCardinalDirectionChannel()
{
	return SwapCardinalDirectionChannel;
}

void AChallengerBoxLayerDeviceManager::UpdateMeshInBox(FName ComponentName, int32 NumAsset, int32 NumAdditional)
{
	if(AChallengerBoxLayeringDevice* LayeringDevice = GetLayerSelected())
	{
		LayeringDevice->UpdateMeshInBox(ComponentName, NumAsset, NumAdditional);
	}
}

int32 AChallengerBoxLayerDeviceManager::SwapNumAdditional(int32 NumAdditional, int32 NumAdditionalLength, bool Increase)
{
	int32 Num = 0;
	if (Increase)
	{
		Num = ((NumAdditional + NumAdditionalLength) + 1) % (NumAdditionalLength);
	}
	else
	{
		Num = ((NumAdditional + NumAdditionalLength) - 1) % (NumAdditionalLength);
	}
	return Num;
}

void AChallengerBoxLayerDeviceManager::SetClipboard(bool Undo)
{
	if (AChallengerBoxLayeringDevice* LayeringDevice = GetLayerSelected())
	{
		LayeringDevice->SetClipboard(Undo);
	}
}

void AChallengerBoxLayerDeviceManager::UpdateSave()
{
	UpdateLayeringDevicesByChannel();
	for (AChallengerBoxLayeringDevice* Layer :  LayeringDevices)
	{
		Layer->UpdateSave();
	}
}

void AChallengerBoxLayerDeviceManager::UpdateLoad()
{
	UpdateLayeringDevicesByChannel();
	for (AChallengerBoxLayeringDevice* Layer : LayeringDevices)
	{
		Layer->UpdateLoad();
	}
}

void AChallengerBoxLayerDeviceManager::UpdateBake()
{
	UpdateLayeringDevicesByChannel();
	for (AChallengerBoxLayeringDevice* Layer : LayeringDevices)
	{
		Layer->UpdateBake();
	}
}

int32 AChallengerBoxLayerDeviceManager::SwitchMarkInsertedAssets()
{
	int32 MaxSwitch = 3;
	NumSwitchMarkAssets = (NumSwitchMarkAssets + 1) % MaxSwitch;
	UE_LOG(LogTemp, Warning, TEXT("Num Switch Mark %d"), NumSwitchMarkAssets);
	if (NumSwitchMarkAssets == 0)
	{
		for (AChallengerBoxLayeringDevice* LayerDevice : LayeringDevices)
		{
			LayerDevice->ClearMarkInsertedAssetsInBoxSelected();
		}
	}
	if (NumSwitchMarkAssets == 1)
	{
		for (AChallengerBoxLayeringDevice* LayerDevice : LayeringDevices)
		{
			LayerDevice->ClearMarkInsertedAssetsInBoxSelected();
		}
		AChallengerBoxLayeringDevice* LayeringDevice = GetLayerSelected();
		LayeringDevice->MarkInsertedAssetsInBoxSelected();
	}
	if (NumSwitchMarkAssets == 2)
	{
		for (AChallengerBoxLayeringDevice* LayerDevice : LayeringDevices)
		{
			LayerDevice->ClearMarkInsertedAssetsInBoxSelected();
		}
		AChallengerBoxLayeringDevice* LayeringDevice = GetLayerSelected();
		LayeringDevice->MarkInsertedAssetsInLayer();
	}
	return NumSwitchMarkAssets;
}

TMap<int32, int32> AChallengerBoxLayerDeviceManager::GetMapWithKeyChannels()
{
	UpdateLayeringDevicesByChannel();
	TMap<int32, int32> ChannelLayers;
	for (const TPair<int32, FBoxLayeringDevice> Pair : MapLayeringDevicesByChannel)
	{
		int32 Key = Pair.Key;
		int32 Value = Pair.Value.LayeringDeviceAndChannel[0].LayerValue;
		ChannelLayers.Add(Key, Value);
	}
	return ChannelLayers;
}


TMap<int32, int32> AChallengerBoxLayerDeviceManager::GetMapWithKeyLayers()
{
	UpdateLayeringDevicesByChannel();
	TMap<int32, int32> ChannelLayers;
	for (const TPair<int32, FBoxLayeringDevice> Pair : MapLayeringDevicesByChannel)
	{
		FBoxLayeringDevice LayeringDevice = Pair.Value;
		for (FBoxLayeringDeviceAndChannel Layer : LayeringDevice.LayeringDeviceAndChannel)
		{
			ChannelLayers.Add(Layer.LayerValue, Pair.Key);
		}
	}
	return ChannelLayers;
}

bool AChallengerBoxLayerDeviceManager::CheckChannelIsSelected(int32 Value)
{
	if (NumChannelSelected == Value)
	{
		return true;
	}
	return false;
}

bool AChallengerBoxLayerDeviceManager::CheckLayerIsSelected(int32 Value)
{
	if (NumLayerSelected == Value)
	{
		return true;
	}
	return false;
}

void AChallengerBoxLayerDeviceManager::UpdateAssetsChoice(FAssetCardinalDirections Direction)
{
	AChallengerBoxLayeringDevice* LayeringDevice = GetLayerSelected();
	if (LayeringDevice)
	{
		DirectionChoiceSelected = Direction;
		LayeringDevice->SetDirectionSelected(Direction);
	}
}

void AChallengerBoxLayerDeviceManager::LayerSpawn(int32 NumChannel, int32 NumLayer, TSubclassOf<AChallengerBoxLayeringDevice> Layer)
{
	
	AChallengerBoxLayeringDevice* LayerSpawned = GetWorld()->SpawnActor<AChallengerBoxLayeringDevice>(Layer);
	MapLayeringDevices.Add(NumLayer, LayerSpawned);
	LayeringDevices.Add(LayerSpawned);
	LayerSpawned->SetActorTransform(this->GetActorTransform());
	LayerSpawned->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	LayerSpawned->SetStartValuesLayerDeviceManager(this, BoxDeviceClass, true, NumChannel, NumLayer, NumRoomsBuildingX, NumRoomsBuildingY, NumRoomsBuildingZ);
	LayerSpawned->LayerSpawn();

}

void AChallengerBoxLayerDeviceManager::LayerUpdate(int32 NumChannel, int32 NumLayer, AChallengerBoxLayeringDevice* Layer)
{
	if (Layer)
	{
		MapLayeringDevices.Add(NumLayer, Layer);
		LayeringDevices.Add(Layer);
		Layer->SetActorTransform(this->GetActorTransform());
		Layer->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		Layer->SetStartValuesLayerDeviceManager(this, BoxDeviceClass, true, NumChannel, NumLayer, NumRoomsBuildingX, NumRoomsBuildingY, NumRoomsBuildingZ);
		Layer->LayerUpdate();
	}
}

void AChallengerBoxLayerDeviceManager::UpdateLayeringDevicesByChannel()
{
	MapLayeringDevicesByChannel.Empty();
	for (AChallengerBoxLayeringDevice* Layer : LayeringDevices)
	{
		FBoxLayeringDeviceAndChannel DeviceAndChannel;
		DeviceAndChannel.LayerValue = Layer->GetNumLayerDevice();
		DeviceAndChannel.BoxLayeringDevice = Layer;
		FBoxLayeringDevice& LayeringDevice = MapLayeringDevicesByChannel.FindOrAdd(Layer->GetNumChannelDevice());
		LayeringDevice.LayeringDeviceAndChannel.Add(DeviceAndChannel);
	}
}

void AChallengerBoxLayerDeviceManager::HideAlllayers()
{
	for (AChallengerBoxLayeringDevice* LayerDevice : LayeringDevices)
	{
		LayerDevice->HideAllBox();
	}
}

void AChallengerBoxLayerDeviceManager::UpdateLayerAndBoxSelected()
{
	if (AChallengerBoxLayeringDevice* LayeringDevice = GetLayerSelected())
	{
		LayeringDevice->UpdateBoxSelected();
	}
}

AChallengerBoxLayeringDevice* AChallengerBoxLayerDeviceManager::GetLayerSelected()
{
	
	if(AChallengerBoxLayeringDevice** LayeringDevicePtr = MapLayeringDevices.Find(NumLayerSelected))
	{
		return *LayeringDevicePtr;
	}
	return nullptr;
}

void AChallengerBoxLayerDeviceManager::UpdateSwitchMarkInsertedAssets()
{
	if (NumSwitchMarkAssets == 0)
	{
		for (AChallengerBoxLayeringDevice* LayerDevice : LayeringDevices)
		{
			LayerDevice->ClearMarkInsertedAssetsInBoxSelected();
		}
	}
	if (NumSwitchMarkAssets == 1)
	{
		for (AChallengerBoxLayeringDevice* LayerDevice : LayeringDevices)
		{
			LayerDevice->ClearMarkInsertedAssetsInBoxSelected();
		}
		AChallengerBoxLayeringDevice* LayeringDevice = GetLayerSelected();
		LayeringDevice->MarkInsertedAssetsInBoxSelected();
	}
	if (NumSwitchMarkAssets == 2)
	{
		for (AChallengerBoxLayeringDevice* LayerDevice : LayeringDevices)
		{
			LayerDevice->ClearMarkInsertedAssetsInBoxSelected();
		}
		AChallengerBoxLayeringDevice* LayeringDevice = GetLayerSelected();
		LayeringDevice->MarkInsertedAssetsInLayer();
	}
}
