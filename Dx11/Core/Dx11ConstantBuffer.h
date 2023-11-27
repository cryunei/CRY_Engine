#pragma once


#include "Dx11Buffer.h"
#include "Dx11CoreTypes.h"
#include "Dx11Device.h"


class IDxConstantBufferDescriptor;


//=====================================================================================================================
// @brief	Dx11ConstantBuffer
//=====================================================================================================================
class Dx11ConstantBuffer : public Dx11Buffer
{
    CLASS_DEFAULT_BODY( Dx11ConstantBuffer )

private:
    ERenderPipeLineStage BindStage;  // Binded rendering pipeline stage

public:
    // Construct
    Dx11ConstantBuffer() = default;

    // Destruct
    virtual ~Dx11ConstantBuffer() override = default;

    // Create buffer
    void CreateBuffer( size_t Size, D3D11_USAGE Usage, D3D11_CPU_ACCESS_FLAG CpuAccess );

    // Set register
    void SetRegister( ERenderPipeLineStage Stage, int Idx );

    // Update
    template< typename T >
    void Update( const T& Data ) const;
};


//=====================================================================================================================
// @brief	Update
//=====================================================================================================================
template < typename T >
void Dx11ConstantBuffer::Update( const T& Data ) const
{
    unsigned int size = sizeof( T );

    D3D11_MAPPED_SUBRESOURCE mappedResource;    
    GetDx11DeviceContext()->Map( GetBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource );
    {
        memcpy_s( mappedResource.pData, size, &Data, size );
    }
    GetDx11DeviceContext()->Unmap( GetBuffer(), 0 );
}
