#include "CrPrimitive.h"
#include "CrAssetManager.h"

//=====================================================================================================================
// @brief	Initialize static primitives
//=====================================================================================================================
void CrPrimitive::InitializeStaticPrimitives()
{
    CrPrimitive* plane = GetAssetManager()->CreatePrimitive( "Plane" );
    if ( plane )
    {
        plane->Locations.insert( plane->Locations.end(),
        {
            Vector3( -1.f, -1.f, 0.f ),
            Vector3( -1.f,  1.f, 0.f ),
            Vector3(  1.f,  1.f, 0.f ),
            Vector3(  1.f, -1.f, 0.f )
        } );

        plane->UVs.insert( plane->UVs.end(),
        {
            Vector2( 0.f, 1.f ),
            Vector2( 0.f, 0.f ),
            Vector2( 1.f, 0.f ),
            Vector2( 1.f, 1.f )
        } );

        plane->Normals = std::vector< Vector3 >( 4, Vector3( 0.f, 0.f, -1.f ) );

        plane->Indices.insert( plane->Indices.end(),
        {
            0, 1, 2,
            3, 0, 2
        } );
    }
}

//=====================================================================================================================
// @brief	Contructor
//=====================================================================================================================
CrPrimitive::CrPrimitive()
: Dx11Usage         ( D3D11_USAGE_DYNAMIC )
, Dx11CpuAccessFlag ( D3D11_CPU_ACCESS_WRITE )
{
}

//=====================================================================================================================
// @brief	C:\Project\CRY_Engine\Dx11\Asset\CrVertexBuffer.h
//=====================================================================================================================
void CrPrimitive::Reserve( int NumVertices )
{
    Locations .reserve( NumVertices );
    UVs       .reserve( NumVertices );
    Normals   .reserve( NumVertices );
    Tangents  .reserve( NumVertices );
    Bitangents.reserve( NumVertices );
}

//=====================================================================================================================
// @brief	Get vertices
//=====================================================================================================================
void CrPrimitive::GetVertices( std::vector< Vertex_Diffuse >& OutVertices ) const
{
    OutVertices.clear();
    OutVertices.reserve( Locations.size() );

    for ( size_t i = 0; i < Locations.size(); ++i )
    {
        Vertex_Diffuse Vertex;
        Vertex.Position  = Locations[ i ];
        Vertex.TextureUV = UVs      [ i ];
        Vertex.Normal    = Normals  [ i ];

        OutVertices.emplace_back( Vertex );
    }
}

//=====================================================================================================================
// @brief	Get vertices
//=====================================================================================================================
void CrPrimitive::GetVertices( std::vector< Vertex_NormalMap >& OutVertices ) const
{
    OutVertices.clear();
    OutVertices.reserve( Locations.size() );

    for ( size_t i = 0; i < Locations.size(); ++i )
    {
        Vertex_NormalMap Vertex;
        Vertex.Position   = Locations [ i ];
        Vertex.TextureUV  = UVs       [ i ];
        Vertex.Normal     = Normals   [ i ];
        Vertex.Tangent    = Tangents  [ i ];
        Vertex.Bitangent  = Bitangents[ i ];

        OutVertices.push_back( Vertex );
    }
}
