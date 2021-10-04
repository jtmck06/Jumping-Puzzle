// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "MovingTiles.generated.h"

UCLASS()
class GAMEDEMO_API AMovingTiles : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingTiles();

	//float value that determines...
	UPROPERTY(EditAnywhere)
	UCurveFloat* MovementCurve;

	FVector StartPoint;
	FVector EndPoint;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PuzzleStartEventFunction();

	//reference to APuzzleStarter that contains the delegate  that will allow the tiles to move once the character steps on it 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class APuzzleStarter* PuzzleStarterRef;

	//Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* Tile;

	//Updates the Tile's relative location
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UTimelineComponent* TimelineComponent;

	FOnTimelineFloat MovementValue;
	FOnTimelineEvent TimelineResetEvent;

	//Function For when the Timeline runs initially 
	UFUNCTION()
	void TimelineBegin(float Value);

	//Function for resetting the timeline once it hits the endpoint
	UFUNCTION()
	void TimelineReverse();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
