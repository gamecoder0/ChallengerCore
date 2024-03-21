// Fill out your copyright notice in the Description page of Project Settings.


#include "Editor/ChallengerBoxLayeringDevice.h"
#include "Editor/ChallengerBoxLayerDeviceManager.h"
#include "Editor/ChallengerBoxDevice.h"
#include "Editor/ChallengerBoxDeviceAssetsCurrent.h"
#include "EditorUtilityWidget.h"


// Sets default values
AChallengerBoxLayeringDevice::AChallengerBoxLayeringDevice()
{
	PrimaryActorTick.bCanEverTick = false;
	NumRoomsBuildingX = 1;
	NumRoomsBuildingY = 1;
	NumRoomsBuildingZ = 1;
	bIsLayerSelected = false;
	AmountLayersByChannel = 1;
}

TArray<FVector> AChallengerBoxLayeringDevice::GetBuildingPositions(int32 RoomsBuildingX, int32 RoomsBuildingY, int32 RoomsBuildingZ)
{
	int32 LocationX = 0;
	int32 LocationY = 0;
	int32 LocationZ = 0;
	TArray<FVector> Locations;
	FVector LocDimencion, IncreaseLocations;
	LocDimencion = GetBuildingPositionsUnits(RoomsBuildingX, RoomsBuildingY, RoomsBuildingZ);
	int32 LenUnitis = trunc(RoomsBuildingX * RoomsBuildingY * RoomsBuildingZ);

	for (int32 i = 0; i < LenUnitis; i++)
	{
		IncreaseLocations = FVector(LocationX, LocationY, LocationZ);
		Locations.Add(IncreaseLocations);
		if (LocationX < LocDimencion.X)
		{
			LocationX++;
		}
		else
		{
			LocationX = 0;
			if (LocationY < LocDimencion.Y)
			{
				LocationY++;
			}
			else
			{
				LocationY = 0;
				if (LocationZ < LocDimencion.Z)
				{
					LocationZ++;
				}
			}
		}
	}

	return Locations;
}

void AChallengerBoxLayeringDevice::GeneratedBuildingBoxes()
{
	RemoveBuildingBoxes();
	TArray<FVector> BuildingPositions = GetBuildingPositions(NumRoomsBuildingX, NumRoomsBuildingY, NumRoomsBuildingZ);
	int32 NumBox = 0;
	for (FVector Positions : BuildingPositions)
	{
		BoxSpawn(Positions, NumBox);
		NumBox++;
	}
	UpdateBoxSelected();
}

void AChallengerBoxLayeringDevice::UpdateBuildingBoxes()
{
	TArray<AActor*> ChildActors;
	GetAttachedActors(ChildActors);
	
	if (ChildActors.Num() == 0)
	{
		GeneratedBuildingBoxes();
	}
	else
	{
		MapPositionsBoxDevice.Empty();
		AllBoxDevice.Empty();
		
		for (AActor* ChildActor : ChildActors)
		{
			AChallengerBoxDevice* ChildBox = Cast<AChallengerBoxDevice>(ChildActor);
			FBoxDataLayersList DataLayersListCurrent;
			if (ChildBox)
			{
				BoxUpdate(ChildBox);
			}
		}
		PositionsBoxSelected = FVector(0.f, 0.f, 0.f);
		UpdateBoxSelected();
	}
}

void AChallengerBoxLayeringDevice::GeneratedEditorUtilityWidget()
{
	if (DeviceAssetsCurrent)
	{
		TSubclassOf<UEditorUtilityWidget> UtilityWidgetClass = DeviceAssetsCurrent->SelectMeshUtilityClass;
		if (UtilityWidgetClass)
		{
			for (int32 i = 0; i < DeviceAssetsCurrent->AmountWidgetsToGenerate; i++)
			{
				UEditorUtilityWidget* NewUtilityWidget = CreateWidget<UEditorUtilityWidget>(GetWorld(), UtilityWidgetClass);
				if (NewUtilityWidget)
				{
					SelectMeshUtilityWidget.Add(NewUtilityWidget);
				}
			}
		}
	}
}

