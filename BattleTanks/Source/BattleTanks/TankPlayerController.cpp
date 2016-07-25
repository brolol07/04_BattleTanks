// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if(!AimingComponent) {return ;}
    {
    FoundAimingComponent(AimingComponent);
    }
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick( DeltaTime );
    AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if(!GetPawn()){return ;};//example if not possesing
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if(!AimingComponent) {return ;}
    
    FVector HitLocation; // Out parameter
    bool bGetHitLocation = GetSightRayHitLocation(HitLocation);
    
    
    if (bGetHitLocation) // Has "side-effect", is going to line trace
    {
     //   UE_LOG(LogTemp, Warning, TEXT("Hit location: %s"), *HitLocation.ToString());
        
        AimingComponent->AimAt(HitLocation);
    }
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
    // Find the crosshair position in pixel coordinates
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation
                                    );
    
    // "De-project" the screen position of the crosshair to a world direction
    FVector LookDirection;
    if (GetLookDirection(ScreenLocation, LookDirection))
    {
        // Line-trace along that LookDirection, and see what we hit (up to max range)
       return GetLookVectorHitLocation(LookDirection, HitLocation);
    }
    
    return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
    if (GetWorld()->LineTraceSingleByChannel(
                                             HitResult,
                                             StartLocation,
                                             EndLocation,
                                             ECollisionChannel::ECC_Visibility)
        )
    {
        HitLocation = HitResult.Location;
        return true;
    }
    HitLocation = FVector(0);
    return false; // Line trace didn't succeed
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const{
    FVector CameraWorldLocation; // To be discarded
    return  DeprojectScreenPositionToWorld(
                                           ScreenLocation.X,
                                           ScreenLocation.Y, 
                                           CameraWorldLocation,
                                           LookDirection
                                           );
}