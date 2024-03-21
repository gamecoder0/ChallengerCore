// Fill out your copyright notice in the Description page of Project Settings.


#include "Editor/ChallengerBoxDevice.h"
#include "Editor/ChallengerBoxDeviceAssetsCurrent.h"
#include "Editor/ChallengerBoxLayeringDevice.h"
#include "Engine/StaticMeshActor.h"

// Sets default values
AChallengerBoxDevice::AChallengerBoxDevice()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, RootSceneComponent));
	RootComponent = RootSceneComponent;

	DownComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::DownComponent).ToString());
	DownMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, DownMeshComponent));
	DownMeshComponent->SetupAttachment(RootSceneComponent);
	DownMeshComponent->ComponentTags.Add(DownComponentTag);
	DownActorComponent = CreateDefaultSubobject<UChildActorComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, DownActorComponent));
	DownActorComponent->SetupAttachment(RootSceneComponent);
	DownActorComponent->ComponentTags.Add(DownComponentTag);

	DownNorthComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::DownNorthComponent).ToString());
	DownNorthMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, DownNorthMeshComponent));
	DownNorthMeshComponent->SetupAttachment(RootSceneComponent);
	DownNorthMeshComponent->ComponentTags.Add(DownNorthComponentTag);
	DownNorthActorComponent = CreateDefaultSubobject<UChildActorComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, DownNorthActorComponent));
	DownNorthActorComponent->SetupAttachment(RootSceneComponent);
	DownNorthActorComponent->ComponentTags.Add(DownNorthComponentTag);

	DownEastComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::DownEastComponent).ToString());
	DownEastMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, DownEastMeshComponent));
	DownEastMeshComponent->SetupAttachment(RootSceneComponent);
	DownEastMeshComponent->ComponentTags.Add(DownEastComponentTag);
	DownEastActorComponent = CreateDefaultSubobject<UChildActorComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, DownEastActorComponent));
	DownEastActorComponent->SetupAttachment(RootSceneComponent);
	DownEastActorComponent->ComponentTags.Add(DownEastComponentTag);

	DownSouthComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::DownSouthComponent).ToString());
	DownSouthMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, DownSouthMeshComponent));
	DownSouthMeshComponent->SetupAttachment(RootSceneComponent);
	DownSouthMeshComponent->ComponentTags.Add(DownSouthComponentTag);
	DownSouthActorComponent = CreateDefaultSubobject<UChildActorComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, DownSouthActorComponent));
	DownSouthActorComponent->SetupAttachment(RootSceneComponent);
	DownSouthActorComponent->ComponentTags.Add(DownSouthComponentTag);

	DownWestComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::DownWestComponent).ToString());
	DownWestMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, DownWestMeshComponent));
	DownWestMeshComponent->SetupAttachment(RootSceneComponent);
	DownWestMeshComponent->ComponentTags.Add(DownWestComponentTag);
	DownWestActorComponent = CreateDefaultSubobject<UChildActorComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, DownWestActorComponent));
	DownWestActorComponent->SetupAttachment(RootSceneComponent);
	DownWestActorComponent->ComponentTags.Add(DownWestComponentTag);

	DownNorthLeftComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::DownNorthLeftComponent).ToString());
	DownNorthLeftMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, DownNorthLeftMeshComponent));
	DownNorthLeftMeshComponent->SetupAttachment(RootSceneComponent);
	DownNorthLeftMeshComponent->ComponentTags.Add(DownNorthLeftComponentTag);
	DownNorthLeftActorComponent = CreateDefaultSubobject<UChildActorComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, DownNorthLeftActorComponent));
	DownNorthLeftActorComponent->SetupAttachment(RootSceneComponent);
	DownNorthLeftActorComponent->ComponentTags.Add(DownNorthLeftComponentTag);

	DownEastLeftComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::DownEastLeftComponent).ToString());
	DownEastLeftMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, DownEastLeftMeshComponent));
	DownEastLeftMeshComponent->SetupAttachment(RootSceneComponent);
	DownEastLeftMeshComponent->ComponentTags.Add(DownEastLeftComponentTag);
	DownEastLeftActorComponent = CreateDefaultSubobject<UChildActorComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, DownEastLeftActorComponent));
	DownEastLeftActorComponent->SetupAttachment(RootSceneComponent);
	DownEastLeftActorComponent->ComponentTags.Add(DownEastLeftComponentTag);

	DownSouthLeftComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::DownSouthLeftComponent).ToString());
	DownSouthLeftMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, DownSouthLeftMeshComponent));
	DownSouthLeftMeshComponent->SetupAttachment(RootSceneComponent);
	DownSouthLeftMeshComponent->ComponentTags.Add(DownSouthLeftComponentTag);
	DownSouthLeftActorComponent = CreateDefaultSubobject<UChildActorComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, DownSouthLeftActorComponent));
	DownSouthLeftActorComponent->SetupAttachment(RootSceneComponent);
	DownSouthLeftActorComponent->ComponentTags.Add(DownSouthLeftComponentTag);

	DownWestLeftComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::DownWestLeftComponent).ToString());
	DownWestLeftMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, DownWestLeftMeshComponent));
	DownWestLeftMeshComponent ->SetupAttachment(RootSceneComponent);
	DownWestLeftMeshComponent ->ComponentTags.Add(DownWestLeftComponentTag);
	DownWestLeftActorComponent = CreateDefaultSubobject<UChildActorComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, DownWestLeftActorComponent));
	DownWestLeftActorComponent ->SetupAttachment(RootSceneComponent);
	DownWestLeftActorComponent ->ComponentTags.Add(DownWestLeftComponentTag);

	DownNorthRightComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::DownNorthRightComponent).ToString());
	DownNorthRightMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, DownNorthRightMeshComponent));
	DownNorthRightMeshComponent ->SetupAttachment(RootSceneComponent);
	DownNorthRightMeshComponent ->ComponentTags.Add(DownNorthRightComponentTag);
	DownNorthRightActorComponent = CreateDefaultSubobject<UChildActorComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, DownNorthRightActorComponent));
	DownNorthRightActorComponent ->SetupAttachment(RootSceneComponent);
	DownNorthRightActorComponent ->ComponentTags.Add(DownNorthRightComponentTag);

	DownEastRightComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::DownEastRightComponent).ToString());
	DownEastRightMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, DownEastRightMeshComponent));
	DownEastRightMeshComponent ->SetupAttachment(RootSceneComponent);
	DownEastRightMeshComponent ->ComponentTags.Add(DownEastRightComponentTag);
	DownEastRightActorComponent = CreateDefaultSubobject<UChildActorComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, DownEastRightActorComponent));
	DownEastRightActorComponent ->SetupAttachment(RootSceneComponent);
	DownEastRightActorComponent ->ComponentTags.Add(DownEastRightComponentTag);

	DownSouthRightComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::DownSouthRightComponent).ToString());
	DownSouthRightMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, DownSouthRightMeshComponent));
	DownSouthRightMeshComponent->SetupAttachment(RootSceneComponent);
	DownSouthRightMeshComponent->ComponentTags.Add(DownSouthRightComponentTag);
	DownSouthRightActorComponent = CreateDefaultSubobject<UChildActorComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, DownSouthRightActorComponent));
	DownSouthRightActorComponent->SetupAttachment(RootSceneComponent);
	DownSouthRightActorComponent->ComponentTags.Add(DownSouthRightComponentTag);

	DownWestRightComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::DownWestRightComponent).ToString());
	DownWestRightMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, DownWestRightMeshComponent));
	DownWestRightMeshComponent->SetupAttachment(RootSceneComponent);
	DownWestRightMeshComponent->ComponentTags.Add(DownWestRightComponentTag);
	DownWestRightActorComponent = CreateDefaultSubobject<UChildActorComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, DownWestRightActorComponent));
	DownWestRightActorComponent->SetupAttachment(RootSceneComponent);
	DownWestRightActorComponent->ComponentTags.Add(DownWestRightComponentTag);

	TopComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::TopComponent).ToString());
	TopMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, TopMeshComponent));
	TopMeshComponent->SetupAttachment(RootSceneComponent);
	TopMeshComponent->ComponentTags.Add(TopComponentTag);
	TopActorComponent = CreateDefaultSubobject<UChildActorComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, TopActorComponent));
	TopActorComponent->SetupAttachment(RootSceneComponent);
	TopActorComponent->ComponentTags.Add(TopComponentTag);

	TopNorthComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::TopNorthComponent).ToString());
	TopNorthMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, TopNorthMeshComponent));
	TopNorthMeshComponent->SetupAttachment(RootSceneComponent);
	TopNorthMeshComponent->ComponentTags.Add(TopNorthComponentTag);
	TopNorthActorComponent = CreateDefaultSubobject<UChildActorComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, TopNorthActorComponent));
	TopNorthActorComponent->SetupAttachment(RootSceneComponent);
	TopNorthActorComponent->ComponentTags.Add(TopNorthComponentTag);

	TopEastComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::TopEastComponent).ToString());
	TopEastMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, TopEastMeshComponent));
	TopEastMeshComponent->SetupAttachment(RootSceneComponent);
	TopEastMeshComponent->ComponentTags.Add(TopEastComponentTag);
	TopEastActorComponent = CreateDefaultSubobject<UChildActorComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, TopEastActorComponent));
	TopEastActorComponent->SetupAttachment(RootSceneComponent);
	TopEastActorComponent->ComponentTags.Add(TopEastComponentTag);

	TopSouthComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::TopSouthComponent).ToString());
	TopSouthMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, TopSouthMeshComponent));
	TopSouthMeshComponent->SetupAttachment(RootSceneComponent);
	TopSouthMeshComponent->ComponentTags.Add(TopSouthComponentTag);
	TopSouthActorComponent = CreateDefaultSubobject<UChildActorComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, TopSouthActorComponent));
	TopSouthActorComponent->SetupAttachment(RootSceneComponent);
	TopSouthActorComponent->ComponentTags.Add(TopSouthComponentTag);

	TopWestComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::TopWestComponent).ToString());
	TopWestMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, TopWestMeshComponent));
	TopWestMeshComponent->SetupAttachment(RootSceneComponent);
	TopWestMeshComponent->ComponentTags.Add(TopWestComponentTag);
	TopWestActorComponent = CreateDefaultSubobject<UChildActorComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, TopWestActorComponent));
	TopWestActorComponent->SetupAttachment(RootSceneComponent);
	TopWestActorComponent->ComponentTags.Add(TopWestComponentTag);

	TopNorthLeftComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::TopNorthLeftComponent).ToString());
	TopNorthLeftMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, TopNorthLeftMeshComponent));
	TopNorthLeftMeshComponent->SetupAttachment(RootSceneComponent);
	TopNorthLeftMeshComponent->ComponentTags.Add(TopNorthLeftComponentTag);
	TopNorthLeftActorComponent = CreateDefaultSubobject<UChildActorComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, TopNorthLeftActorComponent));
	TopNorthLeftActorComponent->SetupAttachment(RootSceneComponent);
	TopNorthLeftActorComponent->ComponentTags.Add(TopNorthLeftComponentTag);

	TopEastLeftComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::TopEastLeftComponent).ToString());
	TopEastLeftMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, TopEastLeftMeshComponent));
	TopEastLeftMeshComponent->SetupAttachment(RootSceneComponent);
	TopEastLeftMeshComponent->ComponentTags.Add(TopEastLeftComponentTag);
	TopEastLeftActorComponent = CreateDefaultSubobject<UChildActorComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, TopEastLeftActorComponent));
	TopEastLeftActorComponent->SetupAttachment(RootSceneComponent);
	TopEastLeftActorComponent->ComponentTags.Add(TopEastLeftComponentTag);

	TopSouthLeftComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::TopSouthLeftComponent).ToString());
	TopSouthLeftMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, TopSouthLeftMeshComponent));
	TopSouthLeftMeshComponent->SetupAttachment(RootSceneComponent);
	TopSouthLeftMeshComponent->ComponentTags.Add(TopSouthLeftComponentTag);
	TopSouthLeftActorComponent = CreateDefaultSubobject<UChildActorComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, TopSouthLeftActorComponent));
	TopSouthLeftActorComponent->SetupAttachment(RootSceneComponent);
	TopSouthLeftActorComponent->ComponentTags.Add(TopSouthLeftComponentTag);

	TopWestLeftComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::TopWestLeftComponent).ToString());
	TopWestLeftMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, TopWestLeftMeshComponent));
	TopWestLeftMeshComponent->SetupAttachment(RootSceneComponent);
	TopWestLeftMeshComponent->ComponentTags.Add(TopWestLeftComponentTag);
	TopWestLeftActorComponent = CreateDefaultSubobject<UChildActorComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, TopWestLeftActorComponent));
	TopWestLeftActorComponent->SetupAttachment(RootSceneComponent);
	TopWestLeftActorComponent->ComponentTags.Add(TopWestLeftComponentTag);

	TopNorthRightComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::TopNorthRightComponent).ToString());
	TopNorthRightMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, TopNorthRightMeshComponent));
	TopNorthRightMeshComponent->SetupAttachment(RootSceneComponent);
	TopNorthRightMeshComponent->ComponentTags.Add(TopNorthRightComponentTag);
	TopNorthRightActorComponent = CreateDefaultSubobject<UChildActorComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, TopNorthRightActorComponent));
	TopNorthRightActorComponent->SetupAttachment(RootSceneComponent);
	TopNorthRightActorComponent->ComponentTags.Add(TopNorthRightComponentTag);

	TopEastRightComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::TopEastRightComponent).ToString());
	TopEastRightMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, TopEastRightMeshComponent));
	TopEastRightMeshComponent->SetupAttachment(RootSceneComponent);
	TopEastRightMeshComponent->ComponentTags.Add(TopEastRightComponentTag);
	TopEastRightActorComponent = CreateDefaultSubobject<UChildActorComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, TopEastRightActorComponent));
	TopEastRightActorComponent->SetupAttachment(RootSceneComponent);
	TopEastRightActorComponent->ComponentTags.Add(TopEastRightComponentTag);

	TopSouthRightComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::TopSouthRightComponent).ToString());
	TopSouthRightMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, TopSouthRightMeshComponent));
	TopSouthRightMeshComponent->SetupAttachment(RootSceneComponent);
	TopSouthRightMeshComponent->ComponentTags.Add(TopSouthRightComponentTag);
	TopSouthRightActorComponent = CreateDefaultSubobject<UChildActorComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, TopSouthRightActorComponent));
	TopSouthRightActorComponent->SetupAttachment(RootSceneComponent);
	TopSouthRightActorComponent->ComponentTags.Add(TopSouthRightComponentTag);

	TopWestRightComponentTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::TopWestRightComponent).ToString());
	TopWestRightMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, TopWestRightMeshComponent));
	TopWestRightMeshComponent->SetupAttachment(RootSceneComponent);
	TopWestRightMeshComponent->ComponentTags.Add(TopWestRightComponentTag);
	TopWestRightActorComponent = CreateDefaultSubobject<UChildActorComponent>(GET_MEMBER_NAME_CHECKED(AChallengerBoxDevice, TopWestRightActorComponent));
	TopWestRightActorComponent->SetupAttachment(RootSceneComponent);
	TopWestRightActorComponent->ComponentTags.Add(TopWestRightComponentTag);

	BoxSelectedTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::BoxSelected).ToString());
	BoxSelected = CreateDefaultSubobject<UStaticMeshComponent>(BoxSelectedTag);
	BoxSelected->SetupAttachment(RootSceneComponent);
	BoxSelected->ComponentTags.Add(BoxSelectedTag);
	BoxSelected->ComponentTags.Add("SelectedMeshType");
	BoxSelected->SetRenderCustomDepth(true);

	NorthSelectedTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::NorthSelected).ToString());
	NorthSelected = CreateDefaultSubobject<UStaticMeshComponent>(NorthSelectedTag);
	NorthSelected->SetupAttachment(RootSceneComponent);
	NorthSelected->ComponentTags.Add(NorthSelectedTag);
	NorthSelected->ComponentTags.Add("SelectedMeshType");
	NorthSelected->SetRenderCustomDepth(true);

	SouthSelectedTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::SouthSelected).ToString());
	SouthSelected = CreateDefaultSubobject<UStaticMeshComponent>(SouthSelectedTag);
	SouthSelected->SetupAttachment(RootSceneComponent);
	SouthSelected->ComponentTags.Add(SouthSelectedTag);
	SouthSelected->ComponentTags.Add("SelectedMeshType");
	SouthSelected->SetRenderCustomDepth(true);

	EastSelectedTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::EastSelected).ToString());
	EastSelected = CreateDefaultSubobject<UStaticMeshComponent>(EastSelectedTag);
	EastSelected->SetupAttachment(RootSceneComponent);
	EastSelected->ComponentTags.Add(EastSelectedTag);
	EastSelected->ComponentTags.Add("SelectedMeshType");
	EastSelected->SetRenderCustomDepth(true);

	WestSelectedTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::WestSelected).ToString());
	WestSelected = CreateDefaultSubobject<UStaticMeshComponent>(WestSelectedTag);
	WestSelected->SetupAttachment(RootSceneComponent);
	WestSelected->ComponentTags.Add(WestSelectedTag);
	WestSelected->ComponentTags.Add("SelectedMeshType");
	WestSelected->SetRenderCustomDepth(true);

	CenterSelectedTag = FName(*UEnum::GetDisplayValueAsText(EBoxComponentsTags::CenterSelected).ToString());
	CenterSelected = CreateDefaultSubobject<UStaticMeshComponent>(CenterSelectedTag);
	CenterSelected->SetupAttachment(RootSceneComponent);
	CenterSelected->ComponentTags.Add(CenterSelectedTag);
	CenterSelected->ComponentTags.Add("SelectedMeshType");
	CenterSelected->SetRenderCustomDepth(true);
}

