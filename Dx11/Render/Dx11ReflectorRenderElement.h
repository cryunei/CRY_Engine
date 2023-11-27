#pragma once


#include "Dx11MeshRenderElement.h"
#include <string>

//=====================================================================================================================
// @brief	Dx11ReflectorRenderElement
//=====================================================================================================================
class Dx11ReflectorRenderElement : public Dx11MeshRenderElement
{
private:
    std::string ReflectorName;

public:
    // Construct
    Dx11ReflectorRenderElement() = default;

    // On render
    virtual void OnRender() const override;

    // Reflector name
    void SetReflectorName( const std::string& InReflectorName ) { ReflectorName = InReflectorName; }
    const std::string& GetReflectorName() const { return ReflectorName; }
    
};
