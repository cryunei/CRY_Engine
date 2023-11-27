#pragma once


#include "Dx11Mesh.h"
#include "Dx11MeshRenderElement.h"
#include <vector>


class IDxRenderElement;
class Dx11Mesh;


using RenderElementList = std::vector< const IDxRenderElement* >;
using MeshRenderElementList = std::vector< Dx11MeshRenderElement* >;