void AChallengerBoxDevice::SetDefaultConfig(UChallengerBoxDeviceAssetsCurrent* AssetsCurrent, int32 RoomsBoxX, int32 RoomsBoxY, int32 RoomsBoxZ, int32 NumBox)
{
	DeviceAssetsCurrent = AssetsCurrent;
	NumPositionBox = NumBox;
	NumRoomsBoxX = RoomsBoxX;
	NumRoomsBoxY = RoomsBoxY;
	NumRoomsBoxZ = RoomsBoxZ;

	SetSelectedBox(false);
}

void AChallengerBoxDevice::SetSelectedBox(bool Value)
{
	TArray<UStaticMeshComponent*> MeshesComponents;
	GetComponents(MeshesComponents);
	if (Value)
	{
		for (UStaticMeshComponent* ComponentSelected : MeshesComponents)
		{
			if (ComponentSelected && ComponentSelected->ComponentTags.Contains("SelectedMeshType"))
			{
				ComponentSelected->SetVisibility(true);
				UpdateDataComponentsSelected();
			}
		}
		if (BoxSelected)
		{
			BoxSelected->SetVisibility(true);
			//MarkInsertedAssets(true);
		}
	}
	else
	{
		for (UStaticMeshComponent* ComponentSelected : MeshesComponents)
		{
			if (ComponentSelected && ComponentSelected->ComponentTags.Contains("SelectedMeshType"))
			{
				ComponentSelected->SetVisibility(false);
				UpdateDataComponentsSelected();
			}
		}
		if (BoxSelected)
		{
			BoxSelected->SetVisibility(false);
			//MarkInsertedAssets(false);
		}
	}
	
}

