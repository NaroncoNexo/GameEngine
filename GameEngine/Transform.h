//
//  Transform.h
//  3DGameEngine
//
//  Created by Johannes Roth on 07.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __3DGameEngine__Transform__
#define __3DGameEngine__Transform__

#include "Math3D.h"

class CTransform
{
public:
	void UpdateMatrices();
    
    void Rotate(const SQuaternion &rotation);
	void LookAt(const SVector3 &point);

    inline void SetTranslation(const SVector3 &translation) { m_translation = translation; }
    inline void SetRotation(const SQuaternion &rotation) { m_rotation = rotation; }
    inline void SetScale(const SVector3 &scale) { m_scale = scale; }

	inline const SVector3 &GetTranslation() const { return m_translation; }
	inline const SQuaternion &GetRotation() const { return m_rotation; }
	inline const SVector3 &GetScale() const { return m_scale; }

	inline const SMatrix4 &GetTransformationMatrix() const { return m_transformationMatrix; }

private:
	SMatrix4 m_transformationMatrix;
    SQuaternion m_rotation { 0, 0, 0, 1 };
	SVector3 m_translation { 0, 0, 0 };
	SVector3 m_scale { 1, 1, 1 };
};

#endif