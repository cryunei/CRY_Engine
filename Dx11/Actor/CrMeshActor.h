#pragma once


#include "CrActor.h"
#include <vector>


class CrMesh;


//=====================================================================================================================
// @brief	CrMeshActor
//=====================================================================================================================
class CrMeshActor : public CrActor
{
private:
    CrMesh*     Mesh     = nullptr;    
    float       Opacity  = 1.f;
    bool        bReflect = false;

    std::vector< std::string > RenderTargets;

public:
    // Constructor
    CrMeshActor() = default;

    // Mesh
    const CrMesh* GetMesh() const { return Mesh; }
    void SetMesh( CrMesh* InMesh ) { Mesh = InMesh; }

    // Render target
    const std::vector< std::string >& GetRenderTargets() const { return RenderTargets; }
    void AddRenderTarget( const std::string& InRenderTarget ) { RenderTargets.emplace_back( InRenderTarget ); }

    // Ocaticy
    float GetOpacity() const { return Opacity; }
    void SetOpacity( float InOpacity ) { Opacity = InOpacity; }

    // Reflect
    bool CanReflect() const { return bReflect; }
    void SetReflect( bool InReflect ) { bReflect = InReflect; }
};
