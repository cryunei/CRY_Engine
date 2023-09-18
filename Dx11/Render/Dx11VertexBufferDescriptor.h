#pragma once


#include "../DxCoreInc.h"
#include "../Asset/CrPrimitive.h"


//=====================================================================================================================
// @brief	EVertexStructureType
//=====================================================================================================================
enum class EVertexBufferStructureType
{
    Diffuse,
    NormalMap,
    None
};


//=====================================================================================================================
// @brief	IDxVertexBufferDescriptor
//=====================================================================================================================
class IDxVertexBufferDescriptor
{
protected:
    EVertexBufferStructureType Type = EVertexBufferStructureType::None;
    void** VerticePtr = nullptr;

    unsigned int Count  = 0;
    unsigned int Stride = 0;

public:
    static IDxVertexBufferDescriptor* Create( EVertexBufferStructureType Type );

public:
    // Read vertice
    virtual void ReadVertice( const CrPrimitive& Primitive ) = 0;

    // Getters
    EVertexBufferStructureType GetType() const { return Type; }
    void** GetVerticePtr() const { return VerticePtr; }
    unsigned int GetSize() const { return Count * Stride; }
    unsigned int GetCount() const { return Count; }
    unsigned int GetStride() const { return Stride; }
};


//=====================================================================================================================
// @brief	Dx11VertexBufferDescriptor
//=====================================================================================================================
template< typename T >
class Dx11VertexBufferDescriptor : public IDxVertexBufferDescriptor
{
protected:
    std::vector< T > Vertice; 

public:
    // Read vertice
    virtual void ReadVertice( const CrPrimitive& Primitive ) override { T::ReadVertice( Primitive, *this ); }

    // Pre read vertice
    void PreReadVertice( unsigned int InCount, unsigned int InStride );

    // Getters
    std::vector< T >& GetVerticeContainer() { return Vertice; }
};

//=====================================================================================================================
// @brief	PreReadVertice
//=====================================================================================================================
template < typename T >
void Dx11VertexBufferDescriptor<T>::PreReadVertice( unsigned int InCount, unsigned int InStride )
{
    Count = InCount;
    Stride = InStride;

    Vertice.clear();
    Vertice.reserve( Count );

    VerticePtr = (void**)Vertice.data();
}


//=====================================================================================================================
// @brief	SVertex_Diffuse
//=====================================================================================================================
struct SVertex_Diffuse
{
    XMFLOAT3 Position;  // position
    XMFLOAT2 TextureUV; // texture uv
    XMFLOAT3 Normal;    // normal

    SVertex_Diffuse( const Vector3& InPosition, const Vector2& InTextureUV, const Vector3& InNormal )
    : Position( InPosition ), TextureUV( InTextureUV ), Normal( InNormal ) {}

    // Read vertice
    static void ReadVertice( const CrPrimitive& Primitive, Dx11VertexBufferDescriptor< SVertex_Diffuse >& Descriptor )
    {
        const std::vector< Vector3 >& locations = Primitive.GetLocations();
        const std::vector< Vector2 >& uvs       = Primitive.GetUVs();
        const std::vector< Vector3 >& normals   = Primitive.GetNormals();

        int count = (unsigned int)( locations.size() );
        Descriptor.PreReadVertice( count, sizeof( SVertex_Diffuse ) );

        std::vector< SVertex_Diffuse >& vertice = Descriptor.GetVerticeContainer();
        for ( int i = 0; i < count; ++i )
        {
            vertice.emplace_back( locations[ i ], uvs[ i ], normals[ i ] );
        }
    }
};


//=====================================================================================================================
// @brief	SVertex_NormalMap
//=====================================================================================================================
struct SVertex_NormalMap
{
    XMFLOAT3 Position;   // position
    XMFLOAT2 TextureUV;  // texture uv
    XMFLOAT3 Normal;     // normal
    XMFLOAT3 Tangent;    // tangent
    XMFLOAT3 Bitangent;  // bitangent

    SVertex_NormalMap( const Vector3& InPosition, const Vector2& InTextureUV, const Vector3& InNormal, const Vector3& InTangent, const Vector3& InBitangent )
    : Position( InPosition ), TextureUV( InTextureUV ), Normal( InNormal ), Tangent( InTangent ), Bitangent( InBitangent ) {}

    // Read vertice
    static void ReadVertice( const CrPrimitive& Primitive, Dx11VertexBufferDescriptor< SVertex_NormalMap >& Descriptor )
    {
        const std::vector< Vector3 >& locations  = Primitive.GetLocations();
        const std::vector< Vector2 >& uvs        = Primitive.GetUVs();
        const std::vector< Vector3 >& normals    = Primitive.GetNormals();
        const std::vector< Vector3 >& tangents   = Primitive.GetTangents();
        const std::vector< Vector3 >& bitangents = Primitive.GetBitangents();

        int count = (unsigned int)( locations.size() );
        Descriptor.PreReadVertice( count, sizeof( SVertex_NormalMap ) );

        std::vector< SVertex_NormalMap >& vertice = Descriptor.GetVerticeContainer();
        for ( int i = 0; i < count; ++i )
        {
            vertice.emplace_back( locations[ i ], uvs[ i ], normals[ i ], tangents[ i ], bitangents[ i ] );
        }
    }
};

//=====================================================================================================================
// @brief	Create
//=====================================================================================================================
inline IDxVertexBufferDescriptor* IDxVertexBufferDescriptor::Create( EVertexBufferStructureType Type )
{
    IDxVertexBufferDescriptor* descriptor = nullptr;

    switch ( Type )
    {
    case EVertexBufferStructureType::Diffuse:   descriptor = new Dx11VertexBufferDescriptor< SVertex_Diffuse   >(); break;
    case EVertexBufferStructureType::NormalMap: descriptor = new Dx11VertexBufferDescriptor< SVertex_NormalMap >(); break;
    }

    if ( descriptor )
    {
        descriptor->Type = Type;
    }

    return descriptor;
}
