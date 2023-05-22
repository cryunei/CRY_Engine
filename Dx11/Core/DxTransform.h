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

    // To local matrix
    Matrix ToLocalMatrix() const;
};
