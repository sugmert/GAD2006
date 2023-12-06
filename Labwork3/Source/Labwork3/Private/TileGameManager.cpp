// Fill out your copyright notice in the Description page of Project Settings.


#include "TileGameManager.h"
#include "TilePlayerController.h"

// Sets default values
ATileGameManager::ATileGameManager() :
	GridSize(100),
	GridOffset(0, 0, 0.5f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	GridSelection = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GridMesh"));
	GridSelection->SetupAttachment(RootComponent);

	Current_Tile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SelectedTile"));
	Current_Tile->SetupAttachment(GridSelection);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		PlaneMesh(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));

	static ConstructorHelpers::FObjectFinder<UMaterialInterface>
		GridMaterial(TEXT("Material'/Game/UI/MAT_GridSlot.MAT_GridSlot'"));

	GridSelection->SetStaticMesh(PlaneMesh.Object);
	GridSelection->SetMaterial(0, GridMaterial.Object);
	GridSelection->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Current_Tile->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void ATileGameManager::BeginPlay()
{
	Super::BeginPlay();

	if (auto PlayerController =
		Cast<ATilePlayerController>(GWorld->GetFirstPlayerController()))
	{
		PlayerController->GameManager = this;
	}
	
}

// Called every frame
void ATileGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATileGameManager::OnActorInteraction(AActor* HitActor, FVector& Location, bool IsPressed)
{
	if (TileTypes.Num() == 0) return;

	FVector GridLoc = GridOffset;
	GridLoc.X = FMath::GridSnap(Location.X, GridSize);
	GridLoc.Y = FMath::GridSnap(Location.Y, GridSize);
	GridLoc.Z = Location.Z;

	UPlayerInput* Input = GWorld->GetFirstPlayerController()->PlayerInput;

	if (Input->WasJustPressed(EKeys::LeftMouseButton))
	{
		int GridX = GridLoc.X / GridSize + MapExtendsInGrids;
		int GridY = GridLoc.Y / GridSize + MapExtendsInGrids;

		if (GridX < 0 || GridY < 0 || GridX >= MapExtendsInGrids * 2 || GridY >= MapExtendsInGrids * 2)
		{
			return;
		}

		if (Map[GridX][GridY] != nullptr) return;

		if (TileTypes.IsValidIndex(CurrentTileIndex))
		{
			ATileBase* SelectedTile = TileTypes[CurrentTileIndex];
			Map[GridX][GridY] = SelectedTile;
			
			FTransform TileTransform(GridLoc + GridOffset);
			SelectedTile->InstancedMesh->AddInstance(
				SelectedTile->InstancedMesh->GetRelativeTransform() * TileTransform,
				true);
		}

		UE_LOG(LogTemp, Warning, TEXT("Hit: %s - %f,%f,%f"),
			HitActor ? *HitActor->GetActorLabel() : TEXT("None"),
			Location.X,
			Location.Y,
			Location.Z);
	}
	else if (Input->WasJustPressed(EKeys::MouseScrollDown))
	{
		CurrentSelectedTile(1);
		UE_LOG(LogTemp, Warning, TEXT("TileType: %s"), *TileTypes[CurrentTileIndex]->GetActorLabel());
	}
	else if (Input->WasJustPressed(EKeys::MouseScrollUp))
	{
		CurrentSelectedTile(-1);
		UE_LOG(LogTemp, Warning, TEXT("TileType: %s"), *TileTypes[CurrentTileIndex]->GetActorLabel());
	}
	else if (Input->WasJustPressed(EKeys::RightMouseButton))
	{
		TileRotation = (TileRotation + 90) % 360;
		CurrentSelectedTile(0);
	}
	else {
		GridSelection->SetWorldLocation(GridLoc + GridOffset);
		CurrentSelectedTile(0);
	}

}

void ATileGameManager::CurrentSelectedTile(int ScrollAmount)
{
	if (TileTypes.Num() == 0) return;

	if (ScrollAmount > 0) {
		CurrentTileIndex = (CurrentTileIndex + 1) % TileTypes.Num();
	}
	else if (ScrollAmount < 0) {
		CurrentTileIndex--;
		if (CurrentTileIndex < 0) CurrentTileIndex = TileTypes.Num() - 1;
	}

	Current_Tile->SetStaticMesh(TileTypes[CurrentTileIndex]->BaseMesh);

	FTransform TileRelTransform = TileTypes[CurrentTileIndex]->InstancedMesh->GetRelativeTransform();
	FTransform TileSelRotTransfrom = FTransform(FRotator(0.0, TileRotation, 0.0));

	Current_Tile->SetRelativeTransform(TileSelRotTransfrom * TileRelTransform);
}

