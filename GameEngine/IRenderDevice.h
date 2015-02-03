//
//  IRenderDevice.h
//  3DGameEngine
//
//  Created by Johannes Roth on 08.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __3DGameEngine__IRenderDevice__
#define __3DGameEngine__IRenderDevice__

#include "IndexedModel.h"
#include "IVertexArray.h"
#include "IShader.h"
#include "IShaderProgram.h"
#include "ITexture.h"
#include "IViewport.h"

typedef unsigned char Pixel_t;

enum
{
    eCLEAR_COLOR = 1 << 0,
    eCLEAR_DEPTH = 1 << 1,
    eCLEAR_STENCIL = 1 << 2
};

class IRenderDevice
{
public:
	IRenderDevice() {  }
	virtual ~IRenderDevice() {  }
    
    virtual void Create() = 0;
    virtual void Release() = 0;
    
    virtual IViewport *CreateViewport(int x, int y, int width, int height) = 0;
    virtual void ReleaseViewport(IViewport *viewport) = 0;
    
    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;
    
    virtual void Clear(int buffers) = 0;

	virtual IVertexArray *CreateVertexArray(const CIndexedModel *indexedModel) = 0;
	virtual void ReleaseVertexArray(IVertexArray *vertexArray) = 0;

    virtual IShader *CreateShader(int shaderType, const std::string &sourceCode) = 0;
    virtual void ReleaseShader(IShader *shader) = 0;
    
    virtual IShaderProgram *CreateEmptyShaderProgram() = 0;
    virtual IShaderProgram *CreateShaderProgram(const std::string &vertexSourceCode, const std::string &fragmentSourceCode) = 0;
    virtual void ReleaseShaderProgram(IShaderProgram *shaderProgram) = 0;

    virtual ITexture *CreateTexture2D(const STextureData2D *data, int filter, int wrap) = 0;
    virtual ITexture *CreateTextureCubeMap(const STextureDataCubeMap *data, int filter) = 0;
    virtual void ReleaseTexture(ITexture *texture) = 0;
};

#endif