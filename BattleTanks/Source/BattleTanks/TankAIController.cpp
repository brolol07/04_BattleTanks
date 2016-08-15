// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Tank.h"//So we can implement OnDeath
#include "TankAimingComponent.h"
#include "TankAIController.h"
//depends on movement component for AI pathfinding system




void ATankAIController::BeginPlay(){
    
    Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn) {
    Super::SetPawn(InPawn);
    
    if(InPawn){
        auto PossesedTank = Cast<ATank>(InPawn);
        
        if(!ensure(PossesedTank) ) {return;}
        PossesedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
    }
}

void ATankAIController::OnPossedTankDeath(){
    if(!GetPawn()){return; }
    GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick(float DeltaTime){
    
    Super::Tick(DeltaTime);
    
    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    
    auto ControlledTank = GetPawn();
    
    if(!ensure(PlayerTank && ControlledTank)){return ; }
        
        //move towards player
        MoveToActor(PlayerTank, AcceptanceRadius);
        //aim towards the player
    auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
        AimingComponent->AimAt(PlayerTank->GetActorLocation());
        //Fire if ready
    if(AimingComponent->GetFiringStatus() == EFiringStatus::Locked)
    {
    AimingComponent->Fire();
    }
}


