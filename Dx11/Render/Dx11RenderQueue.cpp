#include "Dx11RenderQueue.h"
#include "Dx11Mesh.h"
#include "../Core/Dx11VertexBuffer.h"
#include "../Core/Dx11IndexBuffer.h"
#include "../Core/Dx11VertexShader.h"
#include "../Core/Dx11PixelShader.h"
#include "../Core/Dx11Texture2D.h"
#include <algorithm>
#include <iostream>

//=====================================================================================================================
// @brief	Construct
//=====================================================================================================================
Dx11RenderQueue::Dx11RenderQueue()
{
    // Dx11VertexShader* vs71 = new Dx11VertexShader();
    // Dx11VertexShader* vs21 = new Dx11VertexShader();
    // Dx11VertexShader* vs22 = new Dx11VertexShader();
    // Dx11VertexShader* vs23 = new Dx11VertexShader();
    // vs71->SetRenderCount( 7 );
    // vs21->SetRenderCount( 2 );
    // vs22->SetRenderCount( 2 );
    // vs23->SetRenderCount( 2 );
    //
    // Dx11PixelShader* ps41 = new Dx11PixelShader();
    // Dx11PixelShader* ps31 = new Dx11PixelShader();
    // Dx11PixelShader* ps32 = new Dx11PixelShader();
    // Dx11PixelShader* ps33 = new Dx11PixelShader();
    // ps41->SetRenderCount( 4 );    
    // ps31->SetRenderCount( 3 );
    // ps32->SetRenderCount( 3 );
    // ps33->SetRenderCount( 3 );
    //
    // Dx11VertexBuffer* vb61 = new Dx11VertexBuffer();
    // Dx11VertexBuffer* vb41 = new Dx11VertexBuffer();
    // Dx11VertexBuffer* vb31 = new Dx11VertexBuffer();
    // vb61->SetRenderCount( 6 );
    // vb41->SetRenderCount( 4 );
    // vb31->SetRenderCount( 3 );
    //
    // Dx11IndexBuffer* ib31 = new Dx11IndexBuffer();
    // Dx11IndexBuffer* ib32 = new Dx11IndexBuffer();
    // Dx11IndexBuffer* ib33 = new Dx11IndexBuffer();
    // Dx11IndexBuffer* ib34 = new Dx11IndexBuffer();
    // Dx11IndexBuffer* ib11 = new Dx11IndexBuffer();
    // ib31->SetRenderCount( 3 );
    // ib32->SetRenderCount( 3 );
    // ib33->SetRenderCount( 3 );
    // ib34->SetRenderCount( 3 );
    // ib11->SetRenderCount( 1 );
    //
    // Dx11Texture2D* tx21 = new Dx11Texture2D();
    // Dx11Texture2D* tx22 = new Dx11Texture2D();
    // Dx11Texture2D* tx23 = new Dx11Texture2D();
    // Dx11Texture2D* tx24 = new Dx11Texture2D();
    // Dx11Texture2D* tx25 = new Dx11Texture2D();
    // Dx11Texture2D* tx26 = new Dx11Texture2D();
    // Dx11Texture2D* tx11 = new Dx11Texture2D();
    // tx21->SetRenderCount( 2 );
    // tx22->SetRenderCount( 2 );
    // tx23->SetRenderCount( 2 );
    // tx24->SetRenderCount( 2 );
    // tx25->SetRenderCount( 2 );
    // tx26->SetRenderCount( 2 );
    // tx11->SetRenderCount( 1 );
    //
    // Dx11Mesh* mesh = new Dx11Mesh();
    // mesh->GetMaterial().Initialize( vs71, ps41, tx22 );
    // mesh->GetPrimitive().Initialize( vb61, ib31 );
    // Add( mesh );
    //
    // mesh = new Dx11Mesh();
    // mesh->GetMaterial().Initialize( vs71, ps41, tx22 );
    // mesh->GetPrimitive().Initialize( vb61, ib31 );
    // Add( mesh );
    //
    // mesh = new Dx11Mesh();
    // mesh->GetMaterial().Initialize( vs71, ps41, tx22 );
    // mesh->GetPrimitive().Initialize( vb61, ib31 );
    // Add( mesh );
    //
    // mesh = new Dx11Mesh();
    // mesh->GetMaterial().Initialize( vs71, ps41, tx22 );
    // mesh->GetPrimitive().Initialize( vb61, ib32 );
    // Add( mesh );
    //
    // mesh = new Dx11Mesh();
    // mesh->GetMaterial().Initialize( vs71, ps31, tx11 );
    // mesh->GetPrimitive().Initialize( vb61, ib32 );
    // Add( mesh );
    //
    // mesh = new Dx11Mesh();
    // mesh->GetMaterial().Initialize( vs71, ps31, tx11 );
    // mesh->GetPrimitive().Initialize( vb61, ib32 );
    // Add( mesh );
    //
    // mesh = new Dx11Mesh();
    // mesh->GetMaterial().Initialize( vs71, ps31, tx11 );
    // mesh->GetPrimitive().Initialize( vb41, ib33 );
    // Add( mesh );
    //
    // mesh = new Dx11Mesh();
    // mesh->GetMaterial().Initialize( vs21, ps32, tx11 );
    // mesh->GetPrimitive().Initialize( vb41, ib33 );
    // Add( mesh );
    //
    // mesh = new Dx11Mesh();
    // mesh->GetMaterial().Initialize( vs21, ps32, tx11 );
    // mesh->GetPrimitive().Initialize( vb41, ib33 );
    // Add( mesh );
    //
    // mesh = new Dx11Mesh();
    // mesh->GetMaterial().Initialize( vs22, ps32, tx11 );
    // mesh->GetPrimitive().Initialize( vb41, ib34 );
    // Add( mesh );
    //
    // mesh = new Dx11Mesh();
    // mesh->GetMaterial().Initialize( vs22, ps33, tx11 );
    // mesh->GetPrimitive().Initialize( vb31, ib34 );
    // Add( mesh );
    //
    // mesh = new Dx11Mesh();
    // mesh->GetMaterial().Initialize( vs23, ps33, tx11 );
    // mesh->GetPrimitive().Initialize( vb31, ib34 );
    // Add( mesh );
    //
    // mesh = new Dx11Mesh();
    // mesh->GetMaterial().Initialize( vs23, ps33, tx11 );
    // mesh->GetPrimitive().Initialize( vb31, ib11 );
    // Add( mesh );
    //
    // for ( const Dx11Mesh* mesh : Meshes )
    // {
    //     std::cout << "#vs : " << mesh->GetMaterial().GetVertexShader() << ", " << ( mesh->GetMaterial().GetVertexShader() ? mesh->GetMaterial().GetVertexShader()->GetRenderCount() : 0 )
    //       << " #ps : " << mesh->GetMaterial().GetPixelShader() << ", " << ( mesh->GetMaterial().GetPixelShader() ? mesh->GetMaterial().GetPixelShader()->GetRenderCount() : 0 )
    //       << " #vb : " << mesh->GetPrimitive().GetVertexBuffer() << ", " << ( mesh->GetPrimitive().GetVertexBuffer() ? mesh->GetPrimitive().GetVertexBuffer()->GetRenderCount() : 0 )
    //       << " #ib : " << mesh->GetPrimitive().GetIndexBuffer() << ", " << ( mesh->GetPrimitive().GetIndexBuffer() ? mesh->GetPrimitive().GetIndexBuffer()->GetRenderCount() : 0 )
    //       << " #tx : " << mesh->GetMaterial().GetTexture2D() << ", " << ( mesh->GetMaterial().GetTexture2D() ? mesh->GetMaterial().GetTexture2D()->GetRenderCount() : 0 ) << std::endl;
    // }
    //
    // std::random_shuffle( Meshes.begin(), Meshes.end() );
    //
    // Sort();
    // std::cout << "========================================================================================================" << std::endl;
    //
    // for ( const Dx11Mesh* mesh : Meshes )
    // {
    //     std::cout << "#vs : " << mesh->GetMaterial().GetVertexShader() << ", " << ( mesh->GetMaterial().GetVertexShader() ? mesh->GetMaterial().GetVertexShader()->GetRenderCount() : 0 )
    //       << " #ps : " << mesh->GetMaterial().GetPixelShader() << ", " << ( mesh->GetMaterial().GetPixelShader() ? mesh->GetMaterial().GetPixelShader()->GetRenderCount() : 0 )
    //       << " #vb : " << mesh->GetPrimitive().GetVertexBuffer() << ", " << ( mesh->GetPrimitive().GetVertexBuffer() ? mesh->GetPrimitive().GetVertexBuffer()->GetRenderCount() : 0 )
    //       << " #ib : " << mesh->GetPrimitive().GetIndexBuffer() << ", " << ( mesh->GetPrimitive().GetIndexBuffer() ? mesh->GetPrimitive().GetIndexBuffer()->GetRenderCount() : 0 )
    //       << " #tx : " << mesh->GetMaterial().GetTexture2D() << ", " << ( mesh->GetMaterial().GetTexture2D() ? mesh->GetMaterial().GetTexture2D()->GetRenderCount() : 0 ) << std::endl;
    // }
    //
    // std::cout << "========================================================================================================" << std::endl;
    // for ( const IDxRenderElement* renderElement : RenderElements )
    // {
    //     std::cout << renderElement << ", " << ( renderElement ? renderElement->GetRenderCount() : 0 ) << std::endl;
    // }
}

