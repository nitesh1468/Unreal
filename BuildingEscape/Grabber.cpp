// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	CheckPhysicsHandle();
	BindInputAction();
}

void UGrabber::CheckPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no Physics Handle Component!"), *GetOwner()->GetName());
	}
}

void UGrabber::BindInputAction()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if(InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no Input Component!"), *GetOwner()->GetName());
	}
}
void UGrabber::Grab()
{
	FHitResult HitResult;
	HitResult = GetPhysicsBodyInReach();
	if(PhysicsHandle && HitResult.GetActor())
	{
		PhysicsHandle->GrabComponentAtLocation(HitResult.GetComponent(),NAME_None, GetTraceLineEnd());	
	}	
}

void UGrabber::Release()
{
	PhysicsHandle->ReleaseComponent();	
}

FVector UGrabber::GetTraceLineEnd()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT ViewLocation, OUT ViewRotation);
	return ViewLocation + Reach * ViewRotation.Vector();
}

FHitResult UGrabber::GetPhysicsBodyInReach()
{
	TraceLineEnd = GetTraceLineEnd();
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	//To see a debug Line
	//DrawDebugLine(GetWorld(), ViewLocation, TraceLineEnd, FColor(0, 0, 128), false, 0.f, 0, 3.5f);

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		ViewLocation,
		TraceLineEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams	
	);
	return Hit;
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(PhysicsHandle && PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetTraceLineEnd());
	}	
}

