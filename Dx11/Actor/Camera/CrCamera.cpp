#include "CrCamera.h"


//=================================================================================================
// @brief	Constructor
//=================================================================================================
CrCamera::CrCamera()
: LookAtDirection( Vector3::Forward )
, FovDegree      ( 45.f )
, NearDistance   ( 0.1f )
, FarDistance    ( 10000.f )
{
}

//=================================================================================================
// @brief	Set look at direction
//=================================================================================================
void CrCamera::SetLookAtDirection( const Vector3& direction )
{
    LookAtDirection = direction;
}

//=================================================================================================
// @brief	Get view matrix
//=================================================================================================
Matrix CrCamera::GetViewMatrix() const
{
    const Vector3& location = Transform.GetLocation();
    return Matrix::CreateLookAt( location, location + LookAtDirection, Vector3::Up );
}

//=================================================================================================
// @brief	Get projection matrix
//=================================================================================================
Matrix CrCamera::GetProjectionMatrix( float ViewportWidth, float ViewportHeight ) const
{
    //return Matrix::Identity;
    return Matrix::CreatePerspectiveFieldOfView( DirectX::XMConvertToRadians( FovDegree ), ViewportWidth / ViewportHeight, NearDistance, FarDistance );
}
