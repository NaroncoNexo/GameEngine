//
//  RenderDeviceUtils.cpp
//  3DGameEngine
//
//  Created by Johannes Roth on 04.02.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#include "RenderDeviceUtils.h"

ITexture *LoadTexture2D(const std::string &name)
{
	return g_subSystem->GetRenderDevice()->CreateTexture2D(STextureData2D::LoadFromFile(CFileSystem::GetInstance()->GetPathToResourceFile(name)), eTEXTUREFILTER_NEAREST, eTEXTUREWRAP_REPEAT);
}

ITexture *LoadTextureCubeMap(const std::string &name)
{
	return g_subSystem->GetRenderDevice()->CreateTextureCubeMap(STextureDataCubeMap::LoadFromFile(CFileSystem::GetInstance()->GetPathToResourceFile(name), true), eTEXTUREFILTER_NEAREST);
}

IShaderProgram *CreateShaderProgram(IShader *vertexShader, IShader *fragmentShader)
{
	IShaderProgram *shaderProgram = g_subSystem->GetRenderDevice()->CreateEmptyShaderProgram();

	shaderProgram->AddShader(vertexShader);
	shaderProgram->AddShader(fragmentShader);
	shaderProgram->Build();

	return shaderProgram;
}

IShaderProgram *CreateShaderProgram(const std::string &vertexShaderSourceCode, const std::string &fragmentShaderSourceCode)
{
	IShader *vertexShader = g_subSystem->GetRenderDevice()->CreateShader(eSHADERTYPE_VERTEX, vertexShaderSourceCode);
	IShader *fragmentShader = g_subSystem->GetRenderDevice()->CreateShader(eSHADERTYPE_FRAGMENT, fragmentShaderSourceCode);

	IShaderProgram *shaderProgram = CreateShaderProgram(vertexShader, fragmentShader);

	g_subSystem->GetRenderDevice()->ReleaseShader(vertexShader);
	g_subSystem->GetRenderDevice()->ReleaseShader(fragmentShader);

	return shaderProgram;
}
