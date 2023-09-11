#include "Dx11VertexBuffer.h"
#include "Dx11ResourceFactory.h"
#include "../Asset/CrMesh.h"

//=====================================================================================================================
// @brief	Create
//=====================================================================================================================
void Dx11VertexBuffer::CreateBuffer( D3D11_USAGE Usage, D3D11_CPU_ACCESS_FLAG CpuAccess )
{
    Offset = 0; 

    BufferDesc.Usage = Usage;
    BufferDesc.ByteWidth = Descriptor->GetSize();
    BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    BufferDesc.CPUAccessFlags = CpuAccess;

    Create( nullptr );

    D3D11_MAPPED_SUBRESOURCE ms;
    GetDx11DeviceContext()->Map( GetBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &ms );
    {
        memcpy( ms.pData, Descriptor->GetVerticePtr(), BufferDesc.ByteWidth );
    }
    GetDx11DeviceContext()->Unmap( GetBuffer(), 0 );

    PrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

//=====================================================================================================================
// @brief	Create from crasset
//=====================================================================================================================
bool Dx11VertexBuffer::CreateFrom( const CrAsset* AssetPtr )
{
    if ( !AssetPtr ) return false;

    const auto* mesh = ( const CrMesh* )( AssetPtr );
    const auto* primitive = mesh->GetPrimitve();

    SAFE_DELETE( Descriptor );

    Descriptor = IDxVertexBufferDescriptor::Create( mesh->GetVertexStructureType() );
    Descriptor->ReadVertice( *primitive );

    CreateBuffer( primitive->GetDx11Usage(), primitive->GetDx11CpuAccessFlag() );

    return true;
}

//=====================================================================================================================
// @brief	Set render state
//=====================================================================================================================
bool Dx11VertexBuffer::SetRenderState( int InRegisterIndex ) const
{
    if ( Descriptor->GetCount() == 0 ) return false;

    unsigned int stride = Descriptor->GetStride();
    GetDx11DeviceContext()->IASetVertexBuffers( InRegisterIndex, 1, GetBufferAdressOf(), &stride, &Offset );
    GetDx11DeviceContext()->IASetPrimitiveTopology( PrimitiveTopology );

    return true;
}