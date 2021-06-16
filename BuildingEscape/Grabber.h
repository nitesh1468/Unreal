
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#define OUT
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGrabber();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:
	FHitResult OUT Hit;
	UInputComponent* InputComponent = nullptr;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	float Reach = 100.f;
	FVector TraceLineEnd {0.f, 0.f, 0.f};
	FVector OUT ViewLocation;
	FRotator OUT ViewRotation;

	void BindInputAction();
	void CheckPhysicsHandle();
	FHitResult GetPhysicsBodyInReach();
	FVector GetTraceLineEnd();
	void Grab();
	void Release();		
};
