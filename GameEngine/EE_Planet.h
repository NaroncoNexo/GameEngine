//
//  EE_Planet.h
//  3DGameEngine
//
//  Created by Johannes Roth on 21.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __3DGameEngine__EE_Planet__
#define __3DGameEngine__EE_Planet__

/*#include "Entity.h"
#include "IRenderDevice.h"
#include "Material.h"

class CPlanetExtension;

class CPlanetDetailMap
{
public:
    CPlanetDetailMap(IVertexArray *mesh, const CMaterial &material, CPlanetExtension *planet);
    ~CPlanetDetailMap();
    
    void Render(const CCamera *camera, const SMatrix4 &worldMatrix) const;
    
    inline void SetMesh(IVertexArray *mesh) { m_mesh = mesh; }
    inline void SetMaterial(const CMaterial &material) { m_material = material; }
    
    inline IVertexArray *GetMesh() const { return m_mesh; }
    inline CMaterial GetMaterial() const { return m_material; }
    inline CPlanetExtension *GetPlanet() const { return m_planet; }
    
    static CPlanetDetailMap *CreateFromIndexedModel(const CIndexedModel &singleModel, const CMaterial &material, CPlanetExtension *planet);
    static void ReleasePlanetDetailMap(CPlanetDetailMap *detailMap);
    
private:
    IVertexArray *m_mesh;
    CMaterial m_material;
    CPlanetExtension *m_planet;
};

class CPlanetExtension : public IEntityExtension
{
public:
	virtual void Create(int argc, va_list args);
	virtual void Release();

	virtual void OnAdd();
	virtual void OnRemove();

	virtual void Update();
	virtual void Render(const SEntityExtensionRenderParams &params);
    
    void AddLayer(const CMaterial &material);
    
    inline void AddDetailMap(CPlanetDetailMap *planetDetailMap) { m_detailMaps.push_back(planetDetailMap); }
    
    inline float GetRadius() const { return m_planetRadius; }
    
private:
	IVertexArray *m_terrain { nullptr };
    std::vector<CMaterial> m_materials;
    std::vector<CPlanetDetailMap *> m_detailMaps;
    float m_planetRadius;
};*/

#endif