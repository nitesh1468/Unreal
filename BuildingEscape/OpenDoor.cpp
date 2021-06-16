// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw = InitialYaw + 90.f;
	if(!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the OpenDoor component on it, but no pressureplate set"),*GetOwner()->GetName());
	}
	//PlayerThatOpensDoor = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	//PressurePlate->IsOverlappingActor(PlayerThatOpensDoor)
	if(TotalMassofActors()>=TheresholdMass)
	{
		OpenDoor(DeltaTime);
	}
	else
	{
		if(GetWorld()->GetTimeSeconds()>DoorLastOpened+DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw,TargetYaw, 0.75f* DeltaTime);
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
	if (abs(CurrentYaw-TargetYaw)<2.5f)
	{
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw=FMath::Lerp(CurrentYaw,InitialYaw, 2.f* DeltaTime);
	DoorRotation.Yaw=CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}

float UOpenDoor::TotalMassofActors() const
{
	float TotalMass = 0.f;
	TArray<AActor*> OUT OverlappingActors;
	PressurePlate->GetOverlappingActors(OverlappingActors);
	for(int32 i=0;i<OverlappingActors.Num();i++)
	{
		TotalMass += OverlappingActors[i]->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;

}

