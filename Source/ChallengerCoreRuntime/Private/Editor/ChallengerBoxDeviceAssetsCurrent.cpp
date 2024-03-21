// Fill out your copyright notice in the Description page of Project Settings.


#include "Editor/ChallengerBoxDeviceAssetsCurrent.h"

FVector UChallengerBoxDeviceAssetsCurrent::GetBaseLength()
{
    if(DeviceAsset)
    {
        return DeviceAsset->BaseLength;
    }
    else if (DeviceAssetSelection)
    {
        return DeviceAssetSelection->BaseLength;
    }
    return FVector();
}

FName UChallengerBoxDeviceAssetsCurrent::GenerateKeyMapCurrentValues(FName ComponentTag, int32 NumAsset, int32 NumAdditional)
{
    FString Result = FString::Printf(TEXT("(%s),"), *ComponentTag.ToString()) +
                     FString::Printf(TEXT("(NumAsset:%d),"), NumAsset) +
                     FString::Printf(TEXT("(NumAdditional:%d)"), NumAdditional);

    return FName(Result);
}

FName UChallengerBoxDeviceAssetsCurrent::ConvertCompotentTagOfKeyMap(FName KeyMap)
{
    FString KeyMapStr = KeyMap.ToString();
    int32 OpenParenthesisIndex = -1;
    if (KeyMapStr.FindChar('(', OpenParenthesisIndex))
    {
        int32 CloseParenthesisIndex = -1;
        if (KeyMapStr.FindChar(')', CloseParenthesisIndex) && CloseParenthesisIndex > OpenParenthesisIndex)
        {
            FString ComponentTag = KeyMapStr.Mid(OpenParenthesisIndex + 1, CloseParenthesisIndex - OpenParenthesisIndex - 1);
            return FName(*ComponentTag);
        }
    }
    return FName();
}

FBoxDataCurrentValues UChallengerBoxDeviceAssetsCurrent::FindCurrentValuesDataSelection(FName ComponentTag, int32 NumAsset, int32 NumAdditional)
{
    FName KeyGem = GenerateKeyMapCurrentValues(ComponentTag, NumAsset, NumAdditional);
    FBoxDataCurrentValues CurrentValues;
    FBoxDataCurrentValues* CurrentValuesPtr = MappingBaseAssetsSelected.Find(KeyGem);
    if (CurrentValuesPtr)
    {
        CurrentValues = *CurrentValuesPtr;
        return CurrentValues;
    }
    CurrentValues.bIsEmpty = true;
    return CurrentValues;
}

FBoxDataCurrentValues UChallengerBoxDeviceAssetsCurrent::FindCurrentValuesData(FName ComponentTag, int32 NumAsset, int32 NumAdditional)
{
    FName KeyGem = GenerateKeyMapCurrentValues(ComponentTag, NumAsset, NumAdditional);
    FBoxDataCurrentValues* CurrentValuesPtr = MappingBaseAssets.Find(KeyGem);
    FBoxDataCurrentValues CurrentValues;
    if (CurrentValuesPtr)
    {
        CurrentValues = *CurrentValuesPtr;
        return CurrentValues;
    }
    CurrentValues.bIsEmpty = true;
    return CurrentValues;
}

FBoxDataCurrentValues UChallengerBoxDeviceAssetsCurrent::FindCurrentValuesData(FName KeyMap)
{
    FBoxDataCurrentValues* CurrentValuesPtr = MappingBaseAssets.Find(KeyMap);
    FBoxDataCurrentValues CurrentValues;
    if (CurrentValuesPtr)
    {
        CurrentValues = *CurrentValuesPtr;
        return CurrentValues;
    }
    CurrentValues.bIsEmpty = true;
    return CurrentValues;
}

