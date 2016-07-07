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
     //   UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *HitLocation.ToString())
        
        //if it hits something
            // TODO tell controlledtank to aim at this point
        }
}
//get world location of linetrace through crosshair,  true if hits langscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const{
    
    //Find crosshair position
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
//    UE_LOG(LogTemp, Warning, TEXT("Screen Location is %s"), *ScreenLocation.ToString())
    //"De-project" the screen position of the crosshair to a world location
    //line trace along the look direction, and see what we hit(up to max range)
    
    return true;
    
}