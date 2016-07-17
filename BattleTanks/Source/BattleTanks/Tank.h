// Copyright Brolol Games

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward Declarations
class UTankBarrel;
class AProjectile;


UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()
public:
    
    
    
    UFUNCTION(BlueprintCallable, Category = "Firing")
    void Fire();
    
private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 40000.f;


	
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;
    
	
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ReloadTimeInSeconds = 3.f;
    
    //local barrel reference
    UTankBarrel* Barrel = nullptr;
    
    double LastFireTime = 0;

};