#pragma once


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
    Dx11Texture2D*    Texture2D;
    
public:
    // Construct
    Dx11Material();
    
    // Initialize
    void Initialize( Dx11VertexShader* InVertexShader, Dx11PixelShader* InPixelShader, Dx11Texture2D* InTexture2D );

    // Render
    void Render() const;

    // Get vertex shader
    const Dx11VertexShader* GetVertexShader() const { return VertexShader; }

    // Get pixel shader
    const Dx11PixelShader* GetPixelShader() const { return PixelShader; }

    // Get texture
    const Dx11Texture2D* GetTexture2D() const { return Texture2D; }

    // Is renderable
    bool IsRenderable() const { return VertexShader && PixelShader; }
};
