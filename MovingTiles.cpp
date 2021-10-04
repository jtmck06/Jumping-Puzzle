// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingTiles.h"
#include "PuzzleStarter.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMovingTiles::AMovingTiles()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Tile->SetupAttachment(RootComponent);

	TimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent"));
}

// Called when the game starts or when spawned
void AMovingTiles::BeginPlay()
{
	Super::BeginPlay();
	
	//Binds Function TimelineBegin to float MovementValue 
	MovementValue.BindDynamic(this, &AMovingTiles::TimelineBegin);

	//Binds function TimelineReset to event TimelineResetEvent
	TimelineResetEvent.BindDynamic(this, &AMovingTiles::TimelineReverse);
	
	//binding float curve to the timeline component
	if (MovementCurve) {
		TimelineComponent->AddInterpFloat(MovementCurve, MovementValue);
	}

	//Calls the resetting function once the timeline has reached its end so it loops
	TimelineComponent->SetTimelineFinishedFunc(TimelineResetEvent);

	//binds delegate of APuzzleStarter to this class
	if (PuzzleStarterRef) {
		PuzzleStarterRef->OnPuzzleStart.BindUObject(this, &AMovingTiles::PuzzleStartEventFunction);
	}

	//Initializes the Start and End points 
	StartPoint = EndPoint = GetActorLocation();
	EndPoint.Y += 500.0f; //the distance the moving tile will go
}

//Once the character interacts with APuzzleStarter the timeline will play
void AMovingTiles::PuzzleStartEventFunction(){
	TimelineComponent->Play();
}

//The interpolation of the class once timeline between the start and endpoints
void AMovingTiles::TimelineBegin(float Value){
	FVector NewLocation = FMath::Lerp(StartPoint, EndPoint, Value);
	SetActorLocation(NewLocation);
}
//Plays the timeline in reverse once it has reached its end or starts it if has not moved 
void AMovingTiles::TimelineReverse(){
	if (TimelineComponent->GetPlaybackPosition() == 0.0f) {
		TimelineComponent->PlayFromStart();
	}
	else {
		TimelineComponent->Reverse();
	}
}

// Called every frame
void AMovingTiles::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

