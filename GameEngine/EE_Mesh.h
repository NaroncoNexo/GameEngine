//
//  EE_Mesh.h
//  3DGameEngine
//
//  Created by Johannes Roth on 05.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __3DGameEngine__EE_Mesh__
#define __3DGameEngine__EE_Mesh__

#include "Entity.h"
#include "Material.h"
#include "IRenderDevice.h"
#include "Singleton.h"
#include <map>

class CMeshRendererExtension;

class CShaderSortedMeshRenderer : public CSingleton_tpl<CShaderSortedMeshRenderer>
{
public:
    void Render(CCamera *camera);
    
    void AddMeshRendererExtension(CMeshRendererExtension *meshRendererExtension);
    void RemoveMeshRendererExtension(CMeshRendererExtension *meshRendererExtension);
    
private:
    std::map<const CMaterial *, std::vector<const CMeshRendererExtension *>> m_meshRendererExtensions;
};

class CMeshRendererExtension : public IEntityExtension
{
public:
    virtual void Create(int argc, va_list args);
    virtual void Release();
    
    virtual void OnAdd();
    virtual void OnRemove();
    
    virtual void Update();
	virtual void Render(const SEntityExtensionRenderParams &params);
    
    inline void SetModel(const IVertexArray *model) { m_model = model; }
    inline void SetMaterial(const CMaterial *material) { m_material = material; }
    
    inline const IVertexArray *GetModel() const { return m_model; }
	inline const CMaterial *GetMaterial() const { return m_material; }

private:
    const IVertexArray *m_model { nullptr };
    const CMaterial *m_material { nullptr };
};

#endif