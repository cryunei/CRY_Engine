#include "Dx11ConstantBuffer.h"
#include "../Render/Dx11ConstantBufferStructure.h"


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

