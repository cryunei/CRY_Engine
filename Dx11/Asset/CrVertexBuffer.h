#pragma once


#include "CrAsset.h"
#include "../DxTypes.h"
#include <vector>


class CrVertexBuffer : public CrAsset
{
public:
    friend class FbxImportHelper;

private:
    std::vector< Vertex > Vertices;
    D3D11_USAGE           Usage;
    D3D11_CPU_ACCESS_FLAG CpuAccessFlag;

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
    const std::vector< Vertex >& GetVertices() const { return Vertices; }
    D3D11_USAGE GetUsage() const { return Usage; }
    D3D11_CPU_ACCESS_FLAG GetCpuAccessFlag() const { return CpuAccessFlag; }
};
