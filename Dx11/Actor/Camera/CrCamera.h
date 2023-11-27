#pragma once


#include "../CrActor.h"


class CrCamera : public CrActor
{
public:
    Vector3 LookAtDirection = Vector3::Forward;
    Vector3 Up              = Vector3::Up;
    float   FovDegree       = 45.f;
    float   NearDistance    = 0.1f;
    float   FarDistance     = 10000.f;

public:
    // Constructor
    CrCamera() = default;

    // Set look at direction
    void SetLookAtDirection( const Vector3& Direction );

    // Set up vector
    void SetUpVector( const Vector3& InUp ) { Up = InUp; }

    // Look at location
    void LookAt( const Vector3& Location );

    // Get view matrix
    Matrix GetViewMatrix() const;

    // Get projection matrix
    Matrix GetProjectionMatrix( float ViewportWidth, float ViewportHeight ) const;
};
