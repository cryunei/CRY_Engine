#include "Dx11Primitive.h"
#include "../Core/Dx11Device.h"
#include "../Core/Dx11VertexBuffer.h"
#include "../Core/Dx11IndexBuffer.h"


//=====================================================================================================================
// @brief	Construct
//=====================================================================================================================
Dx11Primitive::Dx11Primitive()
: VertexBuffer ( nullptr )
, IndexBuffer  ( nullptr )
{
}

//=====================================================================================================================
// @brief	Initialize
//=====================================================================================================================
void Dx11Primitive::Initialize( Dx11VertexBuffer* InVertexBuffer, Dx11IndexBuffer* InIndexBuffer )
{
    VertexBuffer = InVertexBuffer;
    IndexBuffer  = InIndexBuffer;
}

//=====================================================================================================================
// @brief	Incrase render count
//=====================================================================================================================
void Dx11Primitive::IncreaseRenderCount() const
{
    if ( VertexBuffer ) VertexBuffer->IncreaseRenderCount();
    if ( IndexBuffer  ) IndexBuffer ->IncreaseRenderCount();
}

//=====================================================================================================================
// @brief	Decrease render count
//=====================================================================================================================
void Dx11Primitive::DecreaseRenderCount() const
{
    if ( VertexBuffer ) VertexBuffer->DecreaseRenderCount();
    if ( IndexBuffer  ) IndexBuffer ->DecreaseRenderCount();
}
