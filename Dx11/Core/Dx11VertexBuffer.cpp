#include "Dx11VertexBuffer.h"
#include "Dx11ResourceFactory.h"


//=====================================================================================================================
// @brief	Set render state
//=====================================================================================================================
bool Dx11VertexBuffer::SetRenderState( int InRegisterIndex ) const
{
    if ( Count == 0 ) return false;

    GetDx11DeviceContext()->IASetVertexBuffers( InRegisterIndex, 1, GetBufferAdressOf(), &Stride, &Offset );
    GetDx11DeviceContext()->IASetPrimitiveTopology( PrimitiveTopology );

    return true;
}