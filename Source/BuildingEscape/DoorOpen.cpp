// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorOpen.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UDoorOpen::UDoorOpen()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	OpenAngle = 90.0f;
	TriggerMass = 0.0f;
}


// Called when the game starts
void UDoorOpen::BeginPlay()
{
	Super::BeginPlay();
	PawnActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	Owner = GetOwner();
}

float UDoorOpen::GetTotalMassOverlappingActors() {
	float TotalMassActors = 0.0f;
	TArray<AActor*> OverlappingActors;
	TriggerVolume->GetOverlappingActors(OverlappingActors);
	for (const AActor* const Actor : OverlappingActors) {
		UPrimitiveComponent *PrimitiveComponent = Actor->FindComponentByClass<UPrimitiveComponent>();
		if (PrimitiveComponent == nullptr) {
			continue;
		}
		TotalMassActors += PrimitiveComponent->GetMass();
	}
	return TotalMassActors;
}

// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//Poll the door events.
	//TODO: Create a variable for threshold 
	if (GetTotalMassOverlappingActors() >= TriggerMass) {
		OnOpenRequest.Broadcast();
		///We don't require time checking since now we have moved on to Blueprints.
		//LastDoorCloseTime = GetWorld()->GetTimeSeconds();
	}
	else {
		OnCloseRequest.Broadcast();
	}

	//Not required since not using time.
	/*if (GetWorld()->GetTimeSeconds() - LastDoorCloseTime >= DoorCloseTime) {
		CloseDoor();
	}*/
}

