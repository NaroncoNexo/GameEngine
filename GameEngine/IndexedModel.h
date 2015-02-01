//
//  IndexedModel.h
//  3DGameEngine
//
//  Created by Johannes Roth on 08.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __3DGameEngine__IndexedModel__
#define __3DGameEngine__IndexedModel__

#include "Math3D.h"
#include <vector>
#include <string>

enum
{
    eDRAWMODE_POINTS,
    eDRAWMODE_LINESTRIP,
    eDRAWMODE_LINELOOP,
    eDRAWMODE_LINES,
    eDRAWMODE_TRIANGLESTRIP,
    eDRAWMODE_TRIANGLEFAN,
    eDRAWMODE_TRIANGLES
};

enum
{
    eVERTEXDESC_POSITION = 1 << 0,
    eVERTEXDESC_UV       = 1 << 1,
    eVERTEXDESC_NORMAL   = 1 << 2
};

typedef unsigned int Index_t;

class CIndexedModel
{
public:
	CIndexedModel(int drawMode);
	~CIndexedModel();

	int CalculateStride() const;

	void SetUV(float u, float v);
	void SetNormal(float x, float y, float z);
	void AddVertex(float x, float y, float z);
	void AddIndex(Index_t index);

    void SetVertexData(const float *data, int vertexCount, int vertexDesc);
    void SetIndexData(const Index_t *data, int indexCount);
    
	inline void SetUV(const SVector2 &uv) { SetUV(uv.u, uv.v); }
	inline void SetNormal(const SVector3 &normal) { SetNormal(normal.x, normal.y, normal.z); }
	inline void AddVertex(const SVector3 &vertex) { AddVertex(vertex.x, vertex.y, vertex.z); }

    inline int GetDrawMode() const { return m_drawMode; }
    
	inline const float *GetVertexData() const { return &m_data[0]; }
	inline const Index_t *GetIndexData() const { return &m_indices[0]; }

	inline int GetVertexCount() const { return m_vertexCount; }
	inline int GetIndexCount() const { return (int)m_indices.size(); }

	inline bool HasUV() const { return m_hasUV; }
	inline bool HasNormals() const { return m_hasNormals; }
	inline bool HasIndices() const { return m_hasIndices; }

	static std::vector<CIndexedModel> LoadFromFile(const std::string &filename);

private:
    int m_drawMode { 0 };
    
	int m_vertexCount { 0 };
	std::vector<float> m_data;
	std::vector<Index_t> m_indices;

	SVector2 m_uv;
	SVector3 m_normal;

	bool m_hasUV { false };
	bool m_hasNormals { false };
	bool m_hasIndices { false };

	int m_stride { 0 };
};

#endif