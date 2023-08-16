#include "Dx11ResourceRenderer.h"
#include "../Core/Dx11Resource.h"

//=====================================================================================================================
// @brief	On render
//=====================================================================================================================
void Dx11ResourceRenderer::OnRender() const
{
    ResourcePtr->SetRenderState( RegisterIndex );
}
