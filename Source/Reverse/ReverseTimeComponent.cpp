// Fill out your copyright notice in the Description page of Project Settings.

#include "ReverseTimeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ReverseCharacter.h"

// Sets default values for this component's properties
UReverseTimeComponent::UReverseTimeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	IsReversingTime = false;
	// ...
}


// Called when the game starts
void UReverseTimeComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// get the character
	AReverseCharacter* ReverseTimeEvent = Cast<AReverseCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	ReverseTimeEvent->ReverseTimeEvent.AddDynamic(this, &UReverseTimeComponent::SetReversingTime);
}

void UReverseTimeComponent::SetReversingTime(bool bReversingTime)
{
	IsReversingTime = bReversingTime;
	if (bReversingTime) {
		UE_LOG(LogTemp, Warning, TEXT("Reversing Time"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Stop reversing Time"));
	}

}


// Called every frame
void UReverseTimeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsReversingTime) {
		// storing data

		// TODO: move owner and components to the constructor
		AActor* Owner = GetOwner(); // getting the owner of the component
		TArray<UActorComponent*> Components = Owner->GetComponentsByClass(UStaticMeshComponent::StaticClass()); // getting the static mesh components of the owner

		if (Components.Num() > 0) { // if there're static mesh components
			UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(Components[0]);
			if (StaticMeshComponent) {
				FFrameData FrameData(Owner->GetActorLocation(),  // create new framedata 
					Owner->GetActorRotation(), 
					StaticMeshComponent->GetPhysicsAngularVelocity(), 
					StaticMeshComponent->GetPhysicsLinearVelocity(), 
					DeltaTime);
				if (RecordedTime < 15.0f) { // if recorded time < 15 seconds - add the new Frame Data
					StoredFrameData.AddTail(FrameData);
					RecordedTime += DeltaTime;
					IsOutOfData = false; //since we've just added data
				}
				else { // substracing the oldest FrameData
					while (RunningTime >= 15.0f) {
						auto HeadOfTheList = StoredFrameData.GetHead();
						float HeadDeltaTime = HeadOfTheList->GetValue().DeltaTime;
						StoredFrameData.RemoveNode(HeadOfTheList);
						RecordedTime -= HeadDeltaTime;
					}
					StoredFrameData.AddTail(FrameData); // current frame to save
					RecordedTime += FrameData.DeltaTime;
					IsOutOfData = false;
				}
			}
		}
	}
	else if (!IsOutOfData) {
		//reversing time
		auto Tail = StoredFrameData.GetTail();
		if (Tail) { // if valid
			AActor* Owner = GetOwner(); // setting rotation and location
			Owner->SetActorLocation(Tail->GetValue().ObjectLocatoin);
			Owner->SetActorRotation(Tail->GetValue().ObjecRotation);
			
			TArray<UActorComponent*> Components = Owner->GetComponentsByClass(UStaticMeshComponent::StaticClass()); // getting the static mesh components of the owner
			if (Components.Num() > 0) { // if not empty
				UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(Components[0]);
				if (StaticMeshComponent) {
					StaticMeshComponent->SetPhysicsLinearVelocity(Tail->GetValue().ObjecLinearVelicity); // setting linear velocity
					StaticMeshComponent->SetPhysicsAngularVelocity(Tail->GetValue().ObjecAngularVelocity); // setting angular velocity
				}
			}
			auto Head = StoredFrameData.GetHead();
			if (Head == Tail) { 
				RecordedTime = 0;
				IsOutOfData = true;
			}
			else {
				RecordedTime -= Tail->GetValue().DeltaTime; //subtracting delta time from recorded time
			}
			StoredFrameData.RemoveNode(Tail); // removign the node
		}
	}
}

