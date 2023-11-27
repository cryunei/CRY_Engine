#include "Dx11ReflectorRenderElement.h"
#include "Dx11ReflectionRenderer.h"
#include "../Dx11.h"


//=====================================================================================================================
// @brief	On render
//=====================================================================================================================
void Dx11ReflectorRenderElement::OnRender() const
{
    G_Dx11ReflectionRenderer.SetReflectionBuffer( ReflectorName );

    Dx11MeshRenderElement::OnRender();
}
