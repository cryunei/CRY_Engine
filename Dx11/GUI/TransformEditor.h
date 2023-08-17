#pragma once


class DxTransform;


//=====================================================================================================================
// @brief	TransformEditor
//=====================================================================================================================
class TransformEditor
{
private:
    DxTransform* BindTransformPtr;

    float Location[ 3 ];
    float Rotation[ 3 ];
    float Scale   [ 3 ];

public:
    // Constructor
    TransformEditor();

    // Render
    void Render();

    // Bind transform
    void BindTransform( DxTransform* InTransform );

    // Sync
    void Sync();

    // Get bind transform
    DxTransform* GetBindTransform() { return BindTransformPtr; }
    
};
