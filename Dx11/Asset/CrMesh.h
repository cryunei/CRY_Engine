#pragma once


#include "CrAsset.h"
#include <string>
#include <vector>

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

    std::vector< CrTexture2D* > Texture2DPtrs;

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

    // Texture2D
    const CrTexture2D* GetTexture2D( int Idx ) const { return Texture2DPtrs[ Idx ]; }
    int GetCount_Texture2D() const { return (int)( Texture2DPtrs.size() ); }
};
