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
	m_rotation = (m_rotation * rotation).GetNormalized();
}

void CTransform::LookAt(const SVector3 &point)
{
	/* glm::vec3 lookVector = glm::vec3(x, y, z);
    assert(lookVector != position);

    glm::vec3 direction = glm::normalize(lookVector-position);
    float dot = glm::dot(glm::vec3(0, 0, 1), direction);
    if (fabs(dot - (-1.0f)) < 0.000001f) {
        rotation = glm::angleAxis(RadiansToDegrees(M_PI), glm::vec3(0, 1, 0));
        return;
    }
    else if (fabs(dot - (1.0f)) < 0.000001f) {
        rotation = glm::quat();
        return;
    }

    float angle = -RadiansToDegrees(acosf(dot));

    glm::vec3 cross = glm::normalize(glm::cross(glm::vec3(0, 0, 1), direction));
    rotation = glm::normalize(glm::angleAxis(angle, cross));*/

	SVector3 forward = (point - m_translation).GetNormalized();
	float dot = SVector3(0, 0, 1).Dot(forward);

	if (fabsf(dot + 1.0f) < 0.000001f)
	{
		m_rotation = SQuaternion::CreateAxisRotation(SVector3(0, 1, 0), PI);
		return;
	}
	else if (fabsf(dot - 1.0f) < 0.000001f)
	{
		m_rotation = SQuaternion(0, 0, 0, 1);
		return;
	}

	float angle = -acosf(dot);

	SVector3 cross = SVector3(0, 0, 1).Cross(forward).GetNormalized();
	m_rotation = SQuaternion::CreateAxisRotation(cross, angle).GetNormalized();
}