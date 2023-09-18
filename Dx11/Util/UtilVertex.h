#pragma once


#include "../Externals/DirectXTK/Inc/SimpleMath.h"


using namespace DirectX::SimpleMath;


//=====================================================================================================================
// @brief	Get tangent and bitangent
//=====================================================================================================================
inline void GetTangentAndBitangents( const Vector3 (&Location)[ 3 ], const Vector2 (&UVs)[ 3 ], Vector3 (&OutTangents)[ 3 ], Vector3 (&OutBitangents)[ 3 ] )
{
    Vector3 edge1 = Location[ 1 ] - Location[ 0 ];
    Vector3 edge2 = Location[ 2 ] - Location[ 0 ];

    Vector2 deltaUV1 = UVs[ 1 ] - UVs[ 0 ];
    Vector2 deltaUV2 = UVs[ 2 ] - UVs[ 0 ];

    float f = 1.0f / ( deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y );

    OutTangents[ 0 ] = f * ( deltaUV2.x * edge1 - deltaUV1.x * edge2 );
    OutTangents[ 0 ].Normalize();

    OutTangents[ 1 ] =OutTangents[ 2 ] = OutTangents[ 0 ];

    OutBitangents[ 0 ] = f * ( -deltaUV2.y * edge1 + deltaUV1.y * edge2 );
    OutBitangents[ 0 ].Normalize();

    OutBitangents[ 1 ] = OutBitangents[ 2 ] = OutBitangents[ 0 ];    
}