// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleStarter.generated.h"

//Dynamic Delegate used to call desired classes once the event has been executed 
DECLARE_DELEGATE(FOnPuzzleStarterDelegate);

UCLASS()
class GAMEDEMO_API APuzzleStarter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleStarter();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Once Character enters this box the all functions called by the delegate operate
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	class UBoxComponent* PuzzleStarter;

	UFUNCTION()
	void HandlePuzzleStartEvent();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Delegate Initizled for this class 
	FOnPuzzleStarterDelegate OnPuzzleStart;
};
