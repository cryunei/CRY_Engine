#include "Dx11MeshRenderElement.h"
#include "Dx11ConstantBufferStructure.h"
#include "Dx11GlobalConstantBuffers.h"
#include "Dx11Mesh.h"
#include "../Core/Dx11Device.h"
#include "../Core/Dx11ConstantBuffer.h"
#include "../Core/Dx11IndexBuffer.h"
#include "../Core/Dx11VertexBuffer.h"


//=====================================================================================================================
// @brief	
//=====================================================================================================================
void Dx11MeshRenderElement::OnRender() const
{
    GetDx11GCB()->GetBuffer( EGlobalConstantBufferType::World )->Update< WorldMatrix >( WorldMatrix( XMMatrixTranspose( Transform->GetWorldMatrix() ) ) );
    GetDx11GCB()->GetBuffer( EGlobalConstantBufferType::RenderProperty )->Update< RenderProperty >( RenderProperty( Opacity ) );
    
    if ( IndexBuffer && IndexBuffer->GetCount() > 0 )
    {
        GetDx11DeviceContext()->DrawIndexed( IndexBuffer->GetCount(), 0, 0 );        
    }
    else
    {
        GetDx11DeviceContext()->Draw( VertexBuffer->GetCount(), 0 );
    }
}
