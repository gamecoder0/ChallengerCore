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

void UChallengerDataInstancedMesh::WriteDataTable()
{
	if (bButtonsEnable)
	{
		if (DataTableInstancedMesh && DataTableInstancedMesh->RowStruct == TBaseStructure<FDataInstancedMesh>::Get())
		{
			FDataInstancedMesh* ExistingRow = DataTableInstancedMesh->FindRow<FDataInstancedMesh>(this->GetFName(), "");

			if (ExistingRow)
			{
				ExistingRow->MapBaseBox = MapBaseBox;
				UE_LOG(LogTemp, Display, TEXT("Row with name '%s' already exists. Overwriting."), *(this->GetFName().ToString()));
			}
			else
			{
				FDataInstancedMesh NewRow;
				NewRow.MapBaseBox = MapBaseBox;
				DataTableInstancedMesh->AddRow(this->GetFName(), NewRow);
				UE_LOG(LogTemp, Display, TEXT("Row with name '%s' does not exist. Creating new row."), *(this->GetFName().ToString()));
			}
		}
	}
}

void UChallengerDataInstancedMesh::ReadDataTable()
{
	if (bButtonsEnable)
	{
		if (DataTableInstancedMesh && DataTableInstancedMesh->RowStruct == TBaseStructure<FDataInstancedMesh>::Get())
		{
			FDataInstancedMesh* DataRow = DataTableInstancedMesh->FindRow<FDataInstancedMesh>(this->GetFName(), "");
			if (DataRow)
			{
				MapBaseBox = DataRow->MapBaseBox;
				UE_LOG(LogTemp, Display, TEXT("Row with name '%s' already exists. Overwriting."), *(this->GetFName().ToString()));
			}
			else
			{
				UE_LOG(LogTemp, Display, TEXT("Row with name '%s' does not exist. Creating new row."), *(this->GetFName().ToString()));
			}
		}
	}
}

