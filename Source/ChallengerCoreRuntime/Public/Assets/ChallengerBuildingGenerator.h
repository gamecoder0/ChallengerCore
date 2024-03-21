// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChallengerBuildingGenerator.generated.h"

class UChallengerDataInstancedMesh;
class UHierarchicalInstancedStaticMeshComponent;

USTRUCT()
struct FComponentFind
{
	GENERATED_BODY()

public:

	UHierarchicalInstancedStaticMeshComponent* ComponentElement;
	FString ComponentName;
};

UCLASS()
class CHALLENGERCORERUNTIME_API AChallengerBuildingGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	AChallengerBuildingGenerator();

	UFUNCTION(CallInEditor, Category="Generator")
	void SpawnMeshInComponent();

protected:

	void UpdateMeshesInComponent();
	void SpawnActorInLevel();
	void ClearAllAcomponents();

public:

	/** NullMesh variable:
	* This variable is used to define a simples cube that will be assigned to the UHierarchicalInstancedStaticMeshComponent.
	* By defining a siples cube for this variable, we ensure that the component does not remain empty,
	* which can prevent erros when compiling the level shaders.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ElementsBox")
	UChallengerDataInstancedMesh* DataInstancedMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ElementsBox")
	UStaticMesh* NullMesh;

protected:

	USceneComponent* RootSceneComponent;
	TArray<FComponentFind> ComponentsFind;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Instanced Component")
	UHierarchicalInstancedStaticMeshComponent* FloorComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Instanced Component")
	UHierarchicalInstancedStaticMeshComponent* RampComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Instanced Component")
	UHierarchicalInstancedStaticMeshComponent* FloorConnectComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Instanced Component")
	UHierarchicalInstancedStaticMeshComponent* FloorTileComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Instanced Component")
	UHierarchicalInstancedStaticMeshComponent* RoofComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Instanced Component")
	UHierarchicalInstancedStaticMeshComponent* RoofConnectComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Instanced Component")
	UHierarchicalInstancedStaticMeshComponent* RoofTileComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Instanced Component")
	UHierarchicalInstancedStaticMeshComponent* WallComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Instanced Component")
	UHierarchicalInstancedStaticMeshComponent* WallClosedCornerLeftComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Instanced Component")
	UHierarchicalInstancedStaticMeshComponent* WallClosedCornerRightComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Instanced Component")
	UHierarchicalInstancedStaticMeshComponent* WallOpenCornerRightComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Instanced Component")
	UHierarchicalInstancedStaticMeshComponent* WallOpenCornerLeftComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Instanced Component")
	UHierarchicalInstancedStaticMeshComponent* WallEdgeConnectComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Instanced Component")
	UHierarchicalInstancedStaticMeshComponent* WallHorizontalConnectComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Instanced Component")
	UHierarchicalInstancedStaticMeshComponent* WallShortConnectComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Instanced Component")
	UHierarchicalInstancedStaticMeshComponent* WallTileComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Instanced Component")
	UHierarchicalInstancedStaticMeshComponent* WallVerticalConnectComponent;

private:

	UPROPERTY()
	FName NameFloorComponent;
	UPROPERTY()
	FName NameRampComponent;
	UPROPERTY()
	FName NameFloorConnectComponent;
	UPROPERTY()
	FName NameFloorTileComponent;
	UPROPERTY()
	FName NameRoofComponent;
	UPROPERTY()
	FName NameRoofConnectComponent;
	UPROPERTY()
	FName NameRoofTileComponent;
	UPROPERTY()
	FName NameWallComponent;
	UPROPERTY()
	FName NameWallClosedCornerLeftComponent;
	UPROPERTY()
	FName NameWallClosedCornerRightComponent;
	UPROPERTY()
	FName NameWallOpenCornerLeftComponent;
	UPROPERTY()
	FName NameWallOpenCornerRightComponent;
	UPROPERTY()
	FName NameWallEdgeConnectComponent;
	UPROPERTY()
	FName NameWallHorizontalConnectComponent;
	UPROPERTY()
	FName NameWallShortConnectComponent;
	UPROPERTY()
	FName NameWallTileConnectComponent;
	UPROPERTY()
	FName NameWallTileComponent;
	UPROPERTY()
	FName NameWallVerticalConnectComponent;

};
