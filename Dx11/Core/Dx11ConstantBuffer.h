#pragma once

#include "Dx11Buffer.h"
#include "Dx11Device.h"


class Dx11ConstantBufferStructure;


template < typename T >
class Dx11ConstantBuffer : public Dx11Buffer
{
public:
    // Construct
    Dx11ConstantBuffer() = default;
    Dx11ConstantBuffer( const Dx11ConstantBuffer& Other ) = default;
    Dx11ConstantBuffer( Dx11ConstantBuffer&& Other ) noexcept = default;

    // Destruct
    virtual ~Dx11ConstantBuffer() override = default;

    // Operators
    Dx11ConstantBuffer& operator=( const Dx11ConstantBuffer& Other ) = default;
    Dx11ConstantBuffer& operator=( Dx11ConstantBuffer&& Other ) noexcept = default;

    // Create buffer
    void CreateBuffer( D3D11_USAGE Usage, D3D11_CPU_ACCESS_FLAG CpuAccess );

    // Set vs
    void SetVS( int Idx ) const;

    // Set ps
    void SetPS( int Idx ) const;

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
void Dx11ConstantBuffer<T>::SetVS( int Idx ) const
{
    GetDx11DeviceContext()->VSSetConstantBuffers( Idx, 1, GetBufferAdressOf() );
}

//=====================================================================================================================
// @brief	Set ps
//=====================================================================================================================
template < typename T >
void Dx11ConstantBuffer<T>::SetPS( int Idx ) const
{
    GetDx11DeviceContext()->PSSetConstantBuffers( Idx, 1, GetBufferAdressOf() );
}

//=====================================================================================================================
// @brief	Update
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