AChallengerBoxDevice* AChallengerBoxLayeringDevice::FindBoxDeviceSelected()
{
	AChallengerBoxDevice** BoxDevicePtr = MapPositionsBoxDevice.Find(PositionsBoxSelected);
	if (BoxDevicePtr)
	{
		AChallengerBoxDevice* BoxDevice = *BoxDevicePtr;
		return BoxDevice;
	}
	else
	{
		PositionsBoxSelected = FVector(0.f, 0.f, 0.f);
		BoxDevicePtr = MapPositionsBoxDevice.Find(PositionsBoxSelected);
		if (BoxDevicePtr)
		{
			AChallengerBoxDevice* BoxDevice = *BoxDevicePtr;
			return BoxDevice;
		}
	}

	return nullptr;
}

TArray<UEditorUtilityWidget*> AChallengerBoxLayeringDevice::GetSelectMeshUtilityWidget()
{
	return SelectMeshUtilityWidget;
}

UChallengerBoxDeviceAssetsCurrent* AChallengerBoxLayeringDevice::GetDeviceAssetsCurrent()
{
	if (DeviceAssetsCurrent)
	{
		return DeviceAssetsCurrent;
	}
	return nullptr;
}

void AChallengerBoxLayeringDevice::UpdateMeshInBox(FName ComponentName, int32 NumAsset, int32 NumAdditional)
{
	FName KeyGem = UChallengerBoxDeviceAssetsCurrent::GenerateKeyMapCurrentValues(ComponentName, NumAsset, NumAdditional);
	
	AChallengerBoxDevice* BoxDevice =  FindBoxDeviceSelected();
	if (BoxDevice)
	{
		if (DeviceAssetsCurrent)
		{
			int32 NumBox = BoxDevice->GetNumPositionBox();
			DeviceAssetsCurrent->UpdateDataBuildingClipboard(ComponentName, KeyGem, NumLayeringDevice, NumBox);
		}
		BoxDevice->UpdateMeshInBox(ComponentName, KeyGem);
	}
}

void AChallengerBoxLayeringDevice::SetClipboard(bool Undo)
{
	FBoxDataLayersList CurrentByLayer;
	if (DeviceAssetsCurrent)
	{
		DeviceAssetsCurrent->SetClipboard(Undo, NumLayeringDevice);
		CurrentByLayer = DeviceAssetsCurrent->FindDataBuildingCurrentByLayer(NumLayeringDevice);
	}
	for (AChallengerBoxDevice* BoxDevice : AllBoxDevice)
	{
		BoxDevice->ClearAllMeshComponents();
		if (!CurrentByLayer.IsEmpty)
		{
			int32 NumBox = BoxDevice->GetNumPositionBox();
			if(CurrentByLayer.MapNumBox.Contains(NumBox))
			{
				for (TPair<FName, FName> Pair : CurrentByLayer.MapNumBox[NumBox].MapComponentKey)
				{
					BoxDevice->UpdateMeshInBox(Pair.Key, Pair.Value);
				}
			}
		}
	}
}

void AChallengerBoxLayeringDevice::UpdateSave()
{
	if (DeviceAssetsCurrent)
	{
		for (AChallengerBoxDevice* BoxDevice : AllBoxDevice)
		{
			for (TPair<FName, FName> Pair : BoxDevice->GetMapComponentAndKey())
			{
				DeviceAssetsCurrent->UpdateSave(NumLayeringDevice, BoxDevice->GetNumRoomsBox(), Pair.Value);
			}
			DeviceAssetsCurrent->UpdateDataBuildingClipboard(BoxDevice->GetMapComponentAndKey(), NumLayeringDevice, BoxDevice->GetNumPositionBox());
		}
	}
}

