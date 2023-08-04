#include "Dx11LevelLoader.h"
#include "../Asset/CrMesh.h"
#include "../Asset/CrVertexBuffer.h"
#include "../Core/Dx11ResourceManager.h"
#include "../Level/CrLevel.h"
#include "../Render/Dx11Mesh.h"
#include "../Render/Dx11Renderer.h"


//=====================================================================================================================
// @brief	Load
//=====================================================================================================================
void Dx11LevelLoader::Load( CrLevel& InLevel )
{
    int i = 0;
    for ( const CrMesh* crMesh : InLevel.GetMeshes() )
    {
        Dx11VertexBuffer* vb = GetDx11ResourceManager()->CreateVertexBuffer( crMesh->GetVertexBuffer() );
        Dx11IndexBuffer*  ib = GetDx11ResourceManager()->CreateIndexBuffer ( crMesh->GetIndexBuffer () );
        Dx11VertexShader* vs = GetDx11ResourceManager()->CreateVertexShader( crMesh->GetVertexShader() );
        Dx11PixelShader*  ps = GetDx11ResourceManager()->CreatePixelShader ( crMesh->GetPixelShader () );
        Dx11Texture2D*    tx = GetDx11ResourceManager()->CreateTexture2D   ( crMesh->GetTexture2D   () );

        Dx11Mesh* dxMesh =new Dx11Mesh();
        dxMesh->InitializePrimitive( vb, ib );
        dxMesh->InitializeMaterial( vs, ps, tx );

        Meshes.push_back( dxMesh );

        dxMesh->GetTransform().SetLocationX( -5.f + 10.f * i );
        ++i;
    }
}

//=====================================================================================================================
// @brief	Add render meshes
//=====================================================================================================================
void Dx11LevelLoader::AddRenderMeshes( Dx11Renderer& InRenderer ) const
{
    for ( Dx11Mesh* dxMesh : Meshes )
    {
        InRenderer.AddMeshRenderElement( dxMesh );
    }
    InRenderer.SortRenderQueue();
}
