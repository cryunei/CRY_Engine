#pragma once


#include "TransformEditor.h"


class DevTestUI
{
private:
    TransformEditor CameraTransformEditor;

public:
    // Constructor
    DevTestUI();

    // Render
    void Render();

    // Bind camera transform
    void BindCameraTransform( DxTransform* InTransform ) { CameraTransformEditor.BindTransform( InTransform ); }
    
};