void AChallengerBoxDevice::UpdateDataComponentsSelected()
{
	TArray<UStaticMeshComponent*> MeshesComponents;
	GetComponents(MeshesComponents);
	for (UStaticMeshComponent* Component : MeshesComponents)
	{
		if (DeviceAssetsCurrent && Component->ComponentTags.Contains("SelectedMeshType"))
		{
			TArray<FName> GetTags = Component->ComponentTags;
			FBoxDataCurrentValues CurrentValues = DeviceAssetsCurrent->FindCurrentValuesDataSelection(GetTags[0], 1, 0);
			if(CurrentValues.AssetsData.TypeMesh)
			{
				Component->SetStaticMesh(CurrentValues.AssetsData.TypeMesh);
				Component->SetRelativeTransform(CurrentValues.CurrentTransform);
				Component->CustomDepthStencilValue = 2;
			}
		}
	}
}

void AChallengerBoxDevice::UpdateDataComponentSelected(UStaticMeshComponent* Component, bool Selected)
{
	if (Component)
	{
		TArray<FName> GetTags = Component->ComponentTags;
		if (Selected)
		{
			FBoxDataCurrentValues CurrentValues = DeviceAssetsCurrent->FindCurrentValuesDataSelection(GetTags[0], 0, 0);
			if (CurrentValues.AssetsData.TypeMesh && !CurrentValues.AssetsData.bUseAActor)
			{
				Component->SetStaticMesh(CurrentValues.AssetsData.TypeMesh);
				Component->SetRelativeTransform(CurrentValues.CurrentTransform);
				Component->CustomDepthStencilValue = 1;
			}
		}
		else
		{
			FBoxDataCurrentValues CurrentValues = DeviceAssetsCurrent->FindCurrentValuesDataSelection(GetTags[0], 1, 0);
			if (CurrentValues.AssetsData.TypeMesh && !CurrentValues.AssetsData.bUseAActor)
			{
				Component->SetStaticMesh(CurrentValues.AssetsData.TypeMesh);
				Component->SetRelativeTransform(CurrentValues.CurrentTransform);
				Component->CustomDepthStencilValue = 2;
			}
		}
	}
}

