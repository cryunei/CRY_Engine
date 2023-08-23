#pragma once


#include "CrAsset.h"
#include "../Render/Dx11VertexStructure.h"
#include <vector>


//=====================================================================================================================
// @brief	CrVertexBuffer
//=====================================================================================================================
class CrVertexBuffer : public CrAsset
{
public:
    friend class FbxImportHelper;

private:
    std::vector< Vector3 > Locations;
    std::vector< Vector2 > UVs;
    std::vector< Vector3 > Normals;
    std::vector< Vector3 > Tangents;
    std::vector< Vector3 > Bitangents;

    D3D11_USAGE           Dx11Usage;
    D3D11_CPU_ACCESS_FLAG Dx11CpuAccessFlag;

public:
    // Contructor
    CrVertexBuffer();
    CrVertexBuffer( const CrVertexBuffer& Other ) = default;
    CrVertexBuffer( CrVertexBuffer&& Other ) noexcept = default;

    // Destructor
    ~CrVertexBuffer() = default;

    // operators
    CrVertexBuffer& operator=( const CrVertexBuffer& Other ) = default;
    CrVertexBuffer& operator=( CrVertexBuffer&& Other ) noexcept = default;

    // Getters
    const std::vector< Vector3 >& GetLocations() const { return Locations; }
    const std::vector< Vector2 >& GetUVs() const { return UVs; }
    const std::vector< Vector3 >& GetNormals() const { return Normals; }
    const std::vector< Vector3 >& GetTangents() const { return Tangents; }
    const std::vector< Vector3 >& GetBitangents() const { return Bitangents; }

    D3D11_USAGE GetDx11Usage() const { return Dx11Usage; }
    D3D11_CPU_ACCESS_FLAG GetDx11CpuAccessFlag() const { return Dx11CpuAccessFlag; }

    // Get vertices
    void GetVertices( std::vector< Vertex_Diffuse >& OutVertices ) const;
    void GetVertices( std::vector< Vertex_NormalMap >& OutVertices ) const;
};
