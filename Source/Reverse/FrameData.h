#pragma once
#include "Math/Vector.h"
#include "Math/Rotator.h"

struct FFrameData
{
    // object's attributes to save
    FVector ObjectLocatoin; // object's location
    FRotator ObjecRotation; // object's rotation
    FVector ObjecLinearVelicity;  // object's linear velocity
    FVector ObjecAngularVelocity; // object's angular velocity

    //  store deltatime to know how much time passes between frames
    float DeltaTime;

    FORCEINLINE FFrameData();
    FORCEINLINE FFrameData(FVector Location, FRotator Rotation, FVector LinearVelicity, FVector AngularVelocity, float DeltaTime); // pass info into constructor

};

FFrameData::FFrameData()
{

}

FFrameData::FFrameData(FVector Location, FRotator Rotation, FVector LinearVelicity, FVector AngularVelocity, float DeltaTime) : ObjectLocatoin(Location),
ObjecRotation(Rotation), ObjecLinearVelicity(LinearVelicity), ObjecAngularVelocity(AngularVelocity)
{

}