FVector AChallengerBoxDevice::GetNumRoomsBox()
{
	return FVector(NumRoomsBoxX, NumRoomsBoxY, NumRoomsBoxZ);
}

int32 AChallengerBoxDevice::GetNumPositionBox()
{
	return NumPositionBox;
}

void AChallengerBoxDevice::UpdateMeshInBox(FName ComponentTag, int32 NumAsset, int32 NumAdditional)
{
	FName KeyMap = FName(UChallengerBoxDeviceAssetsCurrent::GenerateKeyMapCurrentValues(ComponentTag, NumAsset, NumAdditional));
	FBoxDataCurrentValues CurrentValues = DeviceAssetsCurrent->FindCurrentValuesData(KeyMap);
	if (!CurrentValues.IsEmpty())
	{
		UChildActorComponent* ActorComponent = FindComponentByTag<UChildActorComponent>(ComponentTag);
		UStaticMeshComponent* MeshComponent = FindComponentByTag<UStaticMeshComponent>(ComponentTag);
		if (CurrentValues.AssetsData.bUseAActor)
		{
			
			if (ActorComponent && MeshComponent)
			{
				if (CurrentValues.AssetsData.TypeActor)
				{
					ActorComponent->SetChildActorClass(CurrentValues.AssetsData.TypeActor);
					ActorComponent->SetRelativeTransform(CurrentValues.CurrentTransform);
					MeshComponent->SetStaticMesh(NULL);
					MeshComponent->SetRelativeTransform(FTransform());
					MapComponentAndKey.Add(ComponentTag, KeyMap);
				}
				else
				{
					ActorComponent->SetChildActorClass(TSubclassOf<AActor>());
					ActorComponent->SetRelativeTransform(FTransform());
					MeshComponent->SetStaticMesh(NULL);
					MeshComponent->SetRelativeTransform(FTransform());
					MapComponentAndKey.Remove(ComponentTag);
				}
			}
		}
		else
		{
			if (ActorComponent && MeshComponent)
			{
				if (CurrentValues.AssetsData.TypeMesh)
				{
					MeshComponent->SetStaticMesh(CurrentValues.AssetsData.TypeMesh);
					MeshComponent->SetMaterial(0, CurrentValues.AssetsData.MaterialToViewer);
					UStaticMesh* Mesh = MeshComponent->GetStaticMesh();
					int32 NumMaterial = Mesh->GetStaticMaterials().Num() - 1;
					MeshComponent->SetMaterial(NumMaterial, CurrentValues.AssetsData.MaterialToViewerEnd);
					MeshComponent->SetRelativeTransform(CurrentValues.CurrentTransform);
					ActorComponent->SetChildActorClass(TSubclassOf<AActor>());
					ActorComponent->SetRelativeTransform(FTransform());
					MapComponentAndKey.Add(ComponentTag, KeyMap);
				}
				else
				{
					ActorComponent->SetChildActorClass(TSubclassOf<AActor>());
					ActorComponent->SetRelativeTransform(FTransform());
					MeshComponent->SetStaticMesh(NULL);
					MeshComponent->SetRelativeTransform(FTransform());
					MapComponentAndKey.Remove(ComponentTag);
				}
			}
		}
	}
}

