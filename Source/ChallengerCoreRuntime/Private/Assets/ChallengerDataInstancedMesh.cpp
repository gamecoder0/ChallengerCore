// Fill out your copyright notice in the Description page of Project Settings.


#include "Assets/ChallengerDataInstancedMesh.h"


void UChallengerDataInstancedMesh::AddAssetBoxDataComponent(int32 NumLayer, FVector BoxBaseLocation, FBuildingComponentsNames ComponentType, UStaticMesh* TypeMesh, FTransform Instance, FVector BaseLength, FName KeyMap, bool bUseAActor, TSubclassOf<AActor> TypeActor)
{
	FBoxDataLayer& DataLayer = MapBaseBox.FindOrAdd(NumLayer);
	FBoxDataComponent& DataComponent = DataLayer.MapBoxDataComponent.FindOrAdd(ComponentType);
	DataComponent.bUseAActor = bUseAActor;
	DataComponent.TypeMesh = TypeMesh;
	DataComponent.TypeActor = TypeActor;
	FBoxAssetDataComponent& AssetDataComponent = DataComponent.MapDataComponent.FindOrAdd(BoxBaseLocation);
	AssetDataComponent.AddNewInstance(BoxBaseLocation, Instance, BaseLength);
	AssetDataComponent.KeyToLoad.Add(KeyMap);
	this->SaveConfig();
}

void UChallengerDataInstancedMesh::CleanBaseBox()
{
	MapBaseBox.Empty();
}

