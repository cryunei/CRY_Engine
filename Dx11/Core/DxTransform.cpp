#include "DxTransform.h"


//=================================================================================================
// @brief	Construct
//=================================================================================================
DxTransform::DxTransform()
: Location ( Vector3::Zero )
, Rotation ( Quaternion::Identity )
, Scale    ( Vector3::One )
{
}

//=================================================================================================
// @brief	To local matrix
//=================================================================================================
Matrix DxTransform::ToLocalMatrix() const
{
    return Matrix::CreateScale         ( Scale     ) *
           Matrix::CreateFromQuaternion( Rotation  ) *
           Matrix::CreateTranslation   ( Location  );
}
