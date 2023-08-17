#include "CrCamera.h"


//=====================================================================================================================
// @brief	Constructor
//=====================================================================================================================
CrCamera::CrCamera()
: LookAtDirection( Vector3::Forward )
, FovDegree      ( 45.f )
, NearDistance   ( 0.1f )
, FarDistance    ( 10000.f )
{
}

//=====================================================================================================================
// @brief	Set look at direction
//=====================================================================================================================
void CrCamera::SetLookAtDirection( const Vector3& direction )
{
    LookAtDirection = direction;
}

//=====================================================================================================================
// @brief	Look at location
//=====================================================================================================================
void CrCamera::LookAt( const Vector3& location )
{
    const Vector3& to = location - Transform.GetLocation();
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
    return Matrix::CreateLookAt( location, location + lookAt, Vector3::Up );
}

//=====================================================================================================================
// @brief	Get projection matrix
//=====================================================================================================================
Matrix CrCamera::GetProjectionMatrix( float ViewportWidth, float ViewportHeight ) const
{
    //return Matrix::Identity;
    return Matrix::CreatePerspectiveFieldOfView( DirectX::XMConvertToRadians( FovDegree ), ViewportWidth / ViewportHeight, NearDistance, FarDistance );
}
