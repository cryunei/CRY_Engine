#include "Dx11IndexBuffer.h"
#include "../DxMacros.h"
#include "../Core/Dx11Device.h"


//=====================================================================================================================
// @brief	Construct
//=====================================================================================================================
Dx11IndexBuffer::Dx11IndexBuffer()
: IndexBuffer( nullptr )
, IndexCount( 0 )
{
    ZeroMemory( &IndexBufferDesc, sizeof( D3D11_BUFFER_DESC ) );
    ZeroMemory( &IndexBufferSD, sizeof( D3D11_SUBRESOURCE_DATA ) );
}

//=====================================================================================================================
// @brief	Create
//=====================================================================================================================
void Dx11IndexBuffer::CreateBuffer( const std::vector<unsigned>& Indices, D3D11_USAGE Usage, D3D11_CPU_ACCESS_FLAG CpuAccess )
{
    if ( Indices.empty() ) return;

    IndexCount = (unsigned int)( Indices.size() );
    unsigned int bufferSize = sizeof( int ) * IndexCount;

    IndexBufferDesc.Usage = Usage;
    IndexBufferDesc.ByteWidth = bufferSize;
    IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    IndexBufferDesc.CPUAccessFlags = CpuAccess;
    IndexBufferDesc.MiscFlags = 0;
    IndexBufferDesc.StructureByteStride = 0;

    IndexBufferSD.pSysMem = &Indices[ 0 ];
    IndexBufferSD.SysMemPitch = 0;
    IndexBufferSD.SysMemSlicePitch = 0;

    GetDx11Device()->CreateBuffer( &IndexBufferDesc, &IndexBufferSD, &IndexBuffer );
}

//=====================================================================================================================
// @brief	Release
//=====================================================================================================================
void Dx11IndexBuffer::Release()
{
    SAFE_RELEASE( IndexBuffer );
}

//=====================================================================================================================
// @brief	Render
//=====================================================================================================================
bool Dx11IndexBuffer::Render() const
{
    if ( IndexCount == 0 ) return false;

    GetDx11DeviceContext()->IASetIndexBuffer( IndexBuffer, DXGI_FORMAT_R32_UINT, 0 );

    return true;
}
