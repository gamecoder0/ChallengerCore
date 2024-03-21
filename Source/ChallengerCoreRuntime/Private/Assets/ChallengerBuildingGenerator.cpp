// Fill out your copyright notice in the Description page of Project Settings.


#include "Assets/ChallengerBuildingGenerator.h"
#include "Assets/ChallengerDataInstancedMesh.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"


// Sets default values
AChallengerBuildingGenerator::AChallengerBuildingGenerator()
{
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootComponent = RootSceneComponent;

	NameFloorComponent = FName(*UEnum::GetDisplayValueAsText(FBuildingComponentsNames::FloorComponent).ToString());
	FloorComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(NameFloorComponent);
	FloorComponent->SetupAttachment(RootSceneComponent);
	FloorComponent->ComponentTags.Add(NameFloorComponent);

	NameRampComponent = FName(*UEnum::GetDisplayValueAsText(FBuildingComponentsNames::RampComponent).ToString());
	RampComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(NameRampComponent);
	RampComponent->SetupAttachment(RootSceneComponent);
	RampComponent->ComponentTags.Add(NameRampComponent);

	NameFloorConnectComponent = FName(*UEnum::GetDisplayValueAsText(FBuildingComponentsNames::FloorConnectComponent).ToString());
	FloorConnectComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(NameFloorConnectComponent);
	FloorConnectComponent->SetupAttachment(RootSceneComponent);
	FloorConnectComponent->ComponentTags.Add(NameFloorConnectComponent);
	
	NameFloorTileComponent = FName(*UEnum::GetDisplayValueAsText(FBuildingComponentsNames::FloorTileComponent).ToString());
	FloorTileComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(NameFloorTileComponent);
	FloorTileComponent->SetupAttachment(RootSceneComponent);
	FloorTileComponent->ComponentTags.Add(NameFloorTileComponent);
	
	NameRoofComponent = FName(*UEnum::GetDisplayValueAsText(FBuildingComponentsNames::RoofComponent).ToString());
	RoofComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(NameRoofComponent);
	RoofComponent->SetupAttachment(RootSceneComponent);
	RoofComponent->ComponentTags.Add(NameRoofComponent);
	
	NameRoofConnectComponent = FName(*UEnum::GetDisplayValueAsText(FBuildingComponentsNames::RoofConnectComponent).ToString());
	RoofConnectComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(NameRoofConnectComponent);
	RoofConnectComponent->SetupAttachment(RootSceneComponent);
	RoofConnectComponent->ComponentTags.Add(NameRoofConnectComponent);
	
	NameRoofTileComponent = FName(*UEnum::GetDisplayValueAsText(FBuildingComponentsNames::RoofTileComponent).ToString());
	RoofTileComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(NameRoofTileComponent);
	RoofTileComponent->SetupAttachment(RootSceneComponent);
	RoofTileComponent->ComponentTags.Add(NameRoofTileComponent);
	
	NameWallComponent = FName(*UEnum::GetDisplayValueAsText(FBuildingComponentsNames::WallComponent).ToString());
	WallComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(NameWallComponent);
	WallComponent->SetupAttachment(RootSceneComponent);
	WallComponent->ComponentTags.Add(NameWallComponent);
	
	NameWallClosedCornerLeftComponent = FName(*UEnum::GetDisplayValueAsText(FBuildingComponentsNames::WallClosedCornerLeftComponent).ToString());
	WallClosedCornerLeftComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(NameWallClosedCornerLeftComponent);
	WallClosedCornerLeftComponent->SetupAttachment(RootSceneComponent);
	WallClosedCornerLeftComponent->ComponentTags.Add(NameWallClosedCornerLeftComponent);
	
	NameWallClosedCornerRightComponent = FName(*UEnum::GetDisplayValueAsText(FBuildingComponentsNames::WallClosedCornerRightComponent).ToString());
	WallClosedCornerRightComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(NameWallClosedCornerRightComponent);
	WallClosedCornerRightComponent->SetupAttachment(RootSceneComponent);
	WallClosedCornerRightComponent->ComponentTags.Add(NameWallClosedCornerRightComponent);
	
	NameWallOpenCornerLeftComponent = FName(*UEnum::GetDisplayValueAsText(FBuildingComponentsNames::WallOpenCornerLeftComponent).ToString());
	WallOpenCornerLeftComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(NameWallOpenCornerLeftComponent);
	WallOpenCornerLeftComponent->SetupAttachment(RootSceneComponent);
	WallOpenCornerLeftComponent->ComponentTags.Add(NameWallOpenCornerLeftComponent);
	
	NameWallOpenCornerRightComponent = FName(*UEnum::GetDisplayValueAsText(FBuildingComponentsNames::WallOpenCornerRightComponent).ToString());
	WallOpenCornerRightComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(NameWallOpenCornerRightComponent);
	WallOpenCornerRightComponent->SetupAttachment(RootSceneComponent);
	WallOpenCornerRightComponent->ComponentTags.Add(NameWallOpenCornerRightComponent);

	NameWallEdgeConnectComponent = FName(*UEnum::GetDisplayValueAsText(FBuildingComponentsNames::WallEdgeConnect).ToString());
	WallEdgeConnectComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(NameWallEdgeConnectComponent);
	WallEdgeConnectComponent->SetupAttachment(RootSceneComponent);
	WallEdgeConnectComponent->ComponentTags.Add(NameWallEdgeConnectComponent);

	NameWallHorizontalConnectComponent = FName(*UEnum::GetDisplayValueAsText(FBuildingComponentsNames::WallHorizontalConnect).ToString());
	WallHorizontalConnectComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(NameWallHorizontalConnectComponent);
	WallHorizontalConnectComponent->SetupAttachment(RootSceneComponent);
	WallHorizontalConnectComponent->ComponentTags.Add(NameWallHorizontalConnectComponent);
	
	NameWallShortConnectComponent = FName(*UEnum::GetDisplayValueAsText(FBuildingComponentsNames::WallShortConnect).ToString());
	WallShortConnectComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(NameWallShortConnectComponent);
	WallShortConnectComponent->SetupAttachment(RootSceneComponent);
	WallShortConnectComponent->ComponentTags.Add(NameWallShortConnectComponent);
	
	NameWallTileComponent = FName(*UEnum::GetDisplayValueAsText(FBuildingComponentsNames::WallTile).ToString());
	WallTileComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(NameWallTileComponent);
	WallTileComponent->SetupAttachment(RootSceneComponent);
	WallTileComponent->ComponentTags.Add(NameWallTileComponent);

	NameWallVerticalConnectComponent = FName(*UEnum::GetDisplayValueAsText(FBuildingComponentsNames::WallVerticalConnect).ToString());
	WallVerticalConnectComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(NameWallVerticalConnectComponent);
	WallVerticalConnectComponent->SetupAttachment(RootSceneComponent);
	WallVerticalConnectComponent->ComponentTags.Add(NameWallVerticalConnectComponent);

}

