//=================================================================================================
// @file	Dx11VertexBuffer.cpp
//
// @date	2023-4-24
//=================================================================================================


#include "Dx11Primitive.h"
#include "../Core/Dx11Device.h"
#include "../Core/Dx11VertexBuffer.h"
#include "../Core/Dx11IndexBuffer.h"
#include "../Core/Dx11ResourceManager.h"
#include "../Core/Dx11VertexShader.h"

//=================================================================================================
// @brief	 Construct
//=================================================================================================
Dx11Primitive::Dx11Primitive()
: VertexShader ( nullptr )
, VertexBuffer ( nullptr )
, IndexBuffer  ( nullptr )
{
}

//=================================================================================================
// @brief	Initialize
//=================================================================================================
void Dx11Primitive::Initialize( Dx11VertexBuffer* InVertexBuffer, Dx11IndexBuffer* InIndexBuffer, Dx11VertexShader* InVertexShader )
{
    VertexBuffer = InVertexBuffer;
    IndexBuffer  = InIndexBuffer;
    VertexShader = InVertexShader;
}

//=================================================================================================
// @brief	Render
//=================================================================================================
void Dx11Primitive::Render() const
{
    if ( !VertexShader || !VertexShader->Render() ) return;
    if ( !VertexBuffer || !VertexBuffer->Render() ) return;

    if ( IndexBuffer && IndexBuffer->Render() )
    {
        GetDx11DeviceContext()->DrawIndexed( IndexBuffer->GetCount(), 0, 0 );                
    }
    else
    {
        GetDx11DeviceContext()->Draw( VertexBuffer->GetCount(), 0 );        
    }
}