#pragma once


#include <vector>
#include "Dx11ResourceRenderer.h"


class Dx11ResourceRenderer;
class Dx11VertexShader;
class Dx11PixelShader;
class Dx11Texture2D;


//=====================================================================================================================
// @brief	Dx11Material
//=====================================================================================================================
class Dx11Material
{
private:
    Dx11VertexShader* VertexShader;
    Dx11PixelShader*  PixelShader;

    std::vector< Dx11ResourceRenderer* > Texture2Ds;
    
public:
    // Construct
    Dx11Material();
    
    // Initialize
    void Initialize( Dx11VertexShader* InVertexShader, Dx11PixelShader* InPixelShader );

    // Initialize texture 2d array
    void InitializeTexture2Ds( const std::vector< Dx11ResourceRenderer* >& InTexture2D );

    // Increase render count
    void IncreaseRenderCount() const;

    // Decrease render count
    void DecreaseRenderCount() const;

    // Render
    void Render() const;

    // Get vertex shader
    const Dx11VertexShader* GetVertexShader() const { return VertexShader; }

    // Get pixel shader
    const Dx11PixelShader* GetPixelShader() const { return PixelShader; }

    // Get texture 2d renderer
    const Dx11ResourceRenderer* GetRenderer_Texture2D( int Idx ) const;

    // get texture 2d count
    int GetCount_Texture2D() const { return (int)( Texture2Ds.size() ); }

    // Is renderable
    bool IsRenderable() const { return VertexShader && PixelShader; }
};
