#include "Dx11MeshRenderer.h"
#include "Dx11Mesh.h"
#include "../Core/Dx11Device.h"
#include "../Core/Dx11VertexBuffer.h"


//=====================================================================================================================
// @brief	
//=====================================================================================================================
void Dx11MeshRenderer::OnRender() const
{
    WorldBufferPtr->Update( WorldMatrix( XMMatrixTranspose( MeshPtr->GetTransform().GetWorldMatrix() ) ) );
    
    GetDx11DeviceContext()->Draw( MeshPtr->GetPrimitive().GetVertexBuffer()->GetCount(), 0 );
}
