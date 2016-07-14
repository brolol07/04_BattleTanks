//Copyright Brolol Games

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"


//Forward Declarations
class UTankTracks;

/**
 * Initialize of the tank movements
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
	
public:
    
    
    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialize(UTankTracks* LeftTrackToSet, UTankTracks* RightTrackToSet);
    
    UFUNCTION(BlueprintCallable, Category = "Input")
    void IntendMoveForward(float Throw);
    
    UFUNCTION(BlueprintCallable, Category = "Input")
    void IntendTurnRight(float Throw);
    
private:
    //Called from the pathfinding logic by the AI controllers/
    virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
    
    UTankTracks* LeftTrack = nullptr;
    UTankTracks* RightTrack = nullptr;
    
};