void AChallengerBoxLayeringDevice::UpdateLoad()
{
	if (DeviceAssetsCurrent)
	{
		TArray<FName> KeysMap;
		TMap<FName, FName> MapComponentKey;
		for (AChallengerBoxDevice* BoxDevice : AllBoxDevice)
		{
			FVector BoxLocation = BoxDevice->GetNumRoomsBox();
			KeysMap.Empty();
			KeysMap = DeviceAssetsCurrent->GetMapLoad(NumLayeringDevice, BoxLocation);

			for (FName KeyMap : KeysMap)
			{
				FName ComponentTag = UChallengerBoxDeviceAssetsCurrent::ConvertCompotentTagOfKeyMap(KeyMap);
				BoxDevice->UpdateMeshInBox(ComponentTag, KeyMap);
			}
			DeviceAssetsCurrent->UpdateDataBuildingClipboard(BoxDevice->GetMapComponentAndKey(), NumLayeringDevice, BoxDevice->GetNumPositionBox());
		}
	}
}

void AChallengerBoxLayeringDevice::UpdateBake()
{
	UE_LOG(LogTemp, Warning, TEXT("UpdateBake"));
	if (DeviceAssetsCurrent)
	{
		TArray<FName> KeysMap;
		TMap<FName, FName> MapComponentKey;
		for (AChallengerBoxDevice* BoxDevice : AllBoxDevice)
		{
			BoxDevice->BakeMeshToLevel(PathSpawnMesh);
		}
	}
}

void AChallengerBoxLayeringDevice::MarkInsertedAssetsInBoxSelected()
{
	AChallengerBoxDevice* BoxDevice = FindBoxDeviceSelected();
	BoxDevice->MarkInsertedAssets(true);
}

void AChallengerBoxLayeringDevice::MarkInsertedAssetsInLayer()
{
	for (AChallengerBoxDevice* BoxDevice : AllBoxDevice)
	{
		BoxDevice->MarkInsertedAssets(true);
	}
}

void AChallengerBoxLayeringDevice::ClearMarkInsertedAssetsInBoxSelected()
{
	for (AChallengerBoxDevice* BoxDevice : AllBoxDevice)
	{
		BoxDevice->ClearMarkInsertedAssets();
	}
}

void AChallengerBoxLayeringDevice::RemoveBuildingBoxes()
{
	for (AChallengerBoxDevice* BoxDevice : AllBoxDevice)
	{
		BoxDevice->Destroy();
	}
	MapPositionsBoxDevice.Empty();
	AllBoxDevice.Empty();
	TArray<AActor*> ChildActors;
	GetAttachedActors(ChildActors);

	for (AActor* ChildActor : ChildActors)
	{
		AChallengerBoxDevice* ChildBoxGenerate = Cast<AChallengerBoxDevice>(ChildActor);
		if (ChildBoxGenerate && ChildBoxGenerate->IsValidLowLevelFast(true))
		{
			ChildBoxGenerate->Destroy();
		}
	}
}

void AChallengerBoxLayeringDevice::SetNumLayeringDevice(int32 NumLayer)
{
	NumLayeringDevice = NumLayer;
}

int32 AChallengerBoxLayeringDevice::GetNumChannelDevice()
{
	return NumChannelDevice;
}

int32 AChallengerBoxLayeringDevice::GetNumLayerDevice()
{
	return NumLayeringDevice;
}

void AChallengerBoxLayeringDevice::SetPositionsBoxSelected(FVector Position)
{
	PositionsBoxSelected = Position;
}

void AChallengerBoxLayeringDevice::HideAllBox()
{
	for (AChallengerBoxDevice* Box : AllBoxDevice)
	{
		Box->SetSelectedBox(false);
	}
}

void AChallengerBoxLayeringDevice::SetDirectionSelected(FAssetCardinalDirections Direction)
{
	AChallengerBoxDevice* BoxDevice = FindBoxDeviceSelected();
	if (BoxDevice)
	{
		BoxDevice->SetDirectionSelected(Direction);
	}
	else 
	{
		UpdateBoxSelected();
		BoxDevice = FindBoxDeviceSelected();
		if (BoxDevice)
		{
			BoxDevice->SetDirectionSelected(Direction);
		}
	}
}

