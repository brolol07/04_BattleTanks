// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankTracks.h"
#include "TankMovementComponent.h"



void UTankMovementComponent::Initialize(UTankTracks* LeftTrackToSet, UTankTracks* RightTrackToSet){
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
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