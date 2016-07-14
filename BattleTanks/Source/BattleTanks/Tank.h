// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward Declarations
class UTankBarrel;
class UTankAimingComponent;
class UTankMovementComponent;
class AProjectile;


UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()
public:
    //getters
    UFUNCTION(BlueprintCallable, Category = Setup)
    void SetBarrelReference(UTankBarrel* BarrelToSet);
    
    
    UFUNCTION(BlueprintCallable, Category = Setup)
    void SetTurretReference(UTankTurret* TurretToSet);
    
    
    void AimAt(FVector HitLocation);
    
    
    UFUNCTION(BlueprintCallable, Category = Firing)
    void Fire();
    
protected:
    UPROPERTY(BlueprintReadOnly)
    UTankMovementComponent* TankMovementComponent = nullptr;
    
    
    UTankAimingComponent* TankAimingComponent = nullptr;
    
private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

 	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	
    UPROPERTY(EditDefaultsOnly, Category = Setup)
    TSubclassOf<AProjectile> ProjectileBlueprint;
    
    UPROPERTY(EditDefaultsOnly, Category = Firing)
    float LaunchSpeed = 40000.f;//find sensible default
	
    
    UPROPERTY(EditDefaultsOnly, Category = Firing)
    float ReloadTimeInSeconds = 3.f;
    
    
    //local reference for spawning projectile
    UTankBarrel* Barrel = nullptr;
    
    double LastFireTime = 0;

};