void AChallengerBoxLayeringDevice::UpdateBoxSelected()
{
	AChallengerBoxDevice* BoxDevice = FindBoxDeviceSelected();
	if (BoxDevice)
	{
		if (bIsLayerSelected)
		{
			BoxDevice->SetSelectedBox(true);
		}
		else
		{
			BoxDevice->SetSelectedBox(false);
		}
	}
}

void AChallengerBoxLayeringDevice::BoxSpawn(FVector Position, int32 BoxNum)
{
	if (BoxDeviceClass && DeviceAssetsCurrent)
	{
		AChallengerBoxDevice* BoxGenerate = GetWorld()->SpawnActor<AChallengerBoxDevice>(BoxDeviceClass);
		FVector Location = GenerateDimensions(Position);
		BoxGenerate->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		BoxGenerate->SetActorLocation(Location);
		BoxGenerate->SetDefaultConfig(DeviceAssetsCurrent, Position.X, Position.Y, Position.Z, BoxNum);
		MapPositionsBoxDevice.Add(Position, BoxGenerate);
		AllBoxDevice.Add(BoxGenerate);
	}
}

void AChallengerBoxLayeringDevice::BoxUpdate(AChallengerBoxDevice* BoxDevice)
{
	if (BoxDevice && DeviceAssetsCurrent)
	{
		FVector Location = GenerateDimensions(BoxDevice->GetNumRoomsBox());
		BoxDevice->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		BoxDevice->SetActorLocation(Location);
		MapPositionsBoxDevice.Add(BoxDevice->GetNumRoomsBox(), BoxDevice);
		AllBoxDevice.Add(BoxDevice);
		for(TPair<FName, FName> Pair : BoxDevice->GetMapComponentAndKey())
		{
			DeviceAssetsCurrent->AddDataLayersList(NumLayeringDevice, BoxDevice->GetNumPositionBox(), Pair.Key, Pair.Value);
		}
	}
}

FVector AChallengerBoxLayeringDevice::GenerateDimensions(FVector BoxPosition)
{
	FVector Dimensions;
	if(DeviceAssetsCurrent)
	{
		Dimensions = (BoxPosition * DeviceAssetsCurrent->GetBaseLength()) + this->GetActorLocation();
	}
	return Dimensions;
}

FVector AChallengerBoxLayeringDevice::GetBuildingPositionsUnits(int32 RoomsBuildingX, int32 RoomsBuildingY, int32 RoomsBuildingZ)
{
	FVector BuildingPositions = FVector(RoomsBuildingX - 1, RoomsBuildingY - 1, RoomsBuildingZ - 1);
	return BuildingPositions;
}

FVector AChallengerBoxLayeringDevice::GetPositionsBoxSelected()
{
	return PositionsBoxSelected;
}

void AChallengerBoxLayeringDevice::UpdateBoxSelectedAndHide()
{
	if(DeviceAssetsCurrent)
	{
		DeviceAssetsCurrent->UpdateData();
	}
	HideAllBox();
	UpdateBuildingBoxes();
	DeviceAssetsCurrent->UpdateData();
}

void AChallengerBoxLayeringDevice::LayerSpawn()
{
	GeneratedBuildingBoxes();
	if (DeviceAssetsCurrent)
	{
		DeviceAssetsCurrent->ClearDataBuilding();
	}
}

void AChallengerBoxLayeringDevice::LayerUpdate()
{
	UpdateBoxSelectedAndHide();
}

void AChallengerBoxLayeringDevice::SetStartValuesLayerDeviceManager(AChallengerBoxLayerDeviceManager* DeviceManager, TSubclassOf<AChallengerBoxDevice> BoxClass, bool bLayerSelected, int32 NumChannel, int32 NumLayer, int32 DimensionsX, int32 DimensionsY, int32 DimensionsZ)
{
	LayerDeviceManager = DeviceManager;
	BoxDeviceClass = BoxClass;
	bIsLayerSelected = bLayerSelected;
	NumChannelDevice = NumChannel;
	NumLayeringDevice = NumLayer;
	NumRoomsBuildingX = DimensionsX;
	NumRoomsBuildingY = DimensionsY;
	NumRoomsBuildingZ = DimensionsZ;
	GeneratedEditorUtilityWidget();
}
