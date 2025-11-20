// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_SpiderWalk.generated.h"

UCLASS()
class SPIDER_API ACPP_SpiderWalk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_SpiderWalk();

private: 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void stressIncrease();
		// Called when the stress is detected to be above user's usual range
		// used to roll back the intesityVal variable and set it up for the lower stage

	void stressDecrease();
		// Called when the stress is determined to be lower than the user's baseline/inside the baselin
		// Used to increase the intensityVal variable and set it up for the next stage
};
