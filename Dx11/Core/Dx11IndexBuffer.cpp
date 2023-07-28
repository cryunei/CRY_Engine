﻿#include "Dx11IndexBuffer.h"
#include "Dx11ResourceFactory.h"
#include "../DxMacros.h"
#include "../Core/Dx11Device.h"


//=====================================================================================================================
// @brief	Construct
//=====================================================================================================================
Dx11IndexBuffer::Dx11IndexBuffer()
: Buffer( nullptr )
, Count( 0 )
{
    ZeroMemory( &BufferDesc, sizeof( D3D11_BUFFER_DESC ) );
    ZeroMemory( &BufferSD, sizeof( D3D11_SUBRESOURCE_DATA ) );
}

//=====================================================================================================================
// @brief	Create
//=====================================================================================================================
void Dx11IndexBuffer::CreateBuffer( const std::vector< unsigned int >& Indices, D3D11_USAGE Usage, D3D11_CPU_ACCESS_FLAG CpuAccess )
{
    if ( Indices.empty() ) return;

    Count = (unsigned int)( Indices.size() );
    unsigned int bufferSize = sizeof( int ) * Count;

    BufferDesc.Usage = Usage;
    BufferDesc.ByteWidth = bufferSize;
    BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    BufferDesc.CPUAccessFlags = CpuAccess;
    BufferDesc.MiscFlags = 0;
    BufferDesc.StructureByteStride = 0;

    BufferSD.pSysMem = &Indices[ 0 ];
    BufferSD.SysMemPitch = 0;
    BufferSD.SysMemSlicePitch = 0;

    Dx11ResourceFactory::CreateBuffer( &Buffer, &BufferDesc, &BufferSD );
}

//=====================================================================================================================
// @brief	Release
//=====================================================================================================================
void Dx11IndexBuffer::Release()
{
    SAFE_RELEASE( Buffer );
}

//=====================================================================================================================
// @brief	Render
//=====================================================================================================================
bool Dx11IndexBuffer::Render() const
{
    if ( Count == 0 ) return false;

    GetDx11DeviceContext()->IASetIndexBuffer( Buffer, DXGI_FORMAT_R32_UINT, 0 );

    return true;
}