// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleStarter.h"
#include "Components/BoxComponent.h"


// Sets default values
APuzzleStarter::APuzzleStarter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PuzzleStarter = CreateDefaultSubobject<UBoxComponent>(TEXT("PuzzleStarter"));
	PuzzleStarter ->SetBoxExtent(FVector(64.f, 64.f, 32.f));
	PuzzleStarter -> SetVisibility(true);
}

// Called when the game starts or when spawned
void APuzzleStarter::BeginPlay()
{
	Super::BeginPlay();
	
}
//signals other Actor classes when the event has been executed.
void APuzzleStarter::HandlePuzzleStartEvent()
{
	OnPuzzleStart.ExecuteIfBound();
}

void APuzzleStarter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	HandlePuzzleStartEvent();
}

// Called every frame
void APuzzleStarter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}




