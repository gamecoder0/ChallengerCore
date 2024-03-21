// Fill out your copyright notice in the Description page of Project Settings.


#include "Editor/ChallengerBoxDeviceAssets.h"


UChallengerBoxDeviceAssets::UChallengerBoxDeviceAssets()
{
	BaseLength = FVector(684.615, 684.615, 684.615);
	bButtonsEnable = false;
}

void UChallengerBoxDeviceAssets::PostLoad()
{
    Super::PostLoad();
    UpdateAssetName();
	UpdateComponentsData();
}

void UChallengerBoxDeviceAssets::UpdateAssets()
{
    UpdateAssetName();
	UpdateComponentsData();
	UpdateTransformAdjustments();
	this->SaveConfig();
}

void UChallengerBoxDeviceAssets::WriteDataTable()
{
	if(bButtonsEnable)
	{
		if (BoxDeviceAssetsDataTable && BoxDeviceAssetsDataTable->RowStruct == TBaseStructure<FBoxDeviceAssetsDataTable>::Get())
		{
			FBoxDeviceAssetsDataTable* ExistingRow = BoxDeviceAssetsDataTable->FindRow<FBoxDeviceAssetsDataTable>(this->GetFName(), "");

			if (ExistingRow)
			{
				ExistingRow->ParametersDeviceAssets = ParametersDeviceAssets;
				ExistingRow->MapComponentData = MapComponentData;
				UE_LOG(LogTemp, Display, TEXT("Row with name '%s' already exists. Overwriting."), *(this->GetFName().ToString()));
			}
			else
			{
				FBoxDeviceAssetsDataTable NewRow;
				NewRow.ParametersDeviceAssets = ParametersDeviceAssets;
				NewRow.MapComponentData = MapComponentData;
				BoxDeviceAssetsDataTable->AddRow(this->GetFName(), NewRow);
				UE_LOG(LogTemp, Display, TEXT("Row with name '%s' does not exist. Creating new row."), *(this->GetFName().ToString()));
			}

		}
	}
}

void UChallengerBoxDeviceAssets::ReadDataTable()
{
	if (bButtonsEnable)
	{
		if (BoxDeviceAssetsDataTable && BoxDeviceAssetsDataTable->RowStruct == TBaseStructure<FBoxDeviceAssetsDataTable>::Get())
		{
			FBoxDeviceAssetsDataTable* DataRow = BoxDeviceAssetsDataTable->FindRow<FBoxDeviceAssetsDataTable>(this->GetFName(), "");
			if (DataRow)
			{
				ParametersDeviceAssets = DataRow->ParametersDeviceAssets;
				MapComponentData = DataRow->MapComponentData;
				UE_LOG(LogTemp, Display, TEXT("Row with name '%s' already exists. Overwriting."), *(this->GetFName().ToString()));
			}
			else
			{
				UE_LOG(LogTemp, Display, TEXT("Row with name '%s' does not exist. Creating new row."), *(this->GetFName().ToString()));
			}
		}
	}
}

