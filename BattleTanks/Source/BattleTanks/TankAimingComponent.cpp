//Copyright Brolol Games

#include "BattleTanks.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

EFiringStatus UTankAimingComponent::GetFiringStatus(){
    return FiringState;
}
void UTankAimingComponent::BeginPlay(){
    //First fire is after the start of play
     LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction){
    if((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds){
        FiringState = EFiringStatus::Reloading;
    }
    else if(IsBarrelMoving()){
        FiringState = EFiringStatus::Locked;
    }else{
        FiringState = EFiringStatus::Firing;
    }
}

bool UTankAimingComponent::IsBarrelMoving(){
    if(!Barrel) {return false;}
    auto BarrelForward = Barrel->GetForwardVector();
    return !BarrelForward.Equals(AimDirection, .1);
    
}
void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet){
 
    Barrel = BarrelToSet;
    Turret = TurretToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation){
    if(!ensure(Barrel)) {return;}
    
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
        AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrelTowards(AimDirection);
    }
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirecton){
    
    if(!ensure(Barrel) || !ensure(Turret)){ return ; }
  //  UE_LOG(LogTemp, Warning, TEXT("I'm here"))
    //Work out the difference between barrel and aim direction
    auto RotationWithoutRoll = FQuat::FindBetween(Barrel->GetForwardVector(), AimDirecton);
    auto DeltaRotator = RotationWithoutRoll.Rotator();
    
    
    //Always yaw the shortest way
    Barrel->Elevate(DeltaRotator.Pitch);
    if(FMath::Abs(DeltaRotator.Yaw) < 180){
        Turret->Rotate(DeltaRotator.Yaw);
    }else{
        Turret->Rotate(-DeltaRotator.Yaw);
    }
}


void UTankAimingComponent::Fire(){
    
    if(FiringState != EFiringStatus::Reloading){
        if(!ensure(Barrel)){return ;}
        if(!ensure(ProjectileBlueprint)){return ; }
        
        //spawn a projectile at the socket
        
        
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(
                                                              ProjectileBlueprint,
                                                              Barrel->GetSocketLocation(FName("Projectile")),
                                                              Barrel->GetSocketRotation(FName("Projectile"))
                                                              );
        
        Projectile->LaunchProjectile(LaunchSpeed);
        LastFireTime = FPlatformTime::Seconds();
    }
}