void UChallengerBoxDeviceAssetsCurrent::UpdateDataBuildingClipboard(FName ComponentTag, FName KeyMap, int32 NumLayer, int32 NumBox)
{
    if (FBoxDataLayers* DataLayerPtr = DataBuilding.MapDataLayers.Find(NumLayer))
    {
        if (DataLayerPtr->LayersList.Num() != 0)
        {
            if(FBoxDataLayersList LayersList = DataLayerPtr->GetFirst(); !LayersList.IsEmpty)
            {
                if (FBoxDataDevice* DataDevice = LayersList.MapNumBox.Find(NumBox))
                {
                    if(FName* GetKeyMap = DataDevice->MapComponentKey.Find(ComponentTag))
                    {
                        if (KeyMap != *GetKeyMap)
                        {
                            DataDevice->MapComponentKey.Add(ComponentTag, KeyMap);
                            DataLayerPtr->AddFirst(LayersList);
                            DataLayerPtr->RemoveLast();
                        }
                    }
                    else
                    {
                        DataDevice->MapComponentKey.Add(ComponentTag, KeyMap);
                        DataLayerPtr->AddFirst(LayersList);
                        DataLayerPtr->RemoveLast();
                    }
                }
                else
                {
                    FBoxDataDevice DataDeviceNew;
                    DataDeviceNew.MapComponentKey.Add(ComponentTag, KeyMap);
                    LayersList.MapNumBox.Add(NumBox, DataDeviceNew);
                    DataLayerPtr->AddFirst(LayersList);
                    DataLayerPtr->RemoveLast();
                }
            }
            else
            {
                FBoxDataDevice DataDeviceNew;
                DataDeviceNew.MapComponentKey.Add(ComponentTag, KeyMap);
                FBoxDataLayersList LayersListNew;
                LayersListNew.MapNumBox.Add(NumBox, DataDeviceNew);
                DataLayerPtr->AddFirst(LayersList);
                DataLayerPtr->RemoveLast();
            }
        }
        else
        {
            FBoxDataDevice DataDeviceNew;
            DataDeviceNew.MapComponentKey.Add(ComponentTag, KeyMap);
            FBoxDataLayersList LayersListNew;
            LayersListNew.MapNumBox.Add(NumBox, DataDeviceNew);
            DataLayerPtr->LayersList.Add(FBoxDataLayersList());
        }
    }
    else
    {
        FBoxDataDevice DataDeviceNew;
        DataDeviceNew.MapComponentKey.Add(ComponentTag, KeyMap);
        FBoxDataLayersList LayersListNew;
        LayersListNew.MapNumBox.Add(NumBox, DataDeviceNew);
        FBoxDataLayers DataLayerNew;
        DataLayerNew.LayersList.Add(LayersListNew);
        DataBuilding.MapDataLayers.Add(NumLayer, DataLayerNew);
    }
}

void UChallengerBoxDeviceAssetsCurrent::UpdateDataBuildingClipboard(TMap<FName, FName> MapComponentKey, int32 NumLayer, int32 NumBox)
{
    if (MapComponentKey.Num() != 0)
    {
        if (FBoxDataLayers* DataLayerPtr = DataBuilding.MapDataLayers.Find(NumLayer))
        {
            if (DataLayerPtr->LayersList.Num() != 0)
            {
                if (FBoxDataLayersList LayersList = DataLayerPtr->GetFirst(); !LayersList.IsEmpty)
                {
                    if (FBoxDataDevice* DataDevice = LayersList.MapNumBox.Find(NumBox))
                    {
                        DataDevice->MapComponentKey.Empty();
                        DataDevice->MapComponentKey = MapComponentKey;
                        DataLayerPtr->AddFirst(LayersList);
                        DataLayerPtr->RemoveLast();
                    }
                    else
                    {
                        FBoxDataDevice DataDeviceNew;
                        DataDeviceNew.MapComponentKey = MapComponentKey;
                        LayersList.MapNumBox.Add(NumBox, DataDeviceNew);
                        DataLayerPtr->AddFirst(LayersList);
                        DataLayerPtr->RemoveLast();
                    }
                }
                else
                {
                    FBoxDataDevice DataDeviceNew;
                    DataDeviceNew.MapComponentKey = MapComponentKey;
                    FBoxDataLayersList LayersListNew;
                    LayersListNew.MapNumBox.Add(NumBox, DataDeviceNew);
                    DataLayerPtr->AddFirst(LayersList);
                    DataLayerPtr->RemoveLast();
                }
            }
            else
            {
                FBoxDataDevice DataDeviceNew;
                DataDeviceNew.MapComponentKey = MapComponentKey;
                FBoxDataLayersList LayersListNew;
                LayersListNew.MapNumBox.Add(NumBox, DataDeviceNew);
                DataLayerPtr->LayersList.Add(FBoxDataLayersList());
            }
        }
        else
        {
            FBoxDataDevice DataDeviceNew;
            DataDeviceNew.MapComponentKey = MapComponentKey;
            FBoxDataLayersList LayersListNew;
            LayersListNew.MapNumBox.Add(NumBox, DataDeviceNew);
            FBoxDataLayers DataLayerNew;
            DataLayerNew.LayersList.Add(LayersListNew);
            DataBuilding.MapDataLayers.Add(NumLayer, DataLayerNew);
        }
    }
}

