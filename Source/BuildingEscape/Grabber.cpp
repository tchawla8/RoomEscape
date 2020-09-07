// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/PlayerController.h"
#include "Public/DrawDebugHelpers.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PhysicsHandle = nullptr;
	PrimaryComponentTick.bCanEverTick = true;
	LineTraceReach = 100.0f;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();
}

///Look for attached Physics Handle.
void UGrabber::FindPhysicsHandleComponent() {
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Physics Handle Not Attached on Actor"))
	}
}

void UGrabber::SetupInputComponent() {
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (nullptr == InputComponent) {
		UE_LOG(LogTemp, Error, TEXT("Input Component not attached for %s"), *(GetOwner()->GetName()))
	}
	else {
		InputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabber::Release);
		UE_LOG(LogTemp, Warning, TEXT("Input Component Found"))
	}
}

FHitResult UGrabber::FindFirstPhysicsBody()
{
	///Line Tracing Single by Object Type
	FHitResult Hit;
	FCollisionObjectQueryParams ObjectType(ECollisionChannel::ECC_PhysicsBody);
	FCollisionQueryParams QueryParam(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(Hit, GetReachLineStart(), GetReachLineEnd(), ObjectType, QueryParam);
	return Hit;
}

FVector UGrabber::GetReachLineEnd() {
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OutPosition, OutRotation);
	return OutPosition + (OutRotation.Vector() * LineTraceReach);
}

FVector UGrabber::GetReachLineStart() {
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OutPosition, OutRotation);
	return OutPosition;
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed"))
	FHitResult HitResult = FindFirstPhysicsBody();
	AActor* HitActor { HitResult.GetActor() };
	if (HitActor != nullptr) {
		PhysicsHandle->GrabComponent(
			HitResult.GetComponent(),
			NAME_None,
			HitActor->GetActorLocation(),
			true
		);
	}
}

void UGrabber::Release() {
	PhysicsHandle->ReleaseComponent();
	UE_LOG(LogTemp, Warning, TEXT("Grab Released"))
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PhysicsHandle->GrabbedComponent != nullptr) {
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}
}