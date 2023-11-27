#include "CrCamera.h"


//=====================================================================================================================
// @brief	Set look at direction
//=====================================================================================================================
void CrCamera::SetLookAtDirection( const Vector3& Direction )
{
    LookAtDirection = Direction;
}

//=====================================================================================================================
// @brief	Look at location
//=====================================================================================================================
void CrCamera::LookAt( const Vector3& Location )
{
    const Vector3& to = Location - Transform.GetLocation();
    const Vector3& lookAt = Vector3::Transform( LookAtDirection, Transform.GetRotation() );

    Quaternion rot;
    Quaternion::FromToRotation( lookAt, to, rot );
    Transform.Rotate( rot ); 
}

//=====================================================================================================================
// @brief	Get view matrix
//=====================================================================================================================
Matrix CrCamera::GetViewMatrix() const
{
    const Vector3& location = Transform.GetLocation();
    const Vector3& lookAt = Vector3::Transform( LookAtDirection, Transform.GetRotation() );
    return Matrix::CreateLookAt( location, location + lookAt, Up );
}

//=====================================================================================================================
// @brief	Get projection matrix
//=====================================================================================================================
Matrix CrCamera::GetProjectionMatrix( float ViewportWidth, float ViewportHeight ) const
{
    //return Matrix::Identity;
    return Matrix::CreatePerspectiveFieldOfView( DirectX::XMConvertToRadians( FovDegree ), ViewportWidth / ViewportHeight, NearDistance, FarDistance );
}
