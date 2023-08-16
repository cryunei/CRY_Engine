#pragma once


#include "Dx11Buffer.h"
#include "Dx11CoreTypes.h"
#include "Dx11Device.h"


class Dx11ConstantBufferStructure;


template < typename T >
class Dx11ConstantBuffer : public Dx11Buffer
{
    CLASS_DEFAULT_BODY( Dx11ConstantBuffer )

private:
    ERenderPipeLineStage BindStage;

public:
    // Construct
    Dx11ConstantBuffer() = default;

    // Destruct
    virtual ~Dx11ConstantBuffer() override = default;

    // Create buffer
    void CreateBuffer( D3D11_USAGE Usage, D3D11_CPU_ACCESS_FLAG CpuAccess );

    // Set register
    void SetRegister( ERenderPipeLineStage Stage, int Idx );

    // Update
    void Update( const T& Data ) const;
};


//=====================================================================================================================
// @brief	Create buffer
//=====================================================================================================================
template < typename T >
void Dx11ConstantBuffer<T>::CreateBuffer( D3D11_USAGE Usage, D3D11_CPU_ACCESS_FLAG CpuAccess )
{
    BufferDesc.Usage = Usage;
    BufferDesc.ByteWidth = sizeof( T );
    BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    BufferDesc.CPUAccessFlags = CpuAccess;

    Create( nullptr );
}

//=====================================================================================================================
// @brief	Set vs
//=====================================================================================================================
template < typename T >
void Dx11ConstantBuffer<T>::SetRegister( ERenderPipeLineStage Stage, int Idx )
{
    BindStage = Stage;

    switch ( BindStage )
    {
    case ERenderPipeLineStage::VertexShader: GetDx11DeviceContext()->VSSetConstantBuffers( Idx, 1, GetBufferAdressOf() ); break;
    case ERenderPipeLineStage::PixelShader:  GetDx11DeviceContext()->PSSetConstantBuffers( Idx, 1, GetBufferAdressOf() ); break;
    }
}

//=====================================================================================================================
// @brief	Update
//=====================================================================================================================
template < typename T >
void Dx11ConstantBuffer<T>::Update( const T& Data ) const
{
    D3D11_MAPPED_SUBRESOURCE mappedResource;

    GetDx11DeviceContext()->Map( GetBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource );
    {
        T* pData = static_cast< T* >( mappedResource.pData );
        *pData = Data;
    }
    GetDx11DeviceContext()->Unmap( GetBuffer(), 0 );
}
