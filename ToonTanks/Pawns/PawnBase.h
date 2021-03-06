// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Actors/ProjectileBase.h"
#include "Components/CapsuleComponent.h"
#include "ToonTanks/Components/HealthComponent.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"


UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()
private:
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components",meta=(AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComp;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components",meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components",meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components",meta=(AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components",meta=(AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;
	//VARIABLES
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Projectile Type",meta=(AllowPrivateAccess = "true"))
	TSubclassOf<AProjectileBase> ProjectileClass;

	UPROPERTY(EditAnywhere,Category = "Effects")
	UParticleSystem* DeathParticle;
	

public:
	APawnBase();
	void PawnDestroyed();
	virtual void HandleDestruction();

protected:
	void RotateTurret(FVector LookAtTarget);

	void Fire();

	


};
