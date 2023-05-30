#pragma once


#include "../../Externals/DirectXTK/Inc/SimpleMath.h"
#include <d3d11.h>


using namespace DirectX::SimpleMath;


class DxTransform
{
private:
    Vector3    Location;
    Quaternion Rotation;
    Vector3    Scale;

public:
    // Construct
    DxTransform();

    // Get location
    inline const Vector3& GetLocation() const { return Location; }

    // Set location
    inline void SetLocation( float X, float Y, float Z ) { Location.x = X; Location.y = Y; Location.z = Z; }

    // Set location x, y, z
    inline void SetLocationX( float V ) { Location.x = V; }
    inline void SetLocationY( float V ) { Location.y = V; }
    inline void SetLocationZ( float V ) { Location.z = V; }

    // Rotate
    inline void SetRotation( float X, float Y, float Z ) { Rotation = Quaternion::CreateFromYawPitchRoll( X, Y, Z ); }

    // Set location x, y, z
    inline void SetRotationX( float V ) { const Vector3& euler = Rotation.ToEuler(); Rotation = Quaternion::CreateFromYawPitchRoll( V, euler.y, euler.z ); }
    inline void SetRotationY( float V ) { const Vector3& euler = Rotation.ToEuler(); Rotation = Quaternion::CreateFromYawPitchRoll( euler.x, V, euler.z ); }
    inline void SetRotationZ( float V ) { const Vector3& euler = Rotation.ToEuler(); Rotation = Quaternion::CreateFromYawPitchRoll( euler.x, euler.y, V ); }

    // Set scale
    inline void SetScale( float X, float Y, float Z ) { Scale.x = X; Scale.y = Y; Scale.z = Z; }

    // Set scale x, y, z
    inline void SetScaleX( float V ) { Scale.x = V; }
    inline void SetScaleY( float V ) { Scale.y = V; }
    inline void SetScaleZ( float V ) { Scale.z = V; }

    // To local matrix
    Matrix ToLocalMatrix() const;

    // Get world matrix
    Matrix GetWorldMatrix() const;
};
