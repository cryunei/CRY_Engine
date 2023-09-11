#include "Dx11MeshRenderElement.h"
#include "Dx11ConstantBufferStructure.h"
#include "Dx11Mesh.h"
#include "../Core/Dx11ConstantBuffer.h"
#include "../Core/Dx11Device.h"
#include "../Core/Dx11IndexBuffer.h"
#include "../Core/Dx11VertexBuffer.h"


//=====================================================================================================================
// @brief	
//=====================================================================================================================
void Dx11MeshRenderElement::OnRender() const
{
    WorldBufferPtr->Update< WorldMatrix >( WorldMatrix( XMMatrixTranspose( MeshPtr->GetTransform().GetWorldMatrix() ) ) );
    
    const Dx11Primitive* primitive = &MeshPtr->GetPrimitive();
    if ( primitive->GetIndexBuffer() && primitive->GetIndexBuffer()->GetCount() > 0 )
    {
        GetDx11DeviceContext()->DrawIndexed( primitive->GetIndexBuffer()->GetCount(), 0, 0 );        
    }
    else
    {
        GetDx11DeviceContext()->Draw( MeshPtr->GetPrimitive().GetVertexBuffer()->GetCount(), 0 );
    }
}
