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
      UE_LOG(LogTemp, Warning, TEXT("Hit location: %s"), *HitLocation.ToString())
        
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
 //   UE_LOG(LogTemp, Warning, TEXT("Screen Location is %s"), *ScreenLocation.ToString())
    //"De-project" the screen position of the crosshair to a world location
    FVector LookDirection;
    if(GetLookDirection(ScreenLocation, LookDirection)){
//        UE_LOG(LogTemp, Warning, TEXT("World direction Location is %s"), *LookDirection.ToString())
        
        //line trace along the look direction, and see what we hit(up to max range)
        GetLookVectorHitLocation(LookDirection, HitLocation);
    }
    
    
    return true;
}
bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const{
    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
    if(GetWorld()->LineTraceSingleByChannel(HitResult,
                                            StartLocation,
                                            EndLocation,
                                            ECollisionChannel::ECC_Visibility)
       ){
        HitLocation = HitResult.Location;
        
       return true;
    } HitLocation = FVector(0);
    return false;//line trace didnt succeed
}
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector LookDirection) const{
    FVector ScreenWorldLocation;//to be disgaurded
 return DeprojectScreenPositionToWorld(ScreenLocation.X,
                                   ScreenLocation.Y,
                                   ScreenWorldLocation,
                                   LookDirection);
}

