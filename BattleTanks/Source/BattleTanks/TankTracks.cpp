// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankTracks.h"


UTankTracks::UTankTracks(){
    PrimaryComponentTick.bCanEverTick =true;
}

void UTankTracks::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction){
    
    auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
    //Work-put the required acceleration to correct this in this frame
    auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
    //Calculate friction
    auto TankRoot =Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //two tracka
    TankRoot->AddForce(CorrectionForce);
}
void UTankTracks::SetThrottle(float Throttle){
    auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot =Cast<UPrimitiveComponent> (GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}