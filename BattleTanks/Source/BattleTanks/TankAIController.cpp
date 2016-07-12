// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Tank.h"
#include "TankAIController.h"





void ATankAIController::BeginPlay(){
    
    Super::BeginPlay();
    
    auto PlayerTank = GetPlayerTank();
    if(!PlayerTank){
        UE_LOG(LogTemp, Warning, TEXT("AI tank cannot find player tank"));
    }
    else{
        UE_LOG(LogTemp, Warning, TEXT("AIController found: %s"), *(PlayerTank->GetName()));
    }
    //UE_LOG(LogTemp, Warning, TEXT("AIController begin play"));
}
void ATankAIController::Tick(float DeltaTime){
    
    Super::Tick(DeltaTime);
    if(GetPlayerTank()){
        //move towards the player
        //aim towards the player
        GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
        //
    }
    
}

ATank* ATankAIController::GetControlledTank() const{
    {
        return Cast<ATank>(GetPawn());
    }
}

ATank* ATankAIController::GetPlayerTank() const{
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if(!PlayerPawn){return nullptr;}
    return Cast<ATank>(PlayerPawn);
    
}

