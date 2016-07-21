// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTracks.generated.h"

/**
 * TankTracks is used to  set maximum driving force and apply forces to the tank.
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTracks : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
    
    
    UFUNCTION(BlueprintCallable, Category = "Input")
    void SetThrottle(float Throttle);

    
    //max force per track, in Newtons
 //   UFunction(EditDefaultsOnly)
    float TrackMaxDrivingForce =45000000.f;
    
private:
    UTankTracks();
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
    
    
    virtual void BeginPlay() override;


    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

};