void AChallengerBuildingGenerator::SpawnMeshInComponent()
{
	ClearAllAcomponents();
	UpdateMeshesInComponent();
	SpawnActorInLevel();
}

void AChallengerBuildingGenerator::UpdateMeshesInComponent()
{
	for (TPair<int32, FBoxDataLayer> PairLayer : DataInstancedMesh->MapBaseBox)
	{
		FBoxDataLayer Box = PairLayer.Value;

		for(TPair<FBuildingComponentsNames, FBoxDataComponent>PairComponent : Box.MapBoxDataComponent)
		{
			FBoxDataComponent DataComponent = PairComponent.Value;
			if(!DataComponent.bUseAActor)
			{
				FName ComponentTag = FName(*UEnum::GetDisplayValueAsText(PairComponent.Key).ToString());
				UHierarchicalInstancedStaticMeshComponent* Component = FindComponentByTag<UHierarchicalInstancedStaticMeshComponent>(ComponentTag);
				if(Component)
				{
					Component->SetStaticMesh(DataComponent.TypeMesh);
					for (TPair<FVector, FBoxAssetDataComponent> PairDataComponent : DataComponent.MapDataComponent)
					{
						FBoxAssetDataComponent AssetDataComponent = PairDataComponent.Value;
						for (FTransform Transform : AssetDataComponent.Instances)
						{
							Component->AddInstance(Transform);
						}
					}
				}
			}
		}
	}
}

void AChallengerBuildingGenerator::SpawnActorInLevel()
{
	for (TPair<int32, FBoxDataLayer> PairLayer : DataInstancedMesh->MapBaseBox)
	{
		FBoxDataLayer Box = PairLayer.Value;

		for (TPair<FBuildingComponentsNames, FBoxDataComponent>PairComponent : Box.MapBoxDataComponent)
		{
			FBoxDataComponent DataComponent = PairComponent.Value;
			if (DataComponent.bUseAActor)
			{
				TSubclassOf<AActor> ActorClass = DataComponent.TypeActor;
				if (ActorClass)
				{
					for (TPair<FVector, FBoxAssetDataComponent> PairDataComponent : DataComponent.MapDataComponent)
					{
						FBoxAssetDataComponent AssetDataComponent = PairDataComponent.Value;
						for (FTransform Transform : AssetDataComponent.Instances)
						{
							AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorClass, FTransform::Identity);
							if (SpawnedActor)
							{
								SpawnedActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
								SpawnedActor->SetActorRelativeTransform(Transform);
							}
						}
					}
					
				}
			}
		}
	}
}

void AChallengerBuildingGenerator::ClearAllAcomponents()
{
	TArray<UHierarchicalInstancedStaticMeshComponent*> Components;
	GetComponents<UHierarchicalInstancedStaticMeshComponent>(Components);
	for (UHierarchicalInstancedStaticMeshComponent* Instance : Components)
	{
		Instance->ClearInstances();
		if(NullMesh)
		{
			Instance->SetStaticMesh(NullMesh);
			Instance->GetStaticMesh()->GetStaticMaterials();
		}
		else
		{
			Instance->SetStaticMesh(NULL);
		}
	}
}

