// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingFloors.generated.h"

UCLASS()
class GAMEDEMO_API AMovingFloors : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingFloors();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Box component that will initiate the floors moving once the character collides with it
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FloorSwtich")
	class UBoxComponent* TriggerTile;
	//Meshes
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FloorSwtich")
	class UStaticMeshComponent* FloorSwitch;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FloorSwtich")
	class UStaticMeshComponent* MidFloor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Floor Swtich")
	class UStaticMeshComponent* FinalFloor;

	//Gives the location of the mesh each FVector is tied allocated for the update function
	UPROPERTY(BlueprintReadWrite, Category = "Floor Switch")
	FVector InitialFloorSwitchLocation;

	UPROPERTY(BlueprintReadWrite, Category = "Floor Switch")
	FVector InitialMidFloorLocation;

	UPROPERTY(BlueprintReadWrite, Category = "Floor Switch")
	FVector InitialFinalFloorLocation;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//Functions that will create events that can be called in Blueprints(BP)
	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch")
	void LowerFloorSwitch();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch")
	void RaiseMidFloor();

	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch")
	void RaiseFinalFloor();

	//Functions that create BP nodes that can update the mesh that each is tied to
	UFUNCTION(BlueprintCallable, Category = "Floor Switch")
	void UpdateFloorSwitchLocation(float Z);

	UFUNCTION(BlueprintCallable, Category = "Floor Switch")
	void UpdateMidFloorLocation(float X);

	UFUNCTION(BlueprintCallable, Category = "Floor Switch")
	void UpdateFinalFloorLocation(float Z);
};
