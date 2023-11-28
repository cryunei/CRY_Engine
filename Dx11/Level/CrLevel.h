#pragma once


#include "../Externals/RapidJSON/include/rapidjson/document.h"
#include <string>
#include <vector>

class CrReflector;
class CrMeshActor;
class CrMesh;


//=====================================================================================================================
// @brief	CrLevel
//=====================================================================================================================
class CrLevel
{
private:
    std::vector< CrMeshActor* > Actors;
    std::vector< CrReflector* > Reflectors;
    
public:
    // Constructor
    CrLevel();

    // Release
    void Release();

    // Load from json
    void LoadFromJson( const std::string& Path );

    // Tick
    void Tick( float DeltaTime );

    // Get meshes
    const std::vector< CrMeshActor* >& GetMeshes() const { return Actors; }

    // Get reflectors
    const std::vector< CrReflector* >& GetReflectors() const { return Reflectors; }

private:
    // Load render targets from json
    void _LoadRenderTargetsFromJson( const rapidjson::Document& Document ) const;

    // Load meshes from json
    void _LoadMeshesFromJson( const rapidjson::Document& Document );

    // Load actors from json
    void _LoadActorsFromJson( const rapidjson::Document& Document );

    // Load reflectors from json
    void _LoadReflectorsFromJson( const rapidjson::Document& Document );
};
