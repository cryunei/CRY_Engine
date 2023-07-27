#include "Dx11VertexBuffer.h"
#include "../DxMacros.h"
#include "../Core/Dx11Device.h"

//=====================================================================================================================
// @brief	Construct
//=====================================================================================================================
Dx11VertexBuffer::Dx11VertexBuffer()
: VertexBuffer      ( nullptr )
, VertexCount       ( 0 )
, Stride            ( 0 )
, Offset            ( 0 )
, PrimitiveTopology ( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST )

{
    ZeroMemory( &VertexBufferDesc, sizeof( D3D11_BUFFER_DESC ) );
}

//=====================================================================================================================
// @brief	Create
//=====================================================================================================================
void Dx11VertexBuffer::CreateBuffer( const std::vector<Vertex>& Vertices, D3D11_USAGE Usage, D3D11_CPU_ACCESS_FLAG CpuAccess )
{
    if ( Vertices.empty() ) return;

    VertexCount = (unsigned int)( Vertices.size() );
    Stride = sizeof( Vertex ); 
    unsigned int bufferSize = Stride * VertexCount;

    VertexBufferDesc.Usage = Usage;
    VertexBufferDesc.ByteWidth = bufferSize;
    VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    VertexBufferDesc.CPUAccessFlags = CpuAccess;

    GetDx11Device()->CreateBuffer( &VertexBufferDesc, nullptr, &VertexBuffer );

    D3D11_MAPPED_SUBRESOURCE ms;
    GetDx11DeviceContext()->Map( VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms );
    {
        memcpy( ms.pData, &Vertices[ 0 ], bufferSize );
    }
    GetDx11DeviceContext()->Unmap( VertexBuffer, 0 );
}

//=====================================================================================================================
// @brief	Release
//=====================================================================================================================
void Dx11VertexBuffer::Release()
{
    SAFE_RELEASE( VertexBuffer );

    VertexCount = 0;
}

//=====================================================================================================================
// @brief	Render
//=====================================================================================================================
bool Dx11VertexBuffer::Render() const
{
    if ( VertexCount == 0 ) return false;

    GetDx11DeviceContext()->IASetVertexBuffers( 0, 1, &VertexBuffer, &Stride, &Offset );
    GetDx11DeviceContext()->IASetPrimitiveTopology( PrimitiveTopology );

    return true;
}
