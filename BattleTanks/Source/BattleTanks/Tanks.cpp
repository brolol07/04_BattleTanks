// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Tanks.h"


// Sets default values
ATanks::ATanks()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATanks::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATanks::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ATanks::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