void AChallengerBoxDevice::UpdateMeshInBox(FName ComponentTag, FName KeyMap)
{
	FBoxDataCurrentValues CurrentValues = DeviceAssetsCurrent->FindCurrentValuesData(KeyMap);
	if (!CurrentValues.IsEmpty())
	{
		UChildActorComponent* ActorComponent = FindComponentByTag<UChildActorComponent>(ComponentTag);
		UStaticMeshComponent* MeshComponent = FindComponentByTag<UStaticMeshComponent>(ComponentTag);
		if (CurrentValues.AssetsData.bUseAActor)
		{

			if (ActorComponent && MeshComponent)
			{
				if (CurrentValues.AssetsData.TypeActor)
				{
					ActorComponent->SetChildActorClass(CurrentValues.AssetsData.TypeActor);
					ActorComponent->SetRelativeTransform(CurrentValues.CurrentTransform);
					MeshComponent->SetStaticMesh(NULL);
					MeshComponent->SetRelativeTransform(FTransform());
					MapComponentAndKey.Add(ComponentTag, KeyMap);
					FTransform DownActorTransform = ActorComponent->GetComponentTransform();
				}
				else
				{
					ActorComponent->SetChildActorClass(TSubclassOf<AActor>());
					ActorComponent->SetRelativeTransform(FTransform());
					MeshComponent->SetStaticMesh(NULL);
					MeshComponent->SetRelativeTransform(FTransform());
					MapComponentAndKey.Remove(ComponentTag);
				}
			}
		}
		else
		{
			if (ActorComponent && MeshComponent)
			{
				if (CurrentValues.AssetsData.TypeMesh)
				{
					MeshComponent->SetStaticMesh(CurrentValues.AssetsData.TypeMesh);
					MeshComponent->SetMaterial(0, CurrentValues.AssetsData.MaterialToViewer);
					UStaticMesh* Mesh = MeshComponent->GetStaticMesh();
					int32 NumMaterial = Mesh->GetStaticMaterials().Num() -1;
					MeshComponent->SetMaterial(NumMaterial, CurrentValues.AssetsData.MaterialToViewerEnd);
					MeshComponent->SetRelativeTransform(CurrentValues.CurrentTransform);
					ActorComponent->SetChildActorClass(TSubclassOf<AActor>());
					ActorComponent->SetRelativeTransform(FTransform());
					MapComponentAndKey.Add(ComponentTag, KeyMap);
				}
				else
				{
					ActorComponent->SetChildActorClass(TSubclassOf<AActor>());
					ActorComponent->SetRelativeTransform(FTransform());
					MeshComponent->SetStaticMesh(NULL);
					MeshComponent->SetRelativeTransform(FTransform());
					MapComponentAndKey.Remove(ComponentTag);
				}
			}
		}
	}
}

