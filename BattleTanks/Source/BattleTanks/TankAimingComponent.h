//Copyright Brolol Games
#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


//Enum for aiming state
UENUM()

enum class EFiringStatus : uint8
{
    Firing, Reloading, Locked
};

//Foward Declaration
class UTankBarrel;
class UTankTurret;

//Holds barrels property's and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
    
    void AimAt(FVector HitLocation);
	
protected:
    
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFiringStatus FiringState = EFiringStatus::Locked;
    
private:
    // Sets default values for this component's properties
    UTankAimingComponent();
    
    UTankBarrel* Barrel = nullptr;
    
    UTankTurret* Turret = nullptr;
    
    void MoveBarrelTowards(FVector AimDirection);
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 40000.f;
};
