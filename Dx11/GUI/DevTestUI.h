#pragma once


#include "TransformEditor.h"


class DevTestUI
{
private:
    TransformEditor CameraTransformEditor;
    float           LightDirection[ 3 ];

public:
    // Constructor
    DevTestUI();

    // Render
    void Render();

    // Bind camera transform
    void BindCameraTransform( DxTransform* InTransform ) { CameraTransformEditor.BindTransform( InTransform ); }
    
};