void AChallengerBoxDevice::ClearAllMeshComponents()
{
	TArray<UStaticMeshComponent*> MeshesComponents;
	GetComponents(MeshesComponents);
	for (UStaticMeshComponent* MeshComponent : MeshesComponents)
	{
		if(!MeshComponent->ComponentTags.Contains("SelectedMeshType"))
		{
			MeshComponent->SetStaticMesh(NULL);
			MeshComponent->SetRelativeTransform(FTransform());
		}
	}
	TArray<UChildActorComponent*> ActorsComponents;
	GetComponents(ActorsComponents);
	for (UChildActorComponent* ActorComponent : ActorsComponents)
	{
		ActorComponent->SetChildActorClass(TSubclassOf<AActor>());
		ActorComponent->SetRelativeTransform(FTransform());
	}
}

TMap<FName, FName> AChallengerBoxDevice::GetMapComponentAndKey()
{
	return MapComponentAndKey;
}

void AChallengerBoxDevice::BakeMeshToLevel(FString Path)
{
	TArray<AActor*> SpawnedActors;
	TArray<UStaticMeshComponent*> MeshesComponents;
	GetComponents(MeshesComponents);
	FString MakePath;
	for (UStaticMeshComponent* MeshComponent : MeshesComponents)
	{
		if (!MeshComponent->ComponentTags.Contains("SelectedMeshType"))
		{
			if (UStaticMesh* StaticMesh = MeshComponent->GetStaticMesh())
			{
				MakePath = FString::Printf(TEXT("%s/%s"), *Path, *StaticMesh->GetName());
				FTransform MeshTransform = MeshComponent->GetComponentTransform();
				AStaticMeshActor* StaticMeshActor = GetWorld()->SpawnActorDeferred<AStaticMeshActor>(AStaticMeshActor::StaticClass(), MeshTransform);
				StaticMeshActor->GetStaticMeshComponent()->SetStaticMesh(StaticMesh);
				StaticMeshActor->FinishSpawning(MeshTransform);
				StaticMeshActor->SetFolderPath(*MakePath);
			}
		}
	}
	TArray<UChildActorComponent*> ActorsComponents;
	GetComponents(ActorsComponents);
	for (UChildActorComponent* ActorComponent : ActorsComponents)
	{
		if (UClass* ActorClass = ActorComponent->GetChildActorClass())
		{
			MakePath = FString::Printf(TEXT("%s/%s"), *Path, *ActorClass->GetName());
			FTransform ActorTransform = ActorComponent->GetComponentTransform();
			AActor* ChildActor = GetWorld()->SpawnActorDeferred<AActor>(ActorClass, ActorTransform);
			ChildActor->FinishSpawning(ActorTransform);
			ChildActor->SetFolderPath(*MakePath);
		}
	}
}

