// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    //-1 is min speed and 1 is max speed
    void Elevate(float RelativeSpeed);
	
private:
    UPROPERTY(EditAnywhere, Category = Setup)
    float MaxDegreesPerSecond =  5;
	
    
    UPROPERTY(EditAnywhere, Category = Setup)
    float MaxElevationDegrees =  40;
    
    
    UPROPERTY(EditAnywhere, Category = Setup)
    float MinElevationDegrees =  0;
};
