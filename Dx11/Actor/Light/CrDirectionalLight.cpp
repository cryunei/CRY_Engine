#include "CrDirectionalLight.h"


//=================================================================================================
// @brief	Construct
//=================================================================================================
CrDirectionalLight::CrDirectionalLight()
: Direction ( Vector3( 1.f, -1.f, 1.f ) )
, Color     ( Vector4( 0.f, 0.15f, 0.3f, 1.f ) )
{
}
