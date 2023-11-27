#include "Dx11ConstantBuffer.h"


//=====================================================================================================================
// @brief	CreateBuffer
//=====================================================================================================================
void Dx11ConstantBuffer::CreateBuffer( size_t Size, D3D11_USAGE Usage, D3D11_CPU_ACCESS_FLAG CpuAccess )
{
    BufferDesc.Usage = Usage;
    BufferDesc.ByteWidth = Size;
    BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    BufferDesc.CPUAccessFlags = CpuAccess;
    Create( nullptr );
}

//=====================================================================================================================
// @brief	Set register
//=====================================================================================================================
void Dx11ConstantBuffer::SetRegister( ERenderPipeLineStage Stage, int Idx )
{
    BindStage = Stage;

    switch ( BindStage )
    {
    case ERenderPipeLineStage::VertexShader: GetDx11DeviceContext()->VSSetConstantBuffers( Idx, 1, GetBufferAdressOf() ); break;
    case ERenderPipeLineStage::PixelShader:  GetDx11DeviceContext()->PSSetConstantBuffers( Idx, 1, GetBufferAdressOf() ); break;
    }
}

