// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Tank.h"
#include "TankAIController.h"
//depends on movement component for AI pathfinding system




void ATankAIController::BeginPlay(){
    
    Super::BeginPlay();
    
}
void ATankAIController::Tick(float DeltaTime){
    
    Super::Tick(DeltaTime);
    
    auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    
    auto ControlledTank = Cast<ATank>(GetPawn());
    
    if(PlayerTank){
        
        //move towards player
        MoveToActor(PlayerTank, AcceptanceRadius);
        //aim towards the player
        ControlledTank->AimAt(PlayerTank->GetActorLocation());
        //Fire if ready
        ControlledTank->Fire();
    }
}

