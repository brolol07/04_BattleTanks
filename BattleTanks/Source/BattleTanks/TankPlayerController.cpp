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
    //get world location if linetrace through crosshair
    //if it hits something
        //tell controlledtank to aim at this point
}