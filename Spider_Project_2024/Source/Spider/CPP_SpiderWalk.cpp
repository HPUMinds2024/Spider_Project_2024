// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_SpiderWalk.h"

int intensityVal = 1;

// Sets default values
ACPP_SpiderWalk::ACPP_SpiderWalk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_SpiderWalk::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_SpiderWalk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_SpiderWalk::stressIncrease() {

	if (intesityVal <= 0){
		// run some sort of reset code to retake baseline and restart the whole experience, since the lowest setting is apparently too high 
	} else{
		intensityVal--;
		// code to make the spider move to the previous zone/bounds for its movement
	}

}

void ACPP_SpiderWalk::stressDecrease(){

	if (intensityVal == intensityMax){

	} else{
		intensityVal++;
		// code to move the spider into its new bounds/region of movement
			// possible other checks for certain intensities on the higher end for different movement entirely
	}

	//some form of code to modify behavior to up the spider's movement's intensity value

}