void UChallengerBoxDeviceAssetsCurrent::UpdateSave(int32 NumLayer, FVector BasePosition, FName KeyMap)
{
    if (FBoxDataCurrentValues* CurrentValues = MappingBaseAssets.Find(KeyMap))
    {
        FBoxDeviceAssetsData AssetData = CurrentValues->AssetsData;
        if (SaveDeviceAssets)
        {
            SaveDeviceAssets->AddAssetBoxDataComponent(
                NumLayer,
                BasePosition,
                AssetData.BuildingComponentName,
                AssetData.TypeMesh, 
                CurrentValues->CurrentTransform, 
                GetBaseLength(), 
                KeyMap,
                AssetData.bUseAActor,
                AssetData.TypeActor
            );
        }
    }
}

TArray<FName> UChallengerBoxDeviceAssetsCurrent::GetMapLoad(int32 Numlayer, FVector BasePosition)
{
    TArray<FName> KeyMap;
    if (SaveDeviceAssets)
    {
        FBoxDataLayer* DataLayer = SaveDeviceAssets->MapBaseBox.Find(Numlayer);
        if (DataLayer)
        {
            for (TPair<FBuildingComponentsNames, FBoxDataComponent> PairDataComponent : DataLayer->MapBoxDataComponent)
            {
                FBoxDataComponent DataComponent = PairDataComponent.Value;
                FBoxAssetDataComponent* AssetDataComponent = DataComponent.MapDataComponent.Find(BasePosition);
                if(AssetDataComponent)
                {
                    for (FName Key : AssetDataComponent->KeyToLoad)
                    {
                        KeyMap.Add(Key);
                    }
                }
            }
        }
    }
    return KeyMap;
}

void UChallengerBoxDeviceAssetsCurrent::SetClipboard(bool Undo, int32 NumLayer)
{
    if (FBoxDataLayers* DataLayerPtr = DataBuilding.MapDataLayers.Find(NumLayer))
    {
        if (Undo)
        {
            DataLayerPtr->Undo();
        }
        else
        {
            DataLayerPtr->Redo();
        }
    }  
}

FBoxDataLayersList UChallengerBoxDeviceAssetsCurrent::FindDataBuildingCurrentByLayer(int32 NumLayer)
{
    if (FBoxDataLayers* DataLayer = DataBuilding.MapDataLayers.Find(NumLayer))
    {
        return DataLayer->GetFirst();
    }
    FBoxDataLayersList LayersList;
    LayersList.IsEmpty = true;
    return LayersList;
}

void UChallengerBoxDeviceAssetsCurrent::ClearDataLayersList(int32 NumLayer)
{
    if(DataBuilding.MapDataLayers.Contains(NumLayer))
    {
        if(DataBuilding.MapDataLayers[NumLayer].LayersList.IsValidIndex(0))
        {
            DataBuilding.MapDataLayers[NumLayer].LayersList[0].MapNumBox.Empty();
        }
    }
}