//=====================================================================================================================
// @brief	Add
//=====================================================================================================================
bool Dx11RenderQueue::Add( const Dx11Mesh* MeshPtr, const WorldMatrixBuffer* WorldBufferPtr )
{
    if ( !MeshPtr ) return false;
    if ( !MeshPtr->GetMaterial().GetVertexShader() ) return false;
    if ( !MeshPtr->GetMaterial().GetPixelShader() ) return false;

    MeshRenderElements.emplace_back( MeshPtr, WorldBufferPtr );

    return true;
}

//=====================================================================================================================
// @brief	Clear
//=====================================================================================================================
void Dx11RenderQueue::Clear()
{
    RenderElements.clear();
    RenderElements.clear();
}

//=====================================================================================================================
// @brief	Sort
//=====================================================================================================================
void Dx11RenderQueue::Sort()
{
    auto ftrCompare = [] ( const Dx11Resource* Lhs, const Dx11Resource* Rhs, bool& Order ) -> bool
    {
        if ( Lhs != Rhs )
        {
            if ( !Lhs || !Rhs )
            {
                Order = Lhs > Rhs;
                return true;
            }

            if ( Lhs->GetRenderCount() == Rhs->GetRenderCount() )
            {
                Order = Lhs > Rhs;                
            }
            else
            {
                Order = Lhs->GetRenderCount() > Rhs->GetRenderCount();   
            }
            return true;
        }
        return false;
    };

    std::sort( MeshRenderElements.begin(), MeshRenderElements.end(), [ ftrCompare ] ( const MeshRenderElement& Lhs, const MeshRenderElement& Rhs )
    {
        const Dx11Mesh* lhsMesh = Lhs.MeshPtr;
        const Dx11Mesh* rhsMesh = Rhs.MeshPtr;

        bool order = false;
        if ( ftrCompare( lhsMesh->GetMaterial ().GetVertexShader(), rhsMesh->GetMaterial().GetVertexShader (), order ) ) return order;
        if ( ftrCompare( lhsMesh->GetMaterial ().GetPixelShader (), rhsMesh->GetMaterial().GetPixelShader  (), order ) ) return order;
        if ( ftrCompare( lhsMesh->GetPrimitive().GetVertexBuffer(), rhsMesh->GetPrimitive().GetVertexBuffer(), order ) ) return order;
        if ( ftrCompare( lhsMesh->GetPrimitive().GetIndexBuffer (), rhsMesh->GetPrimitive().GetIndexBuffer (), order ) ) return order;
        if ( ftrCompare( lhsMesh->GetMaterial ().GetTexture2D   (), rhsMesh->GetMaterial ().GetTexture2D   (), order ) ) return order;

        return false;
    } );

    auto ftrAddRenderElement = [ this ] ( const Dx11Resource** CurrPtr, const Dx11Resource* NewPtr )
    {
        if ( *CurrPtr != NewPtr )
        {
            *CurrPtr = NewPtr;
            if ( NewPtr )
            {
                RenderElements.push_back( NewPtr );
            }
        }
    }; 

    const Dx11Resource* currPtrs[ 5 ] = { nullptr,  };
    for ( const MeshRenderElement& meshRenderElement : MeshRenderElements )
    {
        const Dx11Mesh* mesh = meshRenderElement.MeshPtr;

        ftrAddRenderElement( &currPtrs[ 0 ], mesh->GetMaterial ().GetVertexShader() );
        ftrAddRenderElement( &currPtrs[ 1 ], mesh->GetPrimitive().GetVertexBuffer() );
        ftrAddRenderElement( &currPtrs[ 2 ], mesh->GetPrimitive().GetIndexBuffer () );
        ftrAddRenderElement( &currPtrs[ 3 ], mesh->GetMaterial ().GetPixelShader () );
        ftrAddRenderElement( &currPtrs[ 4 ], mesh->GetMaterial ().GetTexture2D   () );

        RenderElements.push_back( &meshRenderElement.Renderer );        
    }
}

//=====================================================================================================================
// @brief	Render
//=====================================================================================================================
void Dx11RenderQueue::Render() const
{
    for ( const IDxRenderElement* renderElement : RenderElements )
    {
        renderElement->OnRender();
    }
}
