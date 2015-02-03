//
//  OGL3RenderDevice.h
//  3DGameEngine
//
//  Created by Johannes Roth on 08.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __3DGameEngine__OGL3RenderDevice__
#define __3DGameEngine__OGL3RenderDevice__

#include <IRenderDevice.h>

class COGL3RenderDevice : public IRenderDevice
{
public:
	COGL3RenderDevice();
	~COGL3RenderDevice();
    
    virtual void Create();
    virtual void Release();
    
    virtual IViewport *CreateViewport(int x, int y, int width, int height);
    virtual void ReleaseViewport(IViewport *viewport);
    
    virtual void BeginFrame();
    virtual void EndFrame();
    
    virtual void Clear(int buffers);

	virtual IVertexArray *CreateVertexArray(const CIndexedModel *indexedModel);
	virtual void ReleaseVertexArray(IVertexArray *vertexArray);
    
    virtual IShader *CreateShader(int shaderType, const std::string &sourceCode);
    virtual void ReleaseShader(IShader *shader);
    
    virtual IShaderProgram *CreateEmptyShaderProgram();
    virtual IShaderProgram *CreateShaderProgram(const std::string &vertexSourceCode, const std::string &fragmentSourceCode);
    virtual void ReleaseShaderProgram(IShaderProgram *shaderProgram);

    virtual ITexture *CreateTexture2D(const STextureData2D *data, int filter, int wrap);
    virtual ITexture *CreateTextureCubeMap(const STextureDataCubeMap *data, int filter);
    virtual void ReleaseTexture(ITexture *texture);
};

#endif