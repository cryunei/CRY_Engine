#pragma once


#include "Dx11Buffer.h"
#include "../Core/Dx11Device.h"
#include "../DxTypes.h"


//=====================================================================================================================
// @brief	Dx11VertexBuffer
//=====================================================================================================================
class Dx11VertexBuffer : public Dx11Buffer
{
    CLASS_DEFAULT_BODY( Dx11VertexBuffer )

private:
    unsigned int             Count;             // vertex count
    unsigned int             Stride;            // vetex sturct size
    unsigned int             Offset;            // draw start offset
    D3D11_PRIMITIVE_TOPOLOGY PrimitiveTopology; // draw primitive topology type

public:
    // Construct
    Dx11VertexBuffer() = default;

    // Create buffer
    template< typename T >
    void CreateBuffer( const std::vector< T >& Vertices, D3D11_USAGE Usage, D3D11_CPU_ACCESS_FLAG CpuAccess );

    // Set render state
    virtual bool SetRenderState( int InRegisterIndex ) const override;

    // Getters
    unsigned int GetCount() const { return Count; }
};


//=====================================================================================================================
// @brief	Create
//=====================================================================================================================
template< typename T >
void Dx11VertexBuffer::CreateBuffer( const std::vector< T >& Vertices, D3D11_USAGE Usage, D3D11_CPU_ACCESS_FLAG CpuAccess )
{
    if ( Vertices.empty() ) return;

    Count = (unsigned int)( Vertices.size() );
    Stride = sizeof( T );
    Offset = 0; 
    unsigned int bufferSize = Stride * Count;

    BufferDesc.Usage = Usage;
    BufferDesc.ByteWidth = bufferSize;
    BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    BufferDesc.CPUAccessFlags = CpuAccess;

    Create( nullptr );

    D3D11_MAPPED_SUBRESOURCE ms;
    GetDx11DeviceContext()->Map( GetBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &ms );
    {
        memcpy( ms.pData, &Vertices[ 0 ], bufferSize );
    }
    GetDx11DeviceContext()->Unmap( GetBuffer(), 0 );

    PrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}
