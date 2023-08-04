#pragma once


#include "CrAsset.h"
#include <string>


class CrTexture2D;
class CrPixelShader;
class CrIndexBuffer;
class CrVertexShader;
class CrVertexBuffer;


//=====================================================================================================================
// @brief	CrMesh
//=====================================================================================================================
class CrMesh : public CrAsset
{
private:
    CrVertexShader* VertexShaderPtr;
    CrVertexBuffer* VertexBufferPtr;
    CrIndexBuffer*  IndexBufferPtr;
    CrPixelShader*  PixelShaderPtr;
    CrTexture2D*    Texture2DPtr;

public:
    // Constructor
    CrMesh();

    // Load vertex shader
    void LoadVertexShader( const std::string& Name );

    // Load vertex buffer
    void LoadVertexBuffer( const std::string& Name );

    // Load index buffer
    void LoadIndexBuffer( const std::string& Name );

    // Load pixel shader
    void LoadPixelShader( const std::string& Name );

    // Load texture
    void LoadTexture( const std::string& Name );

    // Getters
    const CrVertexShader* GetVertexShader() const { return VertexShaderPtr; }
    const CrVertexBuffer* GetVertexBuffer() const { return VertexBufferPtr; }
    const CrIndexBuffer*  GetIndexBuffer()  const { return IndexBufferPtr;  }
    const CrPixelShader*  GetPixelShader()  const { return PixelShaderPtr;  }
    const CrTexture2D*    GetTexture2D()    const { return Texture2DPtr;    }

};
