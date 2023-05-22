#pragma once


#include "../CrActor.h"


class CrCamera : public CrActor
{
public:
    // Get view projection matrix
    Matrix GetViewProjectionMatrix();
};
