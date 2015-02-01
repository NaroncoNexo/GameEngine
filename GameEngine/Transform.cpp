//
//  Transform.cpp
//  3DGameEngine
//
//  Created by Johannes Roth on 07.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#include "Transform.h"

void CTransform::UpdateMatrices()
{
	SMatrix4 translationMatrix = SMatrix4::CreateTranslation(m_translation.x, m_translation.y, m_translation.z);
	SMatrix4 rotationMatrix = m_rotation.GetMatrix4();
	SMatrix4 scaleMatrix = SMatrix4::CreateScale(m_scale.x, m_scale.y, m_scale.z);

	m_transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

void CTransform::Rotate(const SQuaternion &rotation)
{
    m_rotation = (rotation * m_rotation).GetNormalized();
}