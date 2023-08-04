#pragma once


#include "CrAsset.h"
#include "../DxTypes.h"
#include <vector>


//=====================================================================================================================
// @brief	CrIndexBuffer
//=====================================================================================================================
class CrIndexBuffer : public  CrAsset
{
private:
    std::vector< unsigned int > Indices;
    D3D11_USAGE                 Usage;
    D3D11_CPU_ACCESS_FLAG       CpuAccessFlag;

public:
    // Contructor
    CrIndexBuffer();
    CrIndexBuffer( const CrIndexBuffer& Other ) = default;
    CrIndexBuffer( CrIndexBuffer&& Other ) noexcept = default;

    // Destructor
    ~CrIndexBuffer() = default;

    // operators
    CrIndexBuffer& operator=( const CrIndexBuffer& Other ) = default;
    CrIndexBuffer& operator=( CrIndexBuffer&& Other ) noexcept = default;

    // Getters
    const std::vector< unsigned int >& GetIndices() const { return Indices; }
    D3D11_USAGE GetUsage() const { return Usage; }
    D3D11_CPU_ACCESS_FLAG GetCpuAccessFlag() const { return CpuAccessFlag; }
};
