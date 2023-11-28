#include "CrActor.h"


//=====================================================================================================================
// @brief	Tick
//=====================================================================================================================
void CrActor::Tick( float DeltaTime )
{
    Transform.Rotate( Quaternion::CreateFromAxisAngle( Vector3::Up, DeltaTime * 0.5f ) );
}
