// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet){
    
    if(!BarrelToSet){return ; }
    
    Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet){
    
    if(!TurretToSet){return ; }
    
    Turret = TurretToSet;
}
void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed){
    if(!Barrel) {return;}
    
    FVector OutLaunchVelocity;
    FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
                                                   this,
                                                   OutLaunchVelocity,
                                                   StartLocation,
                                                   HitLocation,
                                                   LaunchSpeed,
                                                   false,
                                                   0,
                                                   0,
                                                   ESuggestProjVelocityTraceOption::DoNotTrace //comment this line to produce bug
                                                                        );
    if(bHaveAimSolution)
    {
        auto AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrelTowards(AimDirection);
        auto Time = GetWorld()->GetTimeSeconds();
        UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), Time)

    }else{
        auto Time = GetWorld()->GetTimeSeconds();
        UE_LOG(LogTemp, Warning, TEXT("%f: No aim solution found"), Time)

    }
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirecton){
    
    //Work out the difference between barrel and aim direction
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator =  AimDirecton.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;
//    UE_LOG(LogTemp, Warning, TEXT("AimAsRotator is %s"), *AimAsRotator.ToString())
    Barrel->Elevate(DeltaRotator.Pitch);
    Turret->Rotate(DeltaRotator.Yaw);
}
