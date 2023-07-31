#pragma once


class Dx11Resource
{
public:
    virtual ~Dx11Resource() = default;

    virtual void Release() = 0;    
};
