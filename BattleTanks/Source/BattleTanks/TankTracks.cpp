// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankTracks.h"


UTankTracks::UTankTracks(){
    PrimaryComponentTick.bCanEverTick =false;
}



void UTankTracks::BeginPlay(){
    OnComponentHit.AddDynamic(this, &UTankTracks::OnHit);
}


void UTankTracks::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit){
    DriveTrack();
    ApplySidewaysForce();
    CurrentThrottle = 0;
}


void UTankTracks::ApplySidewaysForce(){
    
    auto DeltaTime = GetWorld()->GetDeltaSeconds();
    auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
    //Work-put the required acceleration to correct this in this frame
    auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
    //Calculate friction
    auto TankRoot =Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //two tracka
    TankRoot->AddForce(CorrectionForce);
}

void UTankTracks::SetThrottle(float Throttle){
    CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTracks::DriveTrack(){
    auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot =Cast<UPrimitiveComponent> (GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}