void UChallengerBoxDeviceAssetsCurrent::ClearDataBuilding()
{
    DataBuilding.MapDataLayers.Empty();
}

void UChallengerBoxDeviceAssetsCurrent::AddDataLayersList(int32 NumLayer, int32 NumBox, FName ComponentTag, FName KeyMap)
{
    if (DataBuilding.MapDataLayers.Contains(NumLayer))
    {
        if (DataBuilding.MapDataLayers[NumLayer].LayersList.IsValidIndex(0))
        {
            DataBuilding.MapDataLayers[NumLayer].LayersList[0].AddItem(NumBox, ComponentTag, KeyMap);
        }
        else
        {
            FBoxDataLayersList LayersList;
            LayersList.AddItem(NumBox, ComponentTag, KeyMap);
            DataBuilding.MapDataLayers[NumLayer].LayersList.Insert(LayersList, 0);
        }
    }
    else
    {
        FBoxDataLayersList LayersListNew;
        LayersListNew.AddItem(NumBox, ComponentTag, KeyMap);
        FBoxDataLayers DataLayers;
        DataLayers.LayersList.Add(LayersListNew);
        DataBuilding.MapDataLayers.Add(NumLayer, DataLayers);
    }
}

void UChallengerBoxDeviceAssetsCurrent::UpdateBoxCurrentDataSelection()
{
    MappingBaseAssetsSelected.Empty();
    if(DeviceAssetSelection)
    for (TPair<EBoxComponentsTags, FBoxDeviceComponentData> Pair : DeviceAssetSelection->MapComponentData)
    {
        FName ComponentTag = *UEnum::GetDisplayValueAsText(Pair.Key).ToString();
        TArray<FName> Assets = Pair.Value.Assets;
        for (int32 NumAsset = 0; NumAsset < Assets.Num(); NumAsset++)
        {
            FBoxDeviceAssetsData *AssetData = DeviceAssetSelection->ParametersDeviceAssets.Find(Assets[NumAsset]);
            TArray<FBoxAssetsAdjustments> Adjustments = AssetData->TransformAdjustments;
            if (Adjustments.Num() != 0)
            {
                for (int32 NumAdditional = 0; NumAdditional < Adjustments.Num(); NumAdditional++)
                {
                    FBoxDataCurrentValues CurrentValues;
                    CurrentValues.ComponentData = Pair.Value;
                    CurrentValues.AssetsData = *AssetData;
                    CurrentValues.Adjustments = Adjustments[NumAdditional];
                    CurrentValues.CurrentTransform = UChallengerBoxDeviceAssets::GenerateTransforElement
                    (
                        Pair.Value.CardinalDirection,
                        Pair.Value.BaseTransform,
                        Adjustments[NumAdditional],
                        GetBaseLength()
                    );
                    FName KeyGen = GenerateKeyMapCurrentValues(ComponentTag, NumAsset, NumAdditional);
                    CurrentValues.KeyNumAsset = NumAsset;
                    CurrentValues.KeyNumAdditional = NumAdditional;
                    MappingBaseAssetsSelected.Add(KeyGen, CurrentValues);
                }
            }
            else
            {
                FBoxAssetsAdjustments NewAdjustments;
                NewAdjustments.Location = FVector();
                NewAdjustments.Rotation = FRotator();
                FBoxDataCurrentValues CurrentValues;
                CurrentValues.ComponentData = Pair.Value;
                CurrentValues.AssetsData = *AssetData;
                CurrentValues.Adjustments = NewAdjustments;
                CurrentValues.CurrentTransform = UChallengerBoxDeviceAssets::GenerateTransforElement
                (
                    Pair.Value.CardinalDirection,
                    Pair.Value.BaseTransform,
                    NewAdjustments,
                    GetBaseLength()
                );
                FName KeyGen = GenerateKeyMapCurrentValues(ComponentTag, NumAsset, 0);
                CurrentValues.KeyNumAsset = NumAsset;
                CurrentValues.KeyNumAdditional = 0;
                MappingBaseAssetsSelected.Add(KeyGen, CurrentValues);
            }
        }
    }
}

