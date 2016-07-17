// Copyright Brolol Games

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward Declarations
class UTankBarrel;
class UTankAimingComponent;
class AProjectile;


UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()
public:
    
    void AimAt(FVector HitLocation);
    
    
    UFUNCTION(BlueprintCallable, Category = "Firing")
    void Fire();
    
protected:
    UPROPERTY(BlueprintReadOnly)
    UTankAimingComponent* TankAimingComponent = nullptr;
    
private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	


	
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;
    
    //TODO remove once firing is moved to aiming component
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 40000.f;//find sensible default
	
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ReloadTimeInSeconds = 3.f;
    
    //local barrel reference
    UTankBarrel* Barrel = nullptr;
    
    double LastFireTime = 0;

};