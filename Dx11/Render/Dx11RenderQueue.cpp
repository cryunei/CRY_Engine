#include "Dx11RenderQueue.h"
#include "Dx11Mesh.h"
#include "Dx11ResourceRenderer.h"
#include "../Core/Dx11VertexBuffer.h"
#include "../Core/Dx11IndexBuffer.h"
#include "../Core/Dx11VertexShader.h"
#include "../Core/Dx11PixelShader.h"
#include <algorithm>


//=====================================================================================================================
// @brief	Construct
//=====================================================================================================================
Dx11RenderQueue::Dx11RenderQueue()
: CameraPtr ( nullptr )
{
}

//=====================================================================================================================
// @brief	Initialize
//=====================================================================================================================
void Dx11RenderQueue::Initialize( unsigned int Width, unsigned int Height )
{
    RenderTarget.Initialize( Width, Height );
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
    auto ftrCompare = [] ( const IDxRenderElement* Lhs, const IDxRenderElement* Rhs, bool& Order ) -> bool
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

        for ( int i = 0; i < lhsMesh->GetMaterial().GetCount_Texture2D(); ++i )
        {
            if ( ftrCompare( lhsMesh->GetMaterial().GetRenderer_Texture2D( i ), rhsMesh->GetMaterial().GetRenderer_Texture2D( i ), order ) ) return order;
        }

        return false;
    } );

    auto ftrAddRenderElement = [ this ] ( const IDxRenderElement** CurrPtr, const IDxRenderElement* NewPtr )
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

    const IDxRenderElement* currPtrs[ 4 ] = { nullptr,  };
    const IDxRenderElement* currTexturePtrs[ MAX_TEXTURE_REGISTER_COUNT ] = { nullptr,  };
    for ( const MeshRenderElement& meshRenderElement : MeshRenderElements )
    {
        const Dx11Mesh* mesh = meshRenderElement.MeshPtr;

        ftrAddRenderElement( &currPtrs[ 0 ], mesh->GetMaterial ().GetVertexShader() );
        ftrAddRenderElement( &currPtrs[ 1 ], mesh->GetPrimitive().GetVertexBuffer() );
        ftrAddRenderElement( &currPtrs[ 2 ], mesh->GetPrimitive().GetIndexBuffer () );
        ftrAddRenderElement( &currPtrs[ 3 ], mesh->GetMaterial ().GetPixelShader () );

        for ( int i = 0; i < mesh->GetMaterial().GetCount_Texture2D(); ++i )
        {
            ftrAddRenderElement( &currTexturePtrs[ i ], mesh->GetMaterial ().GetRenderer_Texture2D( i ) );
        }

        RenderElements.push_back( &meshRenderElement.Renderer );        
    }
}

//=====================================================================================================================
// @brief	Render
//=====================================================================================================================
void Dx11RenderQueue::Render() const
{    
    float color[ 4 ] = { 0.0f, 0.2f, 0.4f, 1.0f };

    RenderTarget.Clear( color );
    RenderTarget.SetRenderTarget();

    for ( const IDxRenderElement* renderElement : RenderElements )
    {
        renderElement->OnRender();
    }
}
