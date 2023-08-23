#pragma once


#include "../CrActor.h"


class CrDirectionalLight : public CrActor
{
private:
    Vector3 Direction;
    Vector4 Color;

public:
    // Construct
    CrDirectionalLight();

    // Set direction
    void SetDirection( const Vector3& direction ) { Direction = direction; }

    // Set color
    void SetColor( const Vector4& color ) { Color = color; }

    // Get direction
    Vector3 GetDirection() const { return Direction; }

    // Get color
    Vector4 GetColor() const { return Color; }
};
