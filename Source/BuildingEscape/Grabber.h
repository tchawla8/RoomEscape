// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//Grab the Object.
	void Grab();
	//Release the Object.
	void Release();
	void FindPhysicsHandleComponent();
	void SetupInputComponent();
	//Get The first Physics Body after LineTrace.
	FHitResult FindFirstPhysicsBody();
	//Get End Location of Raycast.
	FVector GetReachLineEnd();
	//Get player viewpoint start location.
	FVector GetReachLineStart();

private:
	UPhysicsHandleComponent* PhysicsHandle;
	UInputComponent* InputComponent;
	FVector OutPosition;
	FRotator OutRotation;
	UPROPERTY(EditAnywhere)
	float LineTraceReach;
	
};
