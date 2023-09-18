#include "Dx11LevelLoader.h"
#include "../Asset/CrMesh.h"
#include "../Asset/CrVertexShader.h"
#include "../Asset/CrPixelShader.h"
#include "../Asset/CrPrimitive.h"
#include "../Core/Dx11VertexShader.h"
#include "../Core/Dx11ObjectManager.h"
#include "../Core/Dx11PixelShader.h"
#include "../Level/CrLevel.h"
#include "../Render/Dx11Mesh.h"
#include "../Render/Dx11Renderer.h"


//=====================================================================================================================
// @brief	Load
//=====================================================================================================================
void Dx11LevelLoader::Load( CrLevel& InLevel )
{
    for ( const CrMesh* crMesh : InLevel.GetMeshes() )
    {
        Dx11IndexBuffer*  ib = GetDx11ObjectManager()->GetFrom< Dx11IndexBuffer  >( EDx11ResourceType::IndexBuffer , crMesh->GetPrimitve()     );
        Dx11VertexShader* vs = GetDx11ObjectManager()->GetFrom< Dx11VertexShader >( EDx11ResourceType::VertexShader, crMesh->GetVertexShader() );
        Dx11PixelShader*  ps = GetDx11ObjectManager()->GetFrom< Dx11PixelShader  >( EDx11ResourceType::PixelShader , crMesh->GetPixelShader()  );
        Dx11VertexBuffer* vb = GetDx11ObjectManager()->GetFrom< Dx11VertexBuffer >( EDx11ResourceType::VertexBuffer, crMesh );

        Dx11Mesh* dxMesh =new Dx11Mesh();
        dxMesh->InitializePrimitive( vb, ib );
        dxMesh->InitializeMaterial( vs, ps );

        std::vector< Dx11ResourceRenderer* > dxRRs;
        for ( int t = 0; t < crMesh->GetCount_Texture2D(); ++t )
        {
            Dx11ResourceRenderer* dxRR = GetDx11ObjectManager()->CreateResourceRenderer_Texture2D( crMesh->GetTexture2D( t ), t );
            if ( !dxRR ) break;

            dxRRs.push_back( dxRR );
        }
        dxMesh->InitializeTexture2Ds( dxRRs );
        dxMesh->SetRenderTarget( crMesh->GetRenderTarget() );
        dxMesh->SetOpacity( crMesh->GetOpacity() );

        Meshes.push_back( dxMesh );

        dxMesh->SetTransform( crMesh->GetTransform() );
    }
}

//=====================================================================================================================
// @brief	Add render meshes
//=====================================================================================================================
void Dx11LevelLoader::AddRenderMeshes( Dx11Renderer& InRenderer ) const
{
    auto itr = Meshes.begin();

    for ( ; itr != Meshes.end(); ++itr )
    {
        InRenderer.AddMeshRenderElement( *itr, (*itr)->GetRenderTarget() );
    }

    InRenderer.SortRenderQueue();
}
