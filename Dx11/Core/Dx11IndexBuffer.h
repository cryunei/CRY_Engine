#pragma once

#include "Dx11Buffer.h"
#include "../DxTypes.h"


//=====================================================================================================================
// @brief	Dx11IndexBuffer
//=====================================================================================================================
class Dx11IndexBuffer : public Dx11Buffer
{
    CLASS_DEFAULT_BODY( Dx11IndexBuffer )

private:
    D3D11_SUBRESOURCE_DATA BufferSD;
    unsigned int           Count;

public:
    // Construct
    Dx11IndexBuffer();
    
    // Create buffer
    void CreateBuffer( const std::vector< unsigned int >& Indices, D3D11_USAGE Usage, D3D11_CPU_ACCESS_FLAG CpuAccess );

    // Set to render state
    virtual bool SetRenderState( int InRegisterIndex ) const override;

    // Getters
    unsigned int GetCount() const { return Count; }
};
