#pragma once

#include "Dx11Device.h"
#include "Dx11Resource.h"
#include "Dx11ResourceFactory.h"
#include "../DxMacros.h"
#include "../Asset/CrIndexBuffer.h"


class Dx11ConstantBufferStructure;


template < typename T >
class Dx11ConstantBuffer : public Dx11Resource
{
private:
    ID3D11Buffer* Buffer;

public:
    // Construct
    Dx11ConstantBuffer();
    Dx11ConstantBuffer( const Dx11ConstantBuffer& Other ) = default;
    Dx11ConstantBuffer( Dx11ConstantBuffer&& Other ) noexcept = default;

    // Destruct
    virtual ~Dx11ConstantBuffer() = default;

    // Operators
    Dx11ConstantBuffer& operator=( const Dx11ConstantBuffer& Other ) = default;
    Dx11ConstantBuffer& operator=( Dx11ConstantBuffer&& Other ) noexcept = default;

    // Create buffer
    void CreateBuffer( D3D11_USAGE Usage, D3D11_CPU_ACCESS_FLAG CpuAccess );

    // Release
    virtual void Release() override;

    // Set vs
    void SetVS( int Idx ) const;

    // Set ps
    void SetPS( int Idx ) const;

    // Update
    void Update( const T& Data ) const;
};


//=====================================================================================================================
// @brief	Construct
//=====================================================================================================================
template < typename T >
Dx11ConstantBuffer<T>::Dx11ConstantBuffer()
: Buffer( nullptr )
{
}

//=====================================================================================================================
// @brief	Create buffer
//=====================================================================================================================
template < typename T >
void Dx11ConstantBuffer<T>::CreateBuffer( D3D11_USAGE Usage, D3D11_CPU_ACCESS_FLAG CpuAccess )
{
    D3D11_BUFFER_DESC bd;
    bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.ByteWidth = sizeof( T );
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    bd.MiscFlags = 0;
    bd.StructureByteStride = 0;

    Dx11ResourceFactory::CreateBuffer( &Buffer, &bd, nullptr );
}

//=====================================================================================================================
// @brief	Release
//=====================================================================================================================
template < typename T >
void Dx11ConstantBuffer<T>::Release()
{
    SAFE_RELEASE( Buffer );
}

//=====================================================================================================================
// @brief	Set vs
//=====================================================================================================================
template < typename T >
void Dx11ConstantBuffer<T>::SetVS( int Idx ) const
{
    GetDx11DeviceContext()->VSSetConstantBuffers( Idx, 1, &Buffer );
}

//=====================================================================================================================
// @brief	Set ps
//=====================================================================================================================
template < typename T >
void Dx11ConstantBuffer<T>::SetPS( int Idx ) const
{
    GetDx11DeviceContext()->PSSetConstantBuffers( Idx, 1, &Buffer );
}

//=====================================================================================================================
// @brief	Update
//=====================================================================================================================
template < typename T >
void Dx11ConstantBuffer<T>::Update( const T& Data ) const
{
    D3D11_MAPPED_SUBRESOURCE mappedResource;

    GetDx11DeviceContext()->Map( Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource );
    {
        T* pData = static_cast< T* >( mappedResource.pData );
        *pData = Data;
    }
    GetDx11DeviceContext()->Unmap( Buffer, 0 );
}


