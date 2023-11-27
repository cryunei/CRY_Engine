#include "Dx11RenderQueue.h"
#include "Dx11ConstantBufferStructure.h"
#include "Dx11GlobalConstantBuffers.h"
#include "Dx11ReflectorRenderElement.h"
#include "Dx11ResourceRenderer.h"
#include "../Actor/CrMeshActor.h"
#include "../Actor/Camera/CrCamera.h"
#include "../Asset/CrMesh.h"
#include "../Asset/CrPixelShader.h"
#include "../Asset/CrPrimitive.h"
#include "../Asset/CrVertexShader.h"
#include "../Core/Dx11CoreTypes.h"
#include "../Core/Dx11IndexBuffer.h"
#include "../Core/Dx11ObjectManager.h"
#include "../Core/Dx11PixelShader.h"
#include "../Core/Dx11VertexBuffer.h"
#include "../Core/Dx11VertexShader.h"
#include <algorithm>


//=====================================================================================================================
// @brief	Construct
//=====================================================================================================================
Dx11RenderQueue::Dx11RenderQueue()
: CameraPtr       ( nullptr )
, RenderTargetPtr ( nullptr )
{
}

//=====================================================================================================================
// @brief	Initialize render target
//=====================================================================================================================
void Dx11RenderQueue::InitializeRenderTarget( const std::string& RenderTargetName )
{
    RenderTargetPtr = GetDx11ObjectManager()->Get< Dx11RenderTarget >( EDx11ResourceType::RenderTarget, RenderTargetName );
}

//=====================================================================================================================
// @brief	Add
//=====================================================================================================================
bool Dx11RenderQueue::Add( const CrMeshActor& MeshActor )
{
    const CrMesh* crMesh = MeshActor.GetMesh();

    Dx11MeshRenderElement* elem = nullptr;

    switch ( MeshActor.GetType() )
    {
    case ECrAssetType::MeshActor: elem = new Dx11MeshRenderElement(); break;
    case ECrAssetType::Reflector:
        {
            elem = new Dx11ReflectorRenderElement();
            ((Dx11ReflectorRenderElement*)( elem ) )->SetReflectorName( MeshActor.GetName() ); 
        }
        break;
    }

    elem->Transform    = &MeshActor.GetTransform();
    elem->Opacity      = MeshActor.GetOpacity();
    elem->VertexShader = GetDx11ObjectManager()->GetFrom< Dx11VertexShader >( EDx11ResourceType::VertexShader, crMesh->GetVertexShader() );
    elem->PixelShader  = GetDx11ObjectManager()->GetFrom< Dx11PixelShader  >( EDx11ResourceType::PixelShader , crMesh->GetPixelShader()  );
    elem->VertexBuffer = GetDx11ObjectManager()->GetFrom< Dx11VertexBuffer >( EDx11ResourceType::VertexBuffer, crMesh );
    elem->IndexBuffer  = GetDx11ObjectManager()->GetFrom< Dx11IndexBuffer  >( EDx11ResourceType::IndexBuffer , crMesh->GetPrimitve()     );
    
    for ( int t = 0; t < crMesh->GetCount_Texture2D(); ++t )
    {
        Dx11ResourceRenderer* dxRR = GetDx11ObjectManager()->CreateResourceRenderer_Texture2D( crMesh->GetTexture2D( t ), t );
        if ( !dxRR ) break;

        elem->Texture2Ds.push_back( dxRR );
    }

    MeshRenderElements.push_back( elem );

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
    std::sort( MeshRenderElements.begin(), MeshRenderElements.end(), [ this ] ( const Dx11MeshRenderElement* Lhs, const Dx11MeshRenderElement* Rhs )
    {
        bool order = false;
        if ( _CompareRenderCount( Lhs->VertexShader, Rhs->VertexShader, order ) ) return order;
        if ( _CompareRenderCount( Lhs->PixelShader,  Rhs->PixelShader,  order ) ) return order;
        if ( _CompareRenderCount( Lhs->VertexBuffer, Rhs->VertexBuffer, order ) ) return order;
        if ( _CompareRenderCount( Lhs->IndexBuffer,  Rhs->IndexBuffer,  order ) ) return order;

        for ( int i = 0; i < Lhs->Texture2Ds.size(); ++i )
        {
            if ( _CompareRenderCount( Lhs->Texture2Ds[ i ], Rhs->Texture2Ds[ i ], order ) ) return order;
        }

        return false;
    } );

    const IDxRenderElement* currPtrs[ 4 ] = { nullptr,  };
    const IDxRenderElement* currTexturePtrs[ MAX_TEXTURE_REGISTER_COUNT ] = { nullptr,  };
    for ( const Dx11MeshRenderElement* meshRenderElement : MeshRenderElements )
    {
        _AddRenderElement( &currPtrs[ 0 ], meshRenderElement->VertexShader );
        _AddRenderElement( &currPtrs[ 1 ], meshRenderElement->VertexBuffer );
        _AddRenderElement( &currPtrs[ 2 ], meshRenderElement->IndexBuffer  );
        _AddRenderElement( &currPtrs[ 3 ], meshRenderElement->PixelShader  );

        for ( int i = 0; i < meshRenderElement->Texture2Ds.size(); ++i )
        {
            _AddRenderElement( &currTexturePtrs[ i ], meshRenderElement->Texture2Ds[ i ] );
        }

        RenderElements.push_back( meshRenderElement );        
    }
}

//=====================================================================================================================
// @brief	Render
//=====================================================================================================================
void Dx11RenderQueue::Render() const
{
    if ( CameraPtr )
    {
        GetDx11GCB()->GetBuffer( EGlobalConstantBufferType::ViewProjection )->Update< ViewProjMatrix >( ViewProjMatrix( CameraPtr->GetViewMatrix().Transpose(), CameraPtr->GetProjectionMatrix( (float)( RenderTargetPtr->GetViewport().Width ), (float)( RenderTargetPtr->GetViewport().Height ) ).Transpose() ) );
        GetDx11GCB()->GetBuffer( EGlobalConstantBufferType::Camera )->Update< CameraProperty >( CameraProperty( CameraPtr->GetTransform()->GetLocation() ) );
    }

    RenderTargetPtr->SetRenderTarget();

    for ( const IDxRenderElement* renderElement : RenderElements )
    {
        renderElement->OnRender();
    }
}

//=====================================================================================================================
// @brief	Compare render count
//=====================================================================================================================
bool Dx11RenderQueue::_CompareRenderCount( const IDxRenderElement* Lhs, const IDxRenderElement* Rhs, bool& Order ) const
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
}

//=====================================================================================================================
// @brief	Add render element
//=====================================================================================================================
void Dx11RenderQueue::_AddRenderElement( const IDxRenderElement** CurrPtr, const IDxRenderElement* NewPtr )
{
    if ( *CurrPtr != NewPtr )
    {
        *CurrPtr = NewPtr;
        if ( NewPtr )
        {
            RenderElements.push_back( NewPtr );
        }
    }
}
