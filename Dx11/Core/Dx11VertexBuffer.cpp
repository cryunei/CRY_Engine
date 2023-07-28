#include "Dx11VertexBuffer.h"
#include "Dx11ResourceFactory.h"
#include "../DxMacros.h"
#include "../Core/Dx11Device.h"

//=====================================================================================================================
// @brief	Construct
//=====================================================================================================================
Dx11VertexBuffer::Dx11VertexBuffer()
: Buffer      ( nullptr )
, Count       ( 0 )
, Stride            ( 0 )
, Offset            ( 0 )
, PrimitiveTopology ( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST )

{
    ZeroMemory( &BufferDesc, sizeof( D3D11_BUFFER_DESC ) );
}

//=====================================================================================================================
// @brief	Create
//=====================================================================================================================
void Dx11VertexBuffer::CreateBuffer( const std::vector< Vertex >& Vertices, D3D11_USAGE Usage, D3D11_CPU_ACCESS_FLAG CpuAccess )
{
    if ( Vertices.empty() ) return;

    Count = (unsigned int)( Vertices.size() );
    Stride = sizeof( Vertex ); 
    unsigned int bufferSize = Stride * Count;

    BufferDesc.Usage = Usage;
    BufferDesc.ByteWidth = bufferSize;
    BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    BufferDesc.CPUAccessFlags = CpuAccess;

    Dx11ResourceFactory::CreateBuffer( &Buffer, &BufferDesc, nullptr );

    D3D11_MAPPED_SUBRESOURCE ms;
    GetDx11DeviceContext()->Map( Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms );
    {
        memcpy( ms.pData, &Vertices[ 0 ], bufferSize );
    }
    GetDx11DeviceContext()->Unmap( Buffer, 0 );
}

//=====================================================================================================================
// @brief	Release
//=====================================================================================================================
void Dx11VertexBuffer::Release()
{
    SAFE_RELEASE( Buffer );

    Count = 0;
}

//=====================================================================================================================
// @brief	Render
//=====================================================================================================================
bool Dx11VertexBuffer::Render() const
{
    if ( Count == 0 ) return false;

    GetDx11DeviceContext()->IASetVertexBuffers( 0, 1, &Buffer, &Stride, &Offset );
    GetDx11DeviceContext()->IASetPrimitiveTopology( PrimitiveTopology );

    return true;
}
