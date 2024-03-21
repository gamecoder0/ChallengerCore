// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Editor/ChallengerBoxLayeringDevice.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChallengerBoxDevice.generated.h"


UCLASS()
class CHALLENGERCORERUNTIME_API AChallengerBoxDevice : public AActor
{
	GENERATED_BODY()
	
public:	

	AChallengerBoxDevice();
	void SetDefaultConfig(UChallengerBoxDeviceAssetsCurrent* AssetsCurrent, int32 RoomsBoxX, int32 RoomsBoxY, int32 RoomsBoxZ, int32 NumBox);
	

public:

	void SetSelectedBox(bool Value);
	void SetDirectionSelected(FAssetCardinalDirections Direction);
	FVector GetNumRoomsBox();
	int32 GetNumPositionBox();
	void UpdateMeshInBox(FName ComponentTag, int32 NumAsset, int32 NumAdditional);
	void UpdateMeshInBox(FName ComponentTag, FName KeyMap);
	void ClearAllMeshComponents();
	TMap<FName, FName> GetMapComponentAndKey();
	void BakeMeshToLevel(FString Path);
	void MarkInsertedAssets(bool Value);
	void ClearMarkInsertedAssets();

private:

	void UpdateDataComponentsSelected();
	void UpdateDataComponentSelected(UStaticMeshComponent* Component, bool Selected);

private:

	UPROPERTY()
	USceneComponent* RootSceneComponent;
	UPROPERTY()
	int32 NumRoomsBoxX;
	UPROPERTY()
	int32 NumRoomsBoxY;
	UPROPERTY()
	int32 NumRoomsBoxZ;
	UPROPERTY()
	UChallengerBoxDeviceAssetsCurrent* DeviceAssetsCurrent;
	UPROPERTY()
	int32 NumPositionBox;
	UPROPERTY()
	TMap<FName, FName> MapComponentAndKey;
	
private:

	UPROPERTY()
	FName DownComponentTag;
	UPROPERTY()
	FName DownNorthComponentTag;
	UPROPERTY()
	FName DownEastComponentTag;
	UPROPERTY()
	FName DownSouthComponentTag;
	UPROPERTY()
	FName DownWestComponentTag;
	UPROPERTY()
	FName DownNorthLeftComponentTag;
	UPROPERTY()
	FName DownEastLeftComponentTag;
	UPROPERTY()
	FName DownSouthLeftComponentTag;
	UPROPERTY()
	FName DownWestLeftComponentTag;
	UPROPERTY()
	FName DownNorthRightComponentTag;
	UPROPERTY()
	FName DownEastRightComponentTag;
	UPROPERTY()
	FName DownSouthRightComponentTag;
	UPROPERTY()
	FName DownWestRightComponentTag;
	UPROPERTY()
	FName TopComponentTag;
	UPROPERTY()
	FName TopNorthComponentTag;
	UPROPERTY()
	FName TopEastComponentTag;
	UPROPERTY()
	FName TopSouthComponentTag;
	UPROPERTY()
	FName TopWestComponentTag;
	UPROPERTY()
	FName TopNorthLeftComponentTag;
	UPROPERTY()
	FName TopEastLeftComponentTag;
	UPROPERTY()
	FName TopSouthLeftComponentTag;
	UPROPERTY()
	FName TopWestLeftComponentTag;
	UPROPERTY()
	FName TopNorthRightComponentTag;
	UPROPERTY()
	FName TopEastRightComponentTag;
	UPROPERTY()
	FName TopSouthRightComponentTag;
	UPROPERTY()
	FName TopWestRightComponentTag;
	UPROPERTY()
	FName BoxSelectedTag;
	UPROPERTY()
	FName NorthSelectedTag;
	UPROPERTY()
	FName SouthSelectedTag;
	UPROPERTY()
	FName EastSelectedTag;
	UPROPERTY()
	FName WestSelectedTag;
	UPROPERTY()
	FName CenterSelectedTag;
	
private:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DownMeshComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DownNorthMeshComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DownEastMeshComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DownSouthMeshComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DownWestMeshComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DownNorthLeftMeshComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DownEastLeftMeshComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DownSouthLeftMeshComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DownWestLeftMeshComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DownNorthRightMeshComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DownEastRightMeshComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DownSouthRightMeshComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DownWestRightMeshComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TopMeshComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TopNorthMeshComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TopEastMeshComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TopSouthMeshComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TopWestMeshComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TopNorthLeftMeshComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TopEastLeftMeshComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TopSouthLeftMeshComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TopWestLeftMeshComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TopNorthRightMeshComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TopEastRightMeshComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TopSouthRightMeshComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TopWestRightMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* DownActorComponent;
	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* DownNorthActorComponent;
	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* DownEastActorComponent;
	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* DownSouthActorComponent;
	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* DownWestActorComponent;
	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* DownNorthLeftActorComponent;
	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* DownEastLeftActorComponent;
	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* DownSouthLeftActorComponent;
	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* DownWestLeftActorComponent;
	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* DownNorthRightActorComponent;
	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* DownEastRightActorComponent;
	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* DownSouthRightActorComponent;
	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* DownWestRightActorComponent;
	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* TopActorComponent;
	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* TopNorthActorComponent;
	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* TopEastActorComponent;
	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* TopSouthActorComponent;
	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* TopWestActorComponent;
	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* TopNorthLeftActorComponent;
	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* TopEastLeftActorComponent;
	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* TopSouthLeftActorComponent;
	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* TopWestLeftActorComponent;
	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* TopNorthRightActorComponent;
	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* TopEastRightActorComponent;
	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* TopSouthRightActorComponent;
	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* TopWestRightActorComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BoxSelected;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* NorthSelected;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SouthSelected;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* EastSelected;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* WestSelected;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CenterSelected;
};
