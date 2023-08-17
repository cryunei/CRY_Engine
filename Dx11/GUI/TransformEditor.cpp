#include "TransformEditor.h"
#include "imgui.h"
#include "../Core/DxTransform.h"

//=====================================================================================================================
// @brief	Constructor
//=====================================================================================================================
TransformEditor::TransformEditor()
: BindTransformPtr ( nullptr )
{
    
}

//=====================================================================================================================
// @brief	Bind transform
//=====================================================================================================================
void TransformEditor::BindTransform( DxTransform* InTransform )
{
    BindTransformPtr = InTransform;

    Sync();
}

//=====================================================================================================================
// @brief	Sync
//=====================================================================================================================
void TransformEditor::Sync()
{
    if ( !BindTransformPtr ) return;

    const Vector3& location = BindTransformPtr->GetLocation();
    Location[ 0 ] = location.x;
    Location[ 1 ] = location.y;
    Location[ 2 ] = location.z;

    const Vector3& rotation = BindTransformPtr->GetRotation().ToEuler();
    Rotation[ 0 ] = rotation.x;
    Rotation[ 1 ] = rotation.y;
    Rotation[ 2 ] = rotation.z;

    const Vector3& scale = BindTransformPtr->GetScale();
    Scale[ 0 ] = scale.x;
    Scale[ 1 ] = scale.y;
    Scale[ 2 ] = scale.z;
}

//=====================================================================================================================
// @brief	Render
//=====================================================================================================================
void TransformEditor::Render()
{
    if ( ImGui::InputFloat3( "Location", Location ) )
    {
        if ( !BindTransformPtr ) return;

        BindTransformPtr->SetLocation( Location[ 0 ], Location[ 1 ], Location[ 2 ] );
    }

    if ( ImGui::InputFloat3( "Rotation", Rotation ) )
    {
        if ( !BindTransformPtr ) return;

        BindTransformPtr->SetRotation( Rotation[ 0 ], Rotation[ 1 ], Rotation[ 2 ] );
    }

    if ( ImGui::InputFloat3( "Scale", Scale ) )
    {
        
    }
}
