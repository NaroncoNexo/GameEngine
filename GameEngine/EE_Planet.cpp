//
//  EE_Planet.cpp
//  3DGameEngine
//
//  Created by Johannes Roth on 21.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#include "EE_Planet.h"
#include "Camera.h"
#include "FileSystem.h"

/*struct SDetailModelVertex
{
    union
    {
        struct { float x, y, z; };
        SVector3 pos;
    };
    
    float u, v;
    
    union
    {
        struct { float nx, ny, nz; };
        SVector3 normal;
    };
};

CPlanetDetailMap::CPlanetDetailMap(IVertexArray *mesh, const CMaterial &material, CPlanetExtension *planet)
    : m_mesh(mesh), m_material(material), m_planet(planet)
{
}

CPlanetDetailMap::~CPlanetDetailMap()
{
}

void CPlanetDetailMap::Render(const CCamera *camera, const SMatrix4 &worldMatrix) const
{
}

CPlanetDetailMap *CPlanetDetailMap::CreateFromIndexedModel(const CIndexedModel &singleModel, const CMaterial &material, CPlanetExtension *planet)
{
    SDetailModelVertex *singleModelVertexData = (SDetailModelVertex *)singleModel.GetVertexData();
    
    CIndexedModel model;
    Index_t startIndex = 0;
    
    int stacks = 16;
    int slices = 32;

    for (int stack = 1; stack < stacks; ++stack)
    {
        for (int slice = 0; slice < slices; ++slice)
        {
            float phi = 3.14159f * 0.5f - stack * 3.14159f / (float)stacks + (RAND_NextFloat() * 0.3f - 0.15f);
            float y = sinf(phi) * planet->GetRadius();
            float scale = cosf(phi);
            
            float theta = slice * 2.0f * 3.14159f / (float)slices + (RAND_NextFloat() * 0.3f - 0.15f);
            float x = scale * sinf(theta) * planet->GetRadius();
            float z = scale * cosf(theta) * planet->GetRadius();
            
            SQuaternion rot = SQuaternion::CreateEuler(phi - 3.14159f * 0.5f, theta + 3.14159f, 0);
            
            for (int i = 0; i < singleModel.GetVertexCount(); ++i)
            {
                SDetailModelVertex v = singleModelVertexData[i];
                SVector3 pos = rot * v.pos;
                SVector3 normal = rot * v.normal;
                normal.Normalize();
                
                model.SetUV(v.u, v.v);
                model.SetNormal(normal);
                model.AddVertex(x + pos.x, y + pos.y, z + pos.z);
            }
            
            for (int i = 0; i < singleModel.GetIndexCount(); ++i)
            {
                model.AddIndex(startIndex + singleModel.GetIndexData()[i]);
            }
            
            startIndex += singleModel.GetVertexCount();
        }
    }
    
    return new CPlanetDetailMap(planet->GetEntity()->GetSubSystem()->GetRenderDevice()->CreateVertexArray(&model), material, planet);
}

void CPlanetDetailMap::ReleasePlanetDetailMap(CPlanetDetailMap *detailMap)
{
    detailMap->GetPlanet()->GetEntity()->GetSubSystem()->GetRenderDevice()->ReleaseVertexArray(detailMap->GetMesh());
    delete detailMap;
}

void CPlanetExtension::Create(int argc, va_list args)
{
    if (argc > 0)
    {
        m_planetRadius = (float)va_arg(args, double);
    }
    else
    {
        m_planetRadius = 5.0f;
    }
    
	CIndexedModel rawSphereModel;

    int stacks = 16;
    int slices = 32;

    for (int stack = 0; stack <= stacks; ++stack)
    {
        float phi = 3.14159f * 0.5f - stack * 3.14159f / (float)stacks;
        float y = sinf(phi);
        float scale = cosf(phi);

        for (int slice = 0; slice <= slices; ++slice)
        {
            float theta = slice * 2.0f * 3.14159f / (float)slices;
            float x = scale * sinf(theta);
            float z = scale * cosf(theta);

            SVector2 uv = { slice / (float)(slices * 0.5f), stack / (float)stacks };
            SVector3 normal = { x, y, z };
            SVector3 pos = normal * m_planetRadius;

            rawSphereModel.SetUV(uv);
            rawSphereModel.SetNormal(normal);
            rawSphereModel.AddVertex(pos);
        }
    }

    for (int stack = 0; stack < stacks; ++stack)
    {
        for (int slice = 0; slice < slices; ++slice)
        {
            if (stack != 0)
            {
                rawSphereModel.AddIndex((stack + 0) * (slices + 1) + slice);
                rawSphereModel.AddIndex((stack + 1) * (slices + 1) + slice);
                rawSphereModel.AddIndex((stack + 0) * (slices + 1) + slice + 1);
            }
            
            if (stack != stacks - 1)
            {
                rawSphereModel.AddIndex((stack + 0) * (slices + 1) + slice + 1);
                rawSphereModel.AddIndex((stack + 1) * (slices + 1) + slice);
                rawSphereModel.AddIndex((stack + 1) * (slices + 1) + slice + 1);
            }
        }
    }

	m_terrain = m_entity->GetSubSystem()->GetRenderDevice()->CreateVertexArray(&rawSphereModel);
    
}

void CPlanetExtension::Release()
{
	m_entity->GetSubSystem()->GetRenderDevice()->ReleaseVertexArray(m_terrain);
}

void CPlanetExtension::OnAdd()
{
}

void CPlanetExtension::OnRemove()
{
}

void CPlanetExtension::Update()
{
}

void CPlanetExtension::Render(const SEntityExtensionRenderParams &params)
{
}

void CPlanetExtension::AddLayer(const CMaterial &material)
{
    m_materials.push_back(material);
}*/