// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
    
public: 
    ATank* GetControlledTank() const;
	
    virtual void BeginPlay() override;
    
    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;

private:
    //Start the tank moving barrel so that the crosshair would hit where the tank is aiming
    void AimTowardsCrosshair();
    bool GetSightRayHitLocation(FVector& HitLocation) const;
    
    UPROPERTY(EditAnywhere)
    float CrossHairXLocation = 0.5f;
    UPROPERTY(EditAnywhere)
    float CrossHairYLocation = 0.33333;
    
};
