#pragma once


#include "../CrActor.h"


class CrDirectionalLight : public CrActor
{
private:
    Vector3 Direction;
    Vector3 Color;

public:
    // Construct
    CrDirectionalLight();

    // Set direction
    void SetDirection( const Vector3& direction ) { Direction = direction; }

    // Set color
    void SetColor( const Vector3& color ) { Color = color; }

    // Get direction
    Vector3 GetDirection() const;

    // Get color
    Vector3 GetColor() const;
};
