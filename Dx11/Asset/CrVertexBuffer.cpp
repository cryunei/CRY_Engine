#include "CrVertexBuffer.h"


//=====================================================================================================================
// @brief	Contructor
//=====================================================================================================================
CrVertexBuffer::CrVertexBuffer()
: Dx11Usage         ( D3D11_USAGE_DYNAMIC )
, Dx11CpuAccessFlag ( D3D11_CPU_ACCESS_WRITE )
{
}

//=====================================================================================================================
// @brief	Get vertices
//=====================================================================================================================
void CrVertexBuffer::GetVertices( std::vector< Vertex_Diffuse >& OutVertices ) const
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
void CrVertexBuffer::GetVertices( std::vector< Vertex_NormalMap >& OutVertices ) const
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