TArray<EBoxComponentsTags> UChallengerBoxDeviceAssets::GetComponentsTagsByDirection(FAssetCardinalDirections Direction)
{
	TArray<EBoxComponentsTags> ComponentsTags;
	switch (Direction)
	{
	case FAssetCardinalDirections::Default:
		ComponentsTags.Add(EBoxComponentsTags::Default);
		break;

	case FAssetCardinalDirections::North:
	case FAssetCardinalDirections::NorthLeft:
	case FAssetCardinalDirections::NorthRight:
		ComponentsTags.Add(EBoxComponentsTags::DownNorthComponent);
		ComponentsTags.Add(EBoxComponentsTags::DownNorthLeftComponent);
		ComponentsTags.Add(EBoxComponentsTags::DownNorthRightComponent);
		ComponentsTags.Add(EBoxComponentsTags::TopNorthComponent);
		ComponentsTags.Add(EBoxComponentsTags::TopNorthLeftComponent);
		ComponentsTags.Add(EBoxComponentsTags::TopNorthRightComponent);
		break;

	case FAssetCardinalDirections::South:
	case FAssetCardinalDirections::SouthLeft:
	case FAssetCardinalDirections::SouthRight:
		ComponentsTags.Add(EBoxComponentsTags::DownSouthComponent);
		ComponentsTags.Add(EBoxComponentsTags::DownSouthLeftComponent);
		ComponentsTags.Add(EBoxComponentsTags::DownSouthRightComponent);
		ComponentsTags.Add(EBoxComponentsTags::TopSouthComponent);
		ComponentsTags.Add(EBoxComponentsTags::TopSouthLeftComponent);
		ComponentsTags.Add(EBoxComponentsTags::TopSouthRightComponent);
		break;

	case FAssetCardinalDirections::East:
	case FAssetCardinalDirections::EastLeft:
	case FAssetCardinalDirections::EastRight:
		ComponentsTags.Add(EBoxComponentsTags::DownEastComponent);
		ComponentsTags.Add(EBoxComponentsTags::DownEastLeftComponent);
		ComponentsTags.Add(EBoxComponentsTags::DownEastRightComponent);
		ComponentsTags.Add(EBoxComponentsTags::TopEastComponent);
		ComponentsTags.Add(EBoxComponentsTags::TopEastLeftComponent);
		ComponentsTags.Add(EBoxComponentsTags::TopEastRightComponent);
		break;

	case FAssetCardinalDirections::West:
	case FAssetCardinalDirections::WestLeft:
	case FAssetCardinalDirections::WestRight:
		ComponentsTags.Add(EBoxComponentsTags::DownWestComponent);
		ComponentsTags.Add(EBoxComponentsTags::DownWestLeftComponent);
		ComponentsTags.Add(EBoxComponentsTags::DownWestRightComponent);
		ComponentsTags.Add(EBoxComponentsTags::TopWestComponent);
		ComponentsTags.Add(EBoxComponentsTags::TopWestLeftComponent);
		ComponentsTags.Add(EBoxComponentsTags::TopWestRightComponent);
		break;

	case FAssetCardinalDirections::Center:
		ComponentsTags.Add(EBoxComponentsTags::DownComponent);
		ComponentsTags.Add(EBoxComponentsTags::TopComponent);
		break;

	default:
		break;
	}
	return ComponentsTags;
}

TArray<FName> UChallengerBoxDeviceAssets::GetNameAsstes(EBoxComponentsTags ComponentEnum)
{
	FBoxDeviceComponentData* ComponentDataPtr = MapComponentData.Find(ComponentEnum);
	if(ComponentDataPtr)
	{
		return ComponentDataPtr->Assets;
	}
	return TArray<FName>();
}

void UChallengerBoxDeviceAssets::UpdateTransformAdjustments()
{
	UE_LOG(LogTemp, Warning, TEXT("UpdateTransformAdjustments"));
	for (TPair<FName, FBoxDeviceAssetsData>& Pair : ParametersDeviceAssets)
	{
		FBoxDeviceAssetsData& AssetsData = Pair.Value;
		if (AssetsData.TransformAdjustments.Num() == 0)
		{
			FBoxAssetsAdjustments Adjustments;
			Adjustments.Location = FVector();
			Adjustments.Rotation = FRotator();
			AssetsData.TransformAdjustments.Add(Adjustments);
			UE_LOG(LogTemp, Warning, TEXT("Add Adjustments"));
		}
	}
}



void UChallengerBoxDeviceAssets::UpdateAssetName()
{
    for (TPair<FName, FBoxDeviceAssetsData>& Pair : ParametersDeviceAssets)
    {
        Pair.Value.AssetName = Pair.Key;
    }
}

void UChallengerBoxDeviceAssets::UpdateComponentsData()
{
	for (TPair<EBoxComponentsTags, FBoxDeviceComponentData> Pair : MapComponentData)
	{
		UpdateComponentData(Pair.Key);
	}
}

