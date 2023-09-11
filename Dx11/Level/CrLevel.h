﻿#pragma once


#include <vector>


class CrMesh;


//=====================================================================================================================
// @brief	CrLevel
//=====================================================================================================================
class CrLevel
{
private:
    std::vector< CrMesh* > Meshes;
    CrMesh* TestRT;
    
public:
    // Constructor
    CrLevel();

    // Get meshes
    const std::vector< CrMesh* >& GetMeshes() const { return Meshes; }

    // Get test RT
    CrMesh* GetTestRT() const { return TestRT; }
};
