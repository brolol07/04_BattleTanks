// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankPlayerController.h"




void ATankPlayerController::BeginPlay(){
    
    Super::BeginPlay();
    
    auto ControlledTank = GetControlledTank();
    if(!ControlledTank){
        UE_LOG(LogTemp, Warning, TEXT("controlled tank isn't accessible"));
    }
    else{
        UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing: %s"), *(ControlledTank->GetName()));
    }
    // UE_LOG(LogTemp, Warning, TEXT("PlayerController begin play"));
}

void ATankPlayerController::Tick(float DeltaTime ){
    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
    //UE_LOG(LogTemp, Warning, TEXT("Hey I'm ticking"))
}


ATank* ATankPlayerController::GetControlledTank() const{
    {
        return Cast<ATank>(GetPawn());
    }
}

void ATankPlayerController::AimTowardsCrosshair(){
    if(!GetControlledTank()){return;}
    
    FVector HitLocation; //out parameter
        if(GetSightRayHitLocation(HitLocation)){//going to line trace
        UE_LOG(LogTemp, Warning, TEXT("Hit location %s"), *HitLocation.ToString())
        
        //if it hits something
            //TODO tell controlledtank to aim at this point
        }
}
//get world location of linetrace through crosshair,  true if hits langscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const{
    HitLocation  = FVector(1.0);
    return true;
    
}