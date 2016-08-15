// Copyright Brolol Games

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent; 

/**
 * Responsible for helping the player  aim
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
    
protected:
    
    UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
    void FoundAimingComponent(UTankAimingComponent* AimingCompRef);

    UFUNCTION()
    void OnPossedTankDeath();
public:
    
    virtual void BeginPlay() override;
    
    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;

private:
    //Start the tank moving barrel so that the crosshair would hit where the tank is aiming
    void AimTowardsCrosshair();
    
    void StartSpectatingOnly();
    
    bool GetSightRayHitLocation(FVector& HitLocation) const;
    
    void SetPawn(APawn* InPawn);
    
    
    UPROPERTY(EditDefaultsOnly)
    float CrossHairXLocation = 0.5f;
    
    UPROPERTY(EditDefaultsOnly)
    float CrossHairYLocation = 0.33333f;
 
    UPROPERTY(EditDefaultsOnly)
    float LineTraceRange = 1000000.f;
    
    bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
    bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
