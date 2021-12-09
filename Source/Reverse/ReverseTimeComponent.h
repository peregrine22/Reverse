// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FrameData.h"

#include "ReverseTimeComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class REVERSE_API UReverseTimeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// revesing time when true, collecting data - when false
	bool IsReversingTime;
	
	//out of data, cannot keep reversing
	bool IsOutOfData;

	// time doesn't reverse. keeping track of the time as we going backwards
	float RunningTime; 

	// reversed time. count of the frame data delta times
	float ReverseRunningTime; 

	//total amount of time recorded in FrameData;
	float RecordedTime; // TODO: Move this to a player character and make a variable - "time capacity"

	//data for each frame
	TDoubleLinkedList<FFrameData> StoredFrameData;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Sets default values for this component's properties
	UReverseTimeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void SetReversingTime(bool bReversingTime);

private:


};