void AChallengerBoxDevice::MarkInsertedAssets(bool Value)
{
	TArray<UStaticMeshComponent*> MeshesComponents;
	GetComponents(MeshesComponents);
	for (UStaticMeshComponent* MeshComponent : MeshesComponents)
	{
		if (!MeshComponent->ComponentTags.Contains("SelectedMeshType"))
		{
			MeshComponent->SetRenderCustomDepth(true);
			if (Value)
			{
				MeshComponent->SetCustomDepthStencilValue(1);
			}
			else
			{
				MeshComponent->SetCustomDepthStencilValue(2);
			}
		}
	}
}

void AChallengerBoxDevice::ClearMarkInsertedAssets()
{
	TArray<UStaticMeshComponent*> MeshesComponents;
	GetComponents(MeshesComponents);
	for (UStaticMeshComponent* MeshComponent : MeshesComponents)
	{
		if (!MeshComponent->ComponentTags.Contains("SelectedMeshType"))
		{
			MeshComponent->SetCustomDepthStencilValue(0);
			MeshComponent->SetRenderCustomDepth(false);
		}
	}
}

void AChallengerBoxDevice::SetDirectionSelected(FAssetCardinalDirections Direction)
{
	switch (Direction)
	{
	case FAssetCardinalDirections::Default:
		UpdateDataComponentsSelected();
		break;
	case FAssetCardinalDirections::North:
	case FAssetCardinalDirections::NorthLeft:
	case FAssetCardinalDirections::NorthRight:
		UpdateDataComponentsSelected();
		UpdateDataComponentSelected(NorthSelected, true);
		break;
	case FAssetCardinalDirections::South:
	case FAssetCardinalDirections::SouthLeft:
	case FAssetCardinalDirections::SouthRight:
		UpdateDataComponentsSelected();
		UpdateDataComponentSelected(SouthSelected, true);
		break;
	case FAssetCardinalDirections::East:
	case FAssetCardinalDirections::EastLeft:
	case FAssetCardinalDirections::EastRight:
		UpdateDataComponentsSelected();
		UpdateDataComponentSelected(EastSelected, true);
		break;
	case FAssetCardinalDirections::West:
	case FAssetCardinalDirections::WestLeft:
	case FAssetCardinalDirections::WestRight:
		UpdateDataComponentsSelected();
		UpdateDataComponentSelected(WestSelected, true);
		break;
	case FAssetCardinalDirections::Center:
		UpdateDataComponentsSelected();
		UpdateDataComponentSelected(CenterSelected, true);
		break;
	default:
		UpdateDataComponentsSelected();
		break;
	}
	
}
