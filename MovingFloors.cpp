// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingFloors.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMovingFloors::AMovingFloors()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerTile = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerTile"));
	RootComponent = TriggerTile;

	TriggerTile->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerTile->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	TriggerTile->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerTile->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	TriggerTile->SetBoxExtent(FVector(64.f, 64.f, 32.f));

	FloorSwitch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorSwitch"));
	FloorSwitch->SetupAttachment(GetRootComponent());

	MidFloor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MidFloor"));
	MidFloor->SetupAttachment(GetRootComponent());

	FinalFloor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FinalFloor"));
	FinalFloor->SetupAttachment(GetRootComponent());

	
}

// Called when the game starts or when spawned
void AMovingFloors::BeginPlay()
{
	Super::BeginPlay();
	
	//Ties the box component to the overlap function so once the character collides with the component
	//all the BP events are triggerd 
	TriggerTile->OnComponentBeginOverlap.AddDynamic(this, &AMovingFloors::OnOverlapBegin);

	InitialFloorSwitchLocation = FloorSwitch->GetComponentLocation();
	InitialMidFloorLocation = MidFloor->GetComponentLocation();
	InitialFinalFloorLocation = FinalFloor->GetComponentLocation();
}

// Called every frame
void AMovingFloors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMovingFloors::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
	UE_LOG(LogTemp, Warning, TEXT("OverlapBegin"));
	LowerFloorSwitch();
	RaiseMidFloor();
	RaiseFinalFloor();
}

void AMovingFloors::UpdateFloorSwitchLocation(float Z){
	FVector NewLocation = InitialFloorSwitchLocation;
	NewLocation.Z += Z;
	FloorSwitch->SetWorldLocation(NewLocation);
}

void AMovingFloors::UpdateMidFloorLocation(float X){
	FVector NewLocation = InitialMidFloorLocation;
	NewLocation.X += X;
	MidFloor->SetWorldLocation(NewLocation);
}

void AMovingFloors::UpdateFinalFloorLocation(float Z){
	FVector NewLocation = InitialFinalFloorLocation;
	NewLocation.Z += Z;
	FinalFloor->SetWorldLocation(NewLocation);
}

