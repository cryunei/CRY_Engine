#pragma once


#include "CrAsset.h"
#include "../DxTypes.h"
#include <vector>


//=====================================================================================================================
// @brief	CrPrimitive
//=====================================================================================================================
class CrPrimitive : public CrAsset
{
public:
    friend class FbxImportHelper;

public:
    // Initialize static primitives
    static void InitializeStaticPrimitives();

private:
    std::vector< Vector3 >      Locations;
    std::vector< Vector2 >      UVs;
    std::vector< Vector3 >      Normals;
    std::vector< Vector3 >      Tangents;
    std::vector< Vector3 >      Bitangents;
    std::vector< unsigned int > Indices;

    D3D11_USAGE           Dx11Usage;
    D3D11_CPU_ACCESS_FLAG Dx11CpuAccessFlag;

public:
    // Contructor
    CrPrimitive();
    CrPrimitive( const CrPrimitive& Other ) = default;
    CrPrimitive( CrPrimitive&& Other ) noexcept = default;

    // Destructor
    ~CrPrimitive() = default;

    // Reserve
    void Reserve( int NumVertices );

    // operators
    CrPrimitive& operator=( const CrPrimitive& Other ) = default;
    CrPrimitive& operator=( CrPrimitive&& Other ) noexcept = default;

    // Getters
    const std::vector< Vector3 >& GetLocations() const { return Locations; }
    const std::vector< Vector2 >& GetUVs() const { return UVs; }
    const std::vector< Vector3 >& GetNormals() const { return Normals; }
    const std::vector< Vector3 >& GetTangents() const { return Tangents; }
    const std::vector< Vector3 >& GetBitangents() const { return Bitangents; }
    const std::vector< unsigned int >& GetIndices() const { return Indices; }

    D3D11_USAGE GetDx11Usage() const { return Dx11Usage; }
    D3D11_CPU_ACCESS_FLAG GetDx11CpuAccessFlag() const { return Dx11CpuAccessFlag; }
};
