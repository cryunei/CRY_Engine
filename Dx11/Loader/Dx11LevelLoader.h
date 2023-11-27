#pragma once
#include "../Level/CrLevel.h"

class Dx11Renderer;
class Dx11Mesh;


class Dx11LevelLoader
{
public:
    // Load
    static void Load( class CrLevel& InLevel, Dx11Renderer& InRenderer );
    
};
