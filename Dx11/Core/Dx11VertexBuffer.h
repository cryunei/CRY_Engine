#pragma once


#include "Dx11Buffer.h"
#include "../Core/Dx11Device.h"
#include "..\Render\Dx11VertexBufferDescriptor.h"


class IDxVertexBufferDescriptor;
class CrMesh;


//=====================================================================================================================
// @brief	Dx11VertexBuffer
//=====================================================================================================================
class Dx11VertexBuffer : public Dx11Buffer
{
    CLASS_DEFAULT_BODY( Dx11VertexBuffer )

private:
    IDxVertexBufferDescriptor* Descriptor; // Vertex buffer descriptor
    unsigned int Offset; // draw start offset

    D3D11_PRIMITIVE_TOPOLOGY PrimitiveTopology; // draw primitive topology type

public:
    // Construct
    Dx11VertexBuffer() = default;

    // Create buffer
    void CreateBuffer( D3D11_USAGE Usage, D3D11_CPU_ACCESS_FLAG CpuAccess );

    // Create from crasset
    bool CreateFrom( const CrAsset* AssetPtr );

    // Set render state
    virtual bool SetRenderState( int InRegisterIndex ) const override;

    // Getters
    unsigned int GetCount() const { return Descriptor->GetCount(); }
};