void UChallengerBoxDeviceAssets::UpdateComponentData(EBoxComponentsTags ComponentEnum)
{

    FBoxDeviceComponentData ComponentData;
	
	if (MapComponentData.Contains(ComponentEnum))
	{
		FBoxDeviceComponentData* ComponentDataPtr = MapComponentData.Find(ComponentEnum);
		switch (ComponentEnum)
		{
		case EBoxComponentsTags::BoxSelected:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::BoxSelected).ToString());
			ComponentData.Positions = FBoxPositions::Down;
			ComponentData.CardinalDirection = FAssetCardinalDirections::Default;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, 0.f));
			ComponentData.BaseTransform.SetScale3D(BaseLength / 100);
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			ComponentData.Assets = ComponentDataPtr->Assets;
			MapComponentData[ComponentEnum] = ComponentData;
			break;
		case EBoxComponentsTags::DownComponent:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::DownComponent).ToString());
			ComponentData.Positions = FBoxPositions::Down;
			ComponentData.CardinalDirection = FAssetCardinalDirections::Default;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, 0.f));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			ComponentData.Assets = ComponentDataPtr->Assets;
			MapComponentData[ComponentEnum] = ComponentData;
			break;
		case EBoxComponentsTags::DownNorthComponent:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::DownNorthComponent).ToString());
			ComponentData.Positions = FBoxPositions::DownNorth;
			ComponentData.CardinalDirection = FAssetCardinalDirections::North;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, 0.f));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			ComponentData.Assets = ComponentDataPtr->Assets;
			MapComponentData[ComponentEnum] = ComponentData;
			break;
		case EBoxComponentsTags::DownEastComponent:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::DownEastComponent).ToString());
			ComponentData.Positions = FBoxPositions::DownEast;
			ComponentData.CardinalDirection = FAssetCardinalDirections::East;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, 0.f));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			if (ComponentData.GenDataToCardinal)
			{
				ComponentData.Assets = GetNameAsstes(EBoxComponentsTags::DownNorthComponent);
				MapComponentData[ComponentEnum] = ComponentData;
			}
			else
			{
				ComponentData.Assets = ComponentDataPtr->Assets;
				MapComponentData[ComponentEnum] = ComponentData;
			}
			break;
		case EBoxComponentsTags::DownSouthComponent:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::DownSouthComponent).ToString());
			ComponentData.Positions = FBoxPositions::DownSouth;
			ComponentData.CardinalDirection = FAssetCardinalDirections::South;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, 0.f));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			if (ComponentData.GenDataToCardinal)
			{
				ComponentData.Assets = GetNameAsstes(EBoxComponentsTags::DownNorthComponent);
				MapComponentData[ComponentEnum] = ComponentData;
			}
			else
			{
				ComponentData.Assets = ComponentDataPtr->Assets;
				MapComponentData[ComponentEnum] = ComponentData;
			}
			break;
		case EBoxComponentsTags::DownWestComponent:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::DownWestComponent).ToString());
			ComponentData.Positions = FBoxPositions::DownWest;
			ComponentData.CardinalDirection = FAssetCardinalDirections::West;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, 0.f));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			if (ComponentData.GenDataToCardinal)
			{
				ComponentData.Assets = GetNameAsstes(EBoxComponentsTags::DownNorthComponent);
				MapComponentData[ComponentEnum] = ComponentData;
			}
			else
			{
				ComponentData.Assets = ComponentDataPtr->Assets;
				MapComponentData[ComponentEnum] = ComponentData;
			}
			break;
		case EBoxComponentsTags::DownNorthLeftComponent:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::DownNorthLeftComponent).ToString());
			ComponentData.Positions = FBoxPositions::DownNorthLeft;
			ComponentData.CardinalDirection = FAssetCardinalDirections::NorthLeft;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, 0.f));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			ComponentData.Assets = ComponentDataPtr->Assets;
			MapComponentData[ComponentEnum] = ComponentData;
			break;
		case EBoxComponentsTags::DownEastLeftComponent:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::DownEastLeftComponent).ToString());
			ComponentData.Positions = FBoxPositions::DownEastLeft;
			ComponentData.CardinalDirection = FAssetCardinalDirections::EastLeft;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, 0.f));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			if (ComponentData.GenDataToCardinal)
			{
				ComponentData.Assets = GetNameAsstes(EBoxComponentsTags::DownNorthLeftComponent);
				MapComponentData[ComponentEnum] = ComponentData;
			}
			else
			{
				ComponentData.Assets = ComponentDataPtr->Assets;
				MapComponentData[ComponentEnum] = ComponentData;
			}
			break;
		case EBoxComponentsTags::DownSouthLeftComponent:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::DownSouthLeftComponent).ToString());
			ComponentData.Positions = FBoxPositions::DownSouthLeft;
			ComponentData.CardinalDirection = FAssetCardinalDirections::SouthLeft;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, 0.f));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			if (ComponentData.GenDataToCardinal)
			{
				ComponentData.Assets = GetNameAsstes(EBoxComponentsTags::DownNorthLeftComponent);
				MapComponentData[ComponentEnum] = ComponentData;
			}
			else
			{
				ComponentData.Assets = ComponentDataPtr->Assets;
				MapComponentData[ComponentEnum] = ComponentData;
			}
			break;
		case EBoxComponentsTags::DownWestLeftComponent:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::DownWestLeftComponent).ToString());
			ComponentData.Positions = FBoxPositions::DownWestLeft;
			ComponentData.CardinalDirection = FAssetCardinalDirections::WestLeft;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, 0.f));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			if (ComponentData.GenDataToCardinal)
			{
				ComponentData.Assets = GetNameAsstes(EBoxComponentsTags::DownNorthLeftComponent);
				MapComponentData[ComponentEnum] = ComponentData;
			}
			else
			{
				ComponentData.Assets = ComponentDataPtr->Assets;
				MapComponentData[ComponentEnum] = ComponentData;
			}
			break;
		case EBoxComponentsTags::DownNorthRightComponent:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::DownNorthRightComponent).ToString());
			ComponentData.Positions = FBoxPositions::DownNorthRight;
			ComponentData.CardinalDirection = FAssetCardinalDirections::NorthRight;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, 0.f));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			ComponentData.Assets = ComponentDataPtr->Assets;
			MapComponentData[ComponentEnum] = ComponentData;
			break;
		case EBoxComponentsTags::DownEastRightComponent:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::DownEastRightComponent).ToString());
			ComponentData.Positions = FBoxPositions::DownEastRight;
			ComponentData.CardinalDirection = FAssetCardinalDirections::EastRight;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, 0.f));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			if (ComponentData.GenDataToCardinal)
			{
				ComponentData.Assets = GetNameAsstes(EBoxComponentsTags::DownNorthRightComponent);
				MapComponentData[ComponentEnum] = ComponentData;
			}
			else
			{
				ComponentData.Assets = ComponentDataPtr->Assets;
				MapComponentData[ComponentEnum] = ComponentData;
			}
			break;
		case EBoxComponentsTags::DownSouthRightComponent:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::DownSouthRightComponent).ToString());
			ComponentData.Positions = FBoxPositions::DownSouthRight;
			ComponentData.CardinalDirection = FAssetCardinalDirections::SouthRight;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, 0.f));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			if (ComponentData.GenDataToCardinal)
			{
				ComponentData.Assets = GetNameAsstes(EBoxComponentsTags::DownNorthRightComponent);
				MapComponentData[ComponentEnum] = ComponentData;
			}
			else
			{
				ComponentData.Assets = ComponentDataPtr->Assets;
				MapComponentData[ComponentEnum] = ComponentData;
			};
			break;
		case EBoxComponentsTags::DownWestRightComponent:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::DownWestRightComponent).ToString());
			ComponentData.Positions = FBoxPositions::DownWestRight;
			ComponentData.CardinalDirection = FAssetCardinalDirections::WestRight;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, 0.f));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			if (ComponentData.GenDataToCardinal)
			{
				ComponentData.Assets = GetNameAsstes(EBoxComponentsTags::DownNorthRightComponent);
				MapComponentData[ComponentEnum] = ComponentData;
			}
			else
			{
				ComponentData.Assets = ComponentDataPtr->Assets;
				MapComponentData[ComponentEnum] = ComponentData;
			}
			break;
		case EBoxComponentsTags::TopComponent:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::TopComponent).ToString());
			ComponentData.Positions = FBoxPositions::Top;
			ComponentData.CardinalDirection = FAssetCardinalDirections::Default;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, BaseLength.Z));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			ComponentData.Assets = ComponentDataPtr->Assets;
			MapComponentData[ComponentEnum] = ComponentData;
			break;
		case EBoxComponentsTags::TopNorthComponent:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::TopNorthComponent).ToString());
			ComponentData.Positions = FBoxPositions::TopNorth;
			ComponentData.CardinalDirection = FAssetCardinalDirections::North;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, BaseLength.Z));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			ComponentData.Assets = ComponentDataPtr->Assets;
			MapComponentData[ComponentEnum] = ComponentData;
			break;
		case EBoxComponentsTags::TopEastComponent:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::TopEastComponent).ToString());
			ComponentData.Positions = FBoxPositions::TopEast;
			ComponentData.CardinalDirection = FAssetCardinalDirections::East;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, BaseLength.Z));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			if (ComponentData.GenDataToCardinal)
			{
				ComponentData.Assets = GetNameAsstes(EBoxComponentsTags::TopNorthComponent);
				MapComponentData[ComponentEnum] = ComponentData;
			}
			else
			{
				ComponentData.Assets = ComponentDataPtr->Assets;
				MapComponentData[ComponentEnum] = ComponentData;
			}
			break;
		case EBoxComponentsTags::TopSouthComponent:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::TopSouthComponent).ToString());
			ComponentData.Positions = FBoxPositions::TopSouth;
			ComponentData.CardinalDirection = FAssetCardinalDirections::South;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, BaseLength.Z));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			if (ComponentData.GenDataToCardinal)
			{
				ComponentData.Assets = GetNameAsstes(EBoxComponentsTags::TopNorthComponent);
				MapComponentData[ComponentEnum] = ComponentData;
			}
			else
			{
				ComponentData.Assets = ComponentDataPtr->Assets;
				MapComponentData[ComponentEnum] = ComponentData;
			}
			break;
		case EBoxComponentsTags::TopWestComponent:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::TopWestComponent).ToString());
			ComponentData.Positions = FBoxPositions::TopWest;
			ComponentData.CardinalDirection = FAssetCardinalDirections::West;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, BaseLength.Z));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			if (ComponentData.GenDataToCardinal)
			{
				ComponentData.Assets = GetNameAsstes(EBoxComponentsTags::TopNorthComponent);
				MapComponentData[ComponentEnum] = ComponentData;
			}
			else
			{
				ComponentData.Assets = ComponentDataPtr->Assets;
				MapComponentData[ComponentEnum] = ComponentData;
			}
			break;
		case EBoxComponentsTags::TopNorthLeftComponent:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::TopNorthLeftComponent).ToString());
			ComponentData.Positions = FBoxPositions::TopNorthLeft;
			ComponentData.CardinalDirection = FAssetCardinalDirections::NorthLeft;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, BaseLength.Z));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			ComponentData.Assets = ComponentDataPtr->Assets;
			MapComponentData[ComponentEnum] = ComponentData;
			break;
		case EBoxComponentsTags::TopEastLeftComponent:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::TopEastLeftComponent).ToString());
			ComponentData.Positions = FBoxPositions::TopEastLeft;
			ComponentData.CardinalDirection = FAssetCardinalDirections::EastLeft;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, BaseLength.Z));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			if (ComponentData.GenDataToCardinal)
			{
				ComponentData.Assets = GetNameAsstes(EBoxComponentsTags::TopNorthLeftComponent);
				MapComponentData[ComponentEnum] = ComponentData;
			}
			else
			{
				ComponentData.Assets = ComponentDataPtr->Assets;
				MapComponentData[ComponentEnum] = ComponentData;
			}
			break;
		case EBoxComponentsTags::TopSouthLeftComponent:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::TopSouthLeftComponent).ToString());
			ComponentData.Positions = FBoxPositions::TopSouthLeft;
			ComponentData.CardinalDirection = FAssetCardinalDirections::SouthLeft;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, BaseLength.Z));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			if (ComponentData.GenDataToCardinal)
			{
				ComponentData.Assets = GetNameAsstes(EBoxComponentsTags::TopNorthLeftComponent);
				MapComponentData[ComponentEnum] = ComponentData;
			}
			else
			{
				ComponentData.Assets = ComponentDataPtr->Assets;
				MapComponentData[ComponentEnum] = ComponentData;
			}
			break;
		case EBoxComponentsTags::TopWestLeftComponent:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::TopWestLeftComponent).ToString());
			ComponentData.Positions = FBoxPositions::TopWestLeft;
			ComponentData.CardinalDirection = FAssetCardinalDirections::WestLeft;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, BaseLength.Z));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			if (ComponentData.GenDataToCardinal)
			{
				ComponentData.Assets = GetNameAsstes(EBoxComponentsTags::TopNorthLeftComponent);
				MapComponentData[ComponentEnum] = ComponentData;
			}
			else
			{
				ComponentData.Assets = ComponentDataPtr->Assets;
				MapComponentData[ComponentEnum] = ComponentData;
			}
			break;
		case EBoxComponentsTags::TopNorthRightComponent:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::TopNorthRightComponent).ToString());
			ComponentData.Positions = FBoxPositions::TopNorthRight;
			ComponentData.CardinalDirection = FAssetCardinalDirections::NorthRight;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, BaseLength.Z));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			ComponentData.Assets = ComponentDataPtr->Assets;
			MapComponentData[ComponentEnum] = ComponentData;
			break;
		case EBoxComponentsTags::TopEastRightComponent:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::TopEastRightComponent).ToString());
			ComponentData.Positions = FBoxPositions::TopEastRight;
			ComponentData.CardinalDirection = FAssetCardinalDirections::EastRight;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, BaseLength.Z));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			if (ComponentData.GenDataToCardinal)
			{
				ComponentData.Assets = GetNameAsstes(EBoxComponentsTags::TopNorthRightComponent);
				MapComponentData[ComponentEnum] = ComponentData;
			}
			else
			{
				ComponentData.Assets = ComponentDataPtr->Assets;
				MapComponentData[ComponentEnum] = ComponentData;
			}
			break;
		case EBoxComponentsTags::TopSouthRightComponent:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::TopSouthRightComponent).ToString());
			ComponentData.Positions = FBoxPositions::TopSouthRight;
			ComponentData.CardinalDirection = FAssetCardinalDirections::SouthRight;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, BaseLength.Z));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			if (ComponentData.GenDataToCardinal)
			{
				ComponentData.Assets = GetNameAsstes(EBoxComponentsTags::TopNorthRightComponent);
				MapComponentData[ComponentEnum] = ComponentData;
			}
			else
			{
				ComponentData.Assets = ComponentDataPtr->Assets;
				MapComponentData[ComponentEnum] = ComponentData;
			}
			break;
		case EBoxComponentsTags::TopWestRightComponent:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::TopWestRightComponent).ToString());
			ComponentData.Positions = FBoxPositions::TopWestRight;
			ComponentData.CardinalDirection = FAssetCardinalDirections::WestRight;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, BaseLength.Z));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			if (ComponentData.GenDataToCardinal)
			{
				ComponentData.Assets = GetNameAsstes(EBoxComponentsTags::TopNorthRightComponent);
				MapComponentData[ComponentEnum] = ComponentData;
			}
			else
			{
				ComponentData.Assets = ComponentDataPtr->Assets;
				MapComponentData[ComponentEnum] = ComponentData;
			}
			break;
		case EBoxComponentsTags::NorthSelected:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::NorthSelected).ToString());
			ComponentData.Positions = FBoxPositions::DownNorth;
			ComponentData.CardinalDirection = FAssetCardinalDirections::North;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, 0.f));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			ComponentData.Assets = ComponentDataPtr->Assets;
			MapComponentData[ComponentEnum] = ComponentData;
			break;
		case EBoxComponentsTags::SouthSelected:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::SouthSelected).ToString());
			ComponentData.Positions = FBoxPositions::DownSouth;
			ComponentData.CardinalDirection = FAssetCardinalDirections::South;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, 0.f));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			if (ComponentData.GenDataToCardinal)
			{
				ComponentData.Assets = GetNameAsstes(EBoxComponentsTags::NorthSelected);
				MapComponentData[ComponentEnum] = ComponentData;
			}
			else
			{
				ComponentData.Assets = ComponentDataPtr->Assets;
				MapComponentData[ComponentEnum] = ComponentData;
			}
			break;
		case EBoxComponentsTags::EastSelected:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::EastSelected).ToString());
			ComponentData.Positions = FBoxPositions::DownEast;
			ComponentData.CardinalDirection = FAssetCardinalDirections::East;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, 0.f));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			if (ComponentData.GenDataToCardinal)
			{
				ComponentData.Assets = GetNameAsstes(EBoxComponentsTags::NorthSelected);
				MapComponentData[ComponentEnum] = ComponentData;
			}
			else
			{
				ComponentData.Assets = ComponentDataPtr->Assets;
				MapComponentData[ComponentEnum] = ComponentData;
			}
			break;
		case EBoxComponentsTags::WestSelected:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::WestSelected).ToString());
			ComponentData.Positions = FBoxPositions::DownWest;
			ComponentData.CardinalDirection = FAssetCardinalDirections::West;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, 0.f));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			if (ComponentData.GenDataToCardinal)
			{
				ComponentData.Assets = GetNameAsstes(EBoxComponentsTags::NorthSelected);
				MapComponentData[ComponentEnum] = ComponentData;
			}
			else
			{
				ComponentData.Assets = ComponentDataPtr->Assets;
				MapComponentData[ComponentEnum] = ComponentData;
			}
			break;
		case EBoxComponentsTags::CenterSelected:
			ComponentData.BoxComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::CenterSelected).ToString());
			ComponentData.Positions = FBoxPositions::Down;
			ComponentData.CardinalDirection = FAssetCardinalDirections::Center;
			ComponentData.BaseTransform.SetLocation(FVector(0.f, 0.f, 0.f));
			ComponentData.GenDataToCardinal = ComponentDataPtr->GenDataToCardinal;
			ComponentData.Assets = ComponentDataPtr->Assets;
			MapComponentData[ComponentEnum] = ComponentData;
			break;
		default:
			break;
		}
	}	
}

