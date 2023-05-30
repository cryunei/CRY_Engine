#include "CrCamera.h"


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
Matrix CrCamera::GetProjectionMatrix() const
{
    //return Matrix::Identity;
    return Matrix::CreatePerspectiveFieldOfView( 0.25f * 3.1415926535f, 800.f / 600.f, 0.1f, 1000.f );
}
