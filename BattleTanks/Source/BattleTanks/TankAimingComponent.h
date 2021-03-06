//Copyright Brolol Games
#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


//Enum for aiming state
UENUM()

enum class EFiringStatus : uint8
{
    Firing, Reloading, Locked, OutOfAmmo
};

//Foward Declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

//Holds barrels property's and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
    
    void AimAt(FVector HitLocation);
    
    UFUNCTION(BlueprintCallable, Category = "Firing")
    void Fire();
    
    EFiringStatus GetFiringStatus();
    
    UFUNCTION(BlueprintCallable, Category = "Firing")
    int32 GetRoundsLeft() const ;

protected:
    
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFiringStatus FiringState = EFiringStatus::Reloading;
    
private:
    // Sets default values for this component's properties
    UTankAimingComponent();
    
    
    virtual void BeginPlay() override;
    
    
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
    
    void MoveBarrelTowards(FVector AimDirection);
    
    bool IsBarrelMoving();
    
    UTankBarrel* Barrel = nullptr;
    
    UTankTurret* Turret = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;
    //firing properties
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 40000.f; 

    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ReloadTimeInSeconds = 3.f;
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    int32 RoundsLeft = 3;
    
    FVector AimDirection;
    
    double LastFireTime = 0;

    };
