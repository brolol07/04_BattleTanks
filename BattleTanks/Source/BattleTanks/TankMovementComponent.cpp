//Copyright Brolol Games

#include "BattleTanks.h"
#include "TankTracks.h"
#include "TankMovementComponent.h"



void UTankMovementComponent::Initialize(UTankTracks* LeftTrackToSet, UTankTracks* RightTrackToSet){
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}
void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed){

    //no need to call Super as we're replacing the value of it
    auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
    auto AIForwardIntent = MoveVelocity.GetSafeNormal();
    
    
    auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntent);
    IntendMoveForward(ForwardThrow);
    
    auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntent).Z;
    
    IntendTurnRight(RightThrow);
}

void UTankMovementComponent::IntendMoveForward(float Throw){
    if (!LeftTrack || !RightTrack) {return ;  }
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw){
    if (!LeftTrack || !RightTrack) {return ;  }
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
}