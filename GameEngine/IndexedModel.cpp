//
//  IndexedModel.cpp
//  3DGameEngine
//
//  Created by Johannes Roth on 08.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#include "IndexedModel.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

CIndexedModel::CIndexedModel(int drawMode)
{
    m_drawMode = drawMode;
}

CIndexedModel::~CIndexedModel()
{
}

int CIndexedModel::CalculateStride() const
{
	int stride = 3;
	if (m_hasUV)      stride += 2;
	if (m_hasNormals) stride += 3;
	stride *= sizeof(float);
	return stride;
}

void CIndexedModel::SetUV(float u, float v)
{
	m_uv.u = u;
	m_uv.v = v;

	m_hasUV = true;
}

void CIndexedModel::SetNormal(float x, float y, float z)
{
	m_normal.x = x;
	m_normal.y = y;
	m_normal.z = z;

	m_hasNormals = true;
}

void CIndexedModel::AddVertex(float x, float y, float z)
{
    m_data.push_back(x);
    m_data.push_back(y);
    m_data.push_back(z);

	if (m_hasUV)
	{
		m_data.push_back(m_uv.u);
		m_data.push_back(m_uv.v);
	}

	if (m_hasNormals)
	{
		m_data.push_back(m_normal.x);
		m_data.push_back(m_normal.y);
		m_data.push_back(m_normal.z);
	}

    ++m_vertexCount;
}

void CIndexedModel::AddIndex(Index_t index)
{
	m_indices.push_back(index);

	m_hasIndices = true;
}

void CIndexedModel::SetVertexData(const float *data, int vertexCount, int vertexDesc)
{
    m_vertexCount = vertexCount;
    
    m_hasUV = (vertexDesc & eVERTEXDESC_UV);
    m_hasNormals = (vertexDesc & eVERTEXDESC_NORMAL);
    
    int stride = (3 + (m_hasUV ? 2 : 0) + (m_hasNormals ? 3 : 0));
    int size = vertexCount * stride;
    
    m_data.clear();
    m_data.insert(m_data.begin(), data, data + size);
}

void CIndexedModel::SetIndexData(const Index_t *data, int indexCount)
{
    m_hasIndices = true;
    
    m_indices.clear();
    m_indices.insert(m_indices.begin(), data, data + indexCount);
}

std::vector<CIndexedModel> CIndexedModel::LoadFromFile(const std::string &filename)
{
	Assimp::Importer importer;
    const aiScene *pScene = importer.ReadFile(filename.c_str(), aiProcess_FlipUVs |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType);
    
    std::vector<CIndexedModel> models;
    
    if (!pScene)
    {
        std::cerr << "ASSIMP: Failed to load model from file" << std::endl;
        return models;
    }
    
    for (int i = 0; i < pScene->mNumMeshes; ++i)
    {
        aiMesh *pMesh = pScene->mMeshes[i];
        
        CIndexedModel model(eDRAWMODE_TRIANGLES);

        for (int j = 0; j < pMesh->mNumVertices; ++j)
        {
            aiVector3D pos = pMesh->mVertices[j];
            aiVector3D normal = pMesh->mNormals[j];
            aiVector3D uv = pMesh->HasTextureCoords(0) ? pMesh->mTextureCoords[0][j] : aiVector3D(0, 0, 0);
            
            model.SetNormal(normal.x, normal.y, normal.z);
            model.SetUV(uv.x, uv.y);
            model.AddVertex(pos.x, pos.y, pos.z);
        }

        for (int j = 0; j < pMesh->mNumFaces; ++j)
        {
            const aiFace &face = pMesh->mFaces[j];
            
            for (int k = 0; k < 3; ++k)
            {
                model.AddIndex(face.mIndices[k]);
            }
        }
        
        models.push_back(model);
    }

    return models;
}