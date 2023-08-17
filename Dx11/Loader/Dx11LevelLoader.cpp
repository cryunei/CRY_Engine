#include "Dx11LevelLoader.h"
#include "../Asset/CrMesh.h"
#include "../Core/Dx11Texture2D.h"
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

        Dx11Mesh* dxMesh =new Dx11Mesh();
        dxMesh->InitializePrimitive( vb, ib );
        dxMesh->InitializeMaterial( vs, ps );

        std::vector< Dx11ResourceRenderer* > dxRRs;
        for ( int t = 0; t < crMesh->GetCount_Texture2D(); ++t )
        {
            Dx11ResourceRenderer* dxRR = GetDx11ResourceManager()->CreateResourceRenderer_Texture2D( crMesh->GetTexture2D( t ), t );
            if ( !dxRR ) break;

            dxRRs.push_back( dxRR );
        }
        dxMesh->InitializeTexture2Ds( dxRRs );

        Meshes.push_back( dxMesh );

        dxMesh->GetTransform().SetLocationX( -8.f + 8.f * ( ( i ) % 3 ) );
        dxMesh->GetTransform().SetLocationY( -4.f + 8.f * ( ( i ) / 3 ) );
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
