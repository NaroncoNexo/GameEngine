//
//  OGL3RenderDevice.cpp
//  3DGameEngine
//
//  Created by Johannes Roth on 08.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#include "OGL3RenderDevice.h"
#include "OGL3VertexStream.h"
#include "OGL3VertexArray.h"
#include "OGL3ShaderProgram.h"
#include "OGL3Texture.h"
#include "OGL3Viewport.h"
#include "OGL3.h"
#include <functional>

COGL3RenderDevice::COGL3RenderDevice()
{
}

COGL3RenderDevice::~COGL3RenderDevice()
{
}

void COGL3RenderDevice::Create()
{
#ifdef _WIN32
	glewExperimental = GL_TRUE;
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW\nError message: " << glewGetErrorString(error) << std::endl;
	}
#endif
}

void COGL3RenderDevice::Release()
{
}

IViewport *COGL3RenderDevice::CreateViewport(int x, int y, int width, int height)
{
    return new COGL3Viewport(x, y, width, height);
}

void COGL3RenderDevice::ReleaseViewport(IViewport *viewport)
{
    delete ((COGL3Viewport *)viewport);
}

void COGL3RenderDevice::BeginFrame()
{
}

void COGL3RenderDevice::EndFrame()
{
}

void COGL3RenderDevice::Clear(int buffers)
{
    int GLBuffers = 0;
    GLBuffers |= (buffers & eCLEAR_COLOR) ? GL_COLOR_BUFFER_BIT : 0;
    GLBuffers |= (buffers & eCLEAR_DEPTH) ? GL_DEPTH_BUFFER_BIT : 0;
    GLBuffers |= (buffers & eCLEAR_STENCIL) ? GL_STENCIL_BUFFER_BIT : 0;
    
    glClear(GLBuffers);
}

IVertexArray *COGL3RenderDevice::CreateVertexArray(const CIndexedModel *indexedModel)
{
	auto stride = indexedModel->CalculateStride();

	std::vector<COGL3VertexStream> streams;

	int offset = 0;
	streams.push_back(COGL3VertexStream(0, 3, stride, offset));
    offset += 3 * sizeof(float);

    if (indexedModel->HasUV())
    {
        streams.push_back(COGL3VertexStream(1, 2, stride, offset));
        offset += 2 * sizeof(float);
    }
    if (indexedModel->HasNormals())
    {
        streams.push_back(COGL3VertexStream(2, 3, stride, offset));
        offset += 3 * sizeof(float);
    }

    return new COGL3VertexArray(indexedModel->GetDrawMode(),
                                indexedModel->GetVertexData(), indexedModel->GetVertexCount(),
                                indexedModel->GetIndexData(), indexedModel->GetIndexCount(),
                                stride, streams);
}

void COGL3RenderDevice::ReleaseVertexArray(IVertexArray *vertexArray)
{
	delete vertexArray;
}

IShader *COGL3RenderDevice::CreateShader(int shaderType, const std::string &sourceCode)
{
    return new COGL3Shader(shaderType, sourceCode);
}

void COGL3RenderDevice::ReleaseShader(IShader *shader)
{
    delete shader;
}

IShaderProgram *COGL3RenderDevice::CreateEmptyShaderProgram()
{
    return new COGL3ShaderProgram;
}

void COGL3RenderDevice::ReleaseShaderProgram(IShaderProgram *shaderProgram)
{
    delete shaderProgram;
}

ITexture *COGL3RenderDevice::CreateTexture2D(const STextureData2D &data, int filter, int wrap)
{
    return new COGL3Texture(data, filter, wrap);
}

ITexture *COGL3RenderDevice::CreateTextureCubeMap(const STextureDataCubeMap &data, int filter)
{
    return new COGL3Texture(data, filter);
}

void COGL3RenderDevice::ReleaseTexture(ITexture *texture)
{
    delete texture;
}