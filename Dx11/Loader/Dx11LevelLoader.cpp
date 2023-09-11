#include "Dx11LevelLoader.h"
#include "../Dx11.h"
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
#include "..\Render\Dx11VertexBufferDescriptor.h"

//=====================================================================================================================
// @brief	Load
//=====================================================================================================================
void Dx11LevelLoader::Load( CrLevel& InLevel )
{
    int i = 0;
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

        Meshes.push_back( dxMesh );

        dxMesh->GetTransform().SetLocationX( -8.f + 8.f * ( ( i ) % 3 ) );
        dxMesh->GetTransform().SetLocationY( -4.f + 8.f * ( ( i ) / 3 ) );
        ++i;
    }
    TestMesh = new Dx11Mesh();
    *TestMesh = *Meshes[ 0 ];
    TestMesh->GetTransform().SetLocation( 0.f, 0.f, 0.f );

    CrMesh* crMeshTestRT = InLevel.GetTestRT();
    TestRT = new Dx11Mesh();
    Dx11VertexBuffer* vb = GetDx11ObjectManager()->GetFrom< Dx11VertexBuffer >( EDx11ResourceType::VertexBuffer, crMeshTestRT );
    Dx11IndexBuffer*  ib = GetDx11ObjectManager()->GetFrom< Dx11IndexBuffer  >( EDx11ResourceType::IndexBuffer , crMeshTestRT->GetPrimitve() );
    Dx11VertexShader* vs = GetDx11ObjectManager()->GetFrom< Dx11VertexShader >( EDx11ResourceType::VertexShader, crMeshTestRT->GetVertexShader() );
    Dx11PixelShader*  ps = GetDx11ObjectManager()->GetFrom< Dx11PixelShader  >( EDx11ResourceType::PixelShader , crMeshTestRT->GetPixelShader() );

    TestRT->InitializePrimitive( vb, ib );
    TestRT->InitializeMaterial( vs, ps );

    std::vector< Dx11ResourceRenderer* > dxRRs;
    dxRRs.push_back( GetDx11ObjectManager()->CreateResourceRenderer_Texture2D( G_Dx11Renderer.GetRenderTarget( "TestRT" )->GetTexture2D(), 0 ) );

    TestRT->InitializeTexture2Ds( dxRRs );

    TestRT->GetTransform().SetLocationX( -8.f + 8.f * ( Meshes.size() % 3 ) );
    TestRT->GetTransform().SetLocationY( -4.f + 8.f * ( Meshes.size() / 3 ) );
    TestRT->GetTransform().SetScale( 4.f, 4.f, 1.f );
}

//=====================================================================================================================
// @brief	Add render meshes
//=====================================================================================================================
void Dx11LevelLoader::AddRenderMeshes( Dx11Renderer& InRenderer ) const
{
    auto itr = Meshes.begin();

    for ( ; itr != Meshes.end(); ++itr )
    {
        InRenderer.AddMeshRenderElement( *itr );
    }

    InRenderer.AddMeshRenderElement( TestMesh, "TestRT" );
    
    InRenderer.AddMeshRenderElement( TestRT );
    InRenderer.SortRenderQueue();
}
