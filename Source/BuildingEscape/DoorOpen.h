// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "DoorOpen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UDoorOpen : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpen();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(BlueprintAssignable) FDoorEvent OnOpenRequest;
	UPROPERTY(BlueprintAssignable) FDoorEvent OnCloseRequest;

private :
	float GetTotalMassOverlappingActors();

private :
	//float LastDoorCloseTime;
	UPROPERTY(EditAnywhere) float TriggerMass;
	//UPROPERTY(EditAnywhere) float DoorCloseTime;
	UPROPERTY(EditAnywhere) float OpenAngle;
	UPROPERTY(EditAnywhere) ATriggerVolume* TriggerVolume;
	//Pawn Inherits from Actor
	UPROPERTY(VisibleAnywhere) AActor* PawnActor;
	AActor* Owner;
};