FTransform UChallengerBoxDeviceAssets::GenerateTransforElement(FAssetCardinalDirections Direction, FTransform BaseTransform, FBoxAssetsAdjustments TransformAdjustments, FVector BaseLength)
{
	FTransform ElementTransform;
	float LocationX, LocationY, LocationZ;
	FQuat BaseRotation = BaseTransform.GetRotation() * FQuat(TransformAdjustments.Rotation);
	FVector LocationAdjustments = TransformAdjustments.Location;
	switch (Direction)
	{
	case FAssetCardinalDirections::North:
		LocationX = BaseTransform.GetLocation().X + (BaseLength.X / 2) + LocationAdjustments.X;
		LocationY = BaseTransform.GetLocation().Y + LocationAdjustments.Y;
		LocationZ = BaseTransform.GetLocation().Z + LocationAdjustments.Z;
		ElementTransform.SetRotation(BaseRotation);
		ElementTransform.SetLocation(FVector(LocationX, LocationY, LocationZ));
		break;
	case FAssetCardinalDirections::NorthLeft:
		LocationX = BaseTransform.GetLocation().X + LocationAdjustments.X;
		LocationY = BaseTransform.GetLocation().Y + LocationAdjustments.Y;
		LocationZ = BaseTransform.GetLocation().Z + LocationAdjustments.Z;
		ElementTransform.SetRotation(BaseRotation);
		ElementTransform.SetLocation(FVector(LocationX, LocationY, LocationZ));
		break;
	case FAssetCardinalDirections::NorthRight:
		LocationX = BaseTransform.GetLocation().X + BaseLength.X + LocationAdjustments.X;
		LocationY = BaseTransform.GetLocation().Y + LocationAdjustments.Y;
		LocationZ = BaseTransform.GetLocation().Z + LocationAdjustments.Z;
		ElementTransform.SetRotation(BaseRotation);
		ElementTransform.SetLocation(FVector(LocationX, LocationY, LocationZ));
		break;
	case FAssetCardinalDirections::South:
		LocationX = (BaseTransform.GetLocation().X + (BaseLength.X / 2)) - LocationAdjustments.X;
		LocationY = (BaseTransform.GetLocation().Y + BaseLength.Y) - LocationAdjustments.Y;
		LocationZ = BaseTransform.GetLocation().Z + LocationAdjustments.Z;
		ElementTransform.SetRotation(FQuat(FRotator(0.0f, 180.0f, 0.0f)) * BaseRotation);
		ElementTransform.SetLocation(FVector(LocationX, LocationY, LocationZ));
		break;
	case FAssetCardinalDirections::SouthLeft:
		LocationX = (BaseTransform.GetLocation().X + BaseLength.X) - LocationAdjustments.X;
		LocationY = (BaseTransform.GetLocation().Y + BaseLength.Y) - LocationAdjustments.Y;
		LocationZ = BaseTransform.GetLocation().Z + LocationAdjustments.Z;
		ElementTransform.SetRotation(FQuat(FRotator(0.0f, 180.0f, 0.0f)) * BaseRotation);
		ElementTransform.SetLocation(FVector(LocationX, LocationY, LocationZ));
		break;
	case FAssetCardinalDirections::SouthRight:
		LocationX = BaseTransform.GetLocation().X - LocationAdjustments.X;
		LocationY = (BaseTransform.GetLocation().Y + BaseLength.Y) - LocationAdjustments.Y;
		LocationZ = BaseTransform.GetLocation().Z + LocationAdjustments.Z;
		ElementTransform.SetRotation(FQuat(FRotator(0.0f, 180.0f, 0.0f)) * BaseRotation);
		ElementTransform.SetLocation(FVector(LocationX, LocationY, LocationZ));
		break;
	case FAssetCardinalDirections::East:
		LocationX = (BaseTransform.GetLocation().X + BaseLength.X) - LocationAdjustments.Y;
		LocationY = (BaseTransform.GetLocation().Y + (BaseLength.Y / 2)) + LocationAdjustments.X;
		LocationZ = BaseTransform.GetLocation().Z + LocationAdjustments.Z;
		ElementTransform.SetRotation(FQuat(FRotator(0.0f, 90, 0.0f)) * BaseRotation);
		ElementTransform.SetLocation(FVector(LocationX, LocationY, LocationZ));
		break;
	case FAssetCardinalDirections::EastLeft:
		LocationX = (BaseTransform.GetLocation().X + BaseLength.X) - LocationAdjustments.Y;
		LocationY = BaseTransform.GetLocation().Y + LocationAdjustments.X;
		LocationZ = BaseTransform.GetLocation().Z + LocationAdjustments.Z;
		ElementTransform.SetRotation(FQuat(FRotator(0.0f, 90, 0.0f)) * BaseRotation);
		ElementTransform.SetLocation(FVector(LocationX, LocationY, LocationZ));
		break;
	case FAssetCardinalDirections::EastRight:
		LocationX = (BaseTransform.GetLocation().X + BaseLength.X) - LocationAdjustments.Y;
		LocationY = (BaseTransform.GetLocation().Y + BaseLength.Y) + LocationAdjustments.X;
		LocationZ = BaseTransform.GetLocation().Z + LocationAdjustments.Z;
		ElementTransform.SetRotation(FQuat(FRotator(0.0f, 90, 0.0f)) * BaseRotation);
		ElementTransform.SetLocation(FVector(LocationX, LocationY, LocationZ));
		break;
	case FAssetCardinalDirections::West:
		LocationX = (BaseTransform.GetLocation().X) + LocationAdjustments.Y;
		LocationY = (BaseTransform.GetLocation().Y + (BaseLength.Y / 2)) - LocationAdjustments.X;
		LocationZ = BaseTransform.GetLocation().Z + LocationAdjustments.Z;
		ElementTransform.SetRotation(FQuat(FRotator(0.0f, -90, 0.0f)) * BaseRotation);
		ElementTransform.SetLocation(FVector(LocationX, LocationY, LocationZ));
		break;
	case FAssetCardinalDirections::WestLeft:
		LocationX = BaseTransform.GetLocation().X + LocationAdjustments.Y;
		LocationY = (BaseTransform.GetLocation().Y + BaseLength.Y) - LocationAdjustments.X;
		LocationZ = BaseTransform.GetLocation().Z + LocationAdjustments.Z;
		ElementTransform.SetRotation(FQuat(FRotator(0.0f, -90, 0.0f)) * BaseRotation);
		ElementTransform.SetLocation(FVector(LocationX, LocationY, LocationZ));
		break;
	case FAssetCardinalDirections::WestRight:
		LocationX = BaseTransform.GetLocation().X + LocationAdjustments.Y;
		LocationY = BaseTransform.GetLocation().Y - LocationAdjustments.X;
		LocationZ = BaseTransform.GetLocation().Z + LocationAdjustments.Z;
		ElementTransform.SetRotation(FQuat(FRotator(0.0f, -90, 0.0f)) * BaseRotation);
		ElementTransform.SetLocation(FVector(LocationX, LocationY, LocationZ));
		break;
	case FAssetCardinalDirections::Default:
	case FAssetCardinalDirections::Center:
		LocationX = (BaseTransform.GetLocation().X + (BaseLength.X / 2)) + LocationAdjustments.X;
		LocationY = (BaseTransform.GetLocation().Y + (BaseLength.Y / 2)) + LocationAdjustments.Y;
		LocationZ = BaseTransform.GetLocation().Z + LocationAdjustments.Z;
		ElementTransform.SetRotation(BaseRotation);
		ElementTransform.SetLocation(FVector(LocationX, LocationY, LocationZ));
		ElementTransform.SetScale3D(BaseTransform.GetScale3D());

	default:
		break;
	}

	return ElementTransform;
}