void UChallengerBoxDeviceAssetsCurrent::UpdateBoxCurrentData()
{
    MappingBaseAssets.Empty();
    AmountWidgetsToGenerate = 0;
    if(DeviceAsset)
    {
        for (TPair<EBoxComponentsTags, FBoxDeviceComponentData> Pair : DeviceAsset->MapComponentData)
        {
            FName ComponentTag = *UEnum::GetDisplayValueAsText(Pair.Key).ToString();
            TArray<FName> Assets = Pair.Value.Assets;
            if (AmountWidgetsToGenerate < Assets.Num()) AmountWidgetsToGenerate = Assets.Num();
            for (int32 NumAsset = 0; NumAsset < Assets.Num(); NumAsset++)
            {
                FBoxDeviceAssetsData* AssetData = DeviceAsset->ParametersDeviceAssets.Find(Assets[NumAsset]);
                if(AssetData)
                {
                    TArray<FBoxAssetsAdjustments> Adjustments = AssetData->TransformAdjustments;
                    if (Adjustments.Num() != 0)
                    {
                        for (int32 NumAdditional = 0; NumAdditional < Adjustments.Num(); NumAdditional++)
                        {
                            FBoxDataCurrentValues CurrentValues;
                            CurrentValues.ComponentData = Pair.Value;
                            CurrentValues.AssetsData = *AssetData;
                            CurrentValues.Adjustments = Adjustments[NumAdditional];
                            CurrentValues.CurrentTransform = UChallengerBoxDeviceAssets::GenerateTransforElement
                            (
                                Pair.Value.CardinalDirection,
                                Pair.Value.BaseTransform,
                                Adjustments[NumAdditional],
                                GetBaseLength()
                            );
                            FName KeyGen = GenerateKeyMapCurrentValues(ComponentTag, NumAsset, NumAdditional);
                            CurrentValues.KeyNumAsset = NumAsset;
                            CurrentValues.KeyNumAdditional = NumAdditional;
                            MappingBaseAssets.Add(KeyGen, CurrentValues);
                        }
                    }
                    else
                    {
                        FBoxAssetsAdjustments NewAdjustments;
                        NewAdjustments.Location = FVector();
                        NewAdjustments.Rotation = FRotator();
                        FBoxDataCurrentValues CurrentValues;
                        CurrentValues.ComponentData = Pair.Value;
                        CurrentValues.AssetsData = *AssetData;
                        CurrentValues.Adjustments = NewAdjustments;
                        CurrentValues.CurrentTransform = UChallengerBoxDeviceAssets::GenerateTransforElement
                        (
                            Pair.Value.CardinalDirection,
                            Pair.Value.BaseTransform,
                            NewAdjustments,
                            GetBaseLength()
                        );
                        FName KeyGen = GenerateKeyMapCurrentValues(ComponentTag, NumAsset, 0);
                        CurrentValues.KeyNumAsset = NumAsset;
                        CurrentValues.KeyNumAdditional = 0;
                        MappingBaseAssets.Add(KeyGen, CurrentValues);

                    }
                }
            }
        }
    }
}

void UChallengerBoxDeviceAssetsCurrent::PostLoad()
{
    Super::PostLoad();
    //UpdateBoxCurrentDataSelection();
    //UpdateBoxCurrentData();
    //DataBuilding.MapDataLayers.Empty();
}

void UChallengerBoxDeviceAssetsCurrent::UpdateData()
{
    if (DeviceAsset)
    {
        DeviceAsset->UpdateAssets();
    }
    if (DeviceAssetSelection)
    {
        DeviceAssetSelection->UpdateAssets();
    }
    UpdateBoxCurrentDataSelection();
    UpdateBoxCurrentData();
    this->SaveConfig();
}
