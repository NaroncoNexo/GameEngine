//
//  main.cpp
//  3DGameEngine
//
//  Created by Johannes Roth on 21.12.14.
//  Copyright (c) 2014 Johannes Roth. All rights reserved.
//

#include <iostream>

#include "Material.h"
#include "Entity.h"
#include "Camera.h"
#include "EE_Skybox.h"
#include "EE_Mesh.h"
#include "EE_Planet.h"
#include "FileSystem.h"
#include "CCMSkybox.h"
#include "sdl/SDL2SubSystem.h"
#include "Environment.h"
#include "RenderDeviceUtils.h"

int main(int argc, char *argv[])
{
	g_subSystem = new CSDL2SubSystem;
	g_subSystem->CreateDisplay(1280, 720, "Hello, World!");
	
	std::string vertexShaderSourceCode = ""
		"#version 330\n"
		"\n"
		"\n"
		"layout (location = 0) in vec3 a_Position;"
		"layout (location = 1) in vec2 a_TextureCoordinate;"
		"layout (location = 2) in vec3 a_Normal;"
		""
		"out vec2 v_TextureCoordinate;\n"
		"out vec3 v_Normal;\n"
		""
		"uniform mat4 u_WorldMatrix;"
		"uniform mat4 u_WorldViewProjectionMatrix;"
		"uniform mat4 u_TextureMatrix;"
		""
		"void main()"
		"{"
		"   v_TextureCoordinate = (u_TextureMatrix * vec4(a_TextureCoordinate, 0, 1)).xy;"
		"   v_Normal = (u_WorldMatrix * vec4(a_Normal, 0)).xyz;"
		"   "
		"   gl_Position = u_WorldViewProjectionMatrix * vec4(a_Position, 1);"
		"}"
		"";

	std::string fragmentShaderSourceCode = ""
		"#version 330\n"
		"\n"
		"in vec2 v_TextureCoordinate;\n"
		"in vec3 v_Normal;\n"
		"\n"
		"out vec4 v_FragColor;\n"
		"\n"
		//"uniform sampler2D u_DiffuseTexture;\n"
		"\n"
		"void main()\n"
		"{\n"
		//"   vec4 diffuseColor = texture(u_DiffuseTexture, v_TextureCoordinate);\n"
		"   \n"
		//"   if (diffuseColor.a < 0.5)\n"
		//"       discard;\n"
		"   \n"
		"   float nDotL = max(0.0, dot(v_Normal, normalize(vec3(-0.3, 1.0, -0.5))));\n"
		"   \n"
		"   v_FragColor = vec4(vec3(1, 0, 1), 1.0);\n"
		"}"
		"";

	IShaderProgram *shader = CreateShaderProgram(vertexShaderSourceCode, fragmentShaderSourceCode);

	ITexture *diffuseTexture = LoadTexture2D("res/tex/grass_diff.png");
	ITexture *cubeMap = LoadTextureCubeMap("res/oceanSkybox.png");

	CEntityRoot *root = new CEntityRoot;

	CEntity *sphere = root->AddChild();

	CCamera *camera = new CCamera();
	camera->SetViewport(0, 0, g_subSystem->GetDisplay()->GetWidth(), g_subSystem->GetDisplay()->GetHeight());
	camera->SetPerspectiveProjection(DEG2RAD(70.0f), camera->GetViewport()->GetAspectRatio(), 0.01f, 100.0f);
	camera->GetTransform()->SetTranslation({ 0, 0, -5 });
//	camera->GetTransform()->SetRotation(SQuaternion::CreateEuler(0, 0, 0));

	CSkybox *skybox = new CSkybox(cubeMap);
	CSkyboxClearMethod *skyboxClearMethod = new CSkyboxClearMethod(skybox);

	camera->SetClearMethod(skyboxClearMethod);

	root->AddCamera(camera);

	IVertexArray *sphereMesh = g_subSystem->GetRenderDevice()->CreateVertexArray(&CIndexedModel::LoadFromFile(g_FileSys->GetPathToResourceFile("res/sphere.obj"))[0]);

	CMaterial *sphereMaterial = new CMaterial;
	sphereMaterial->SetShader(shader);

	CMeshRendererExtension *meshRenderer = sphere->AddExtension<CMeshRendererExtension>();

	meshRenderer->SetModel(sphereMesh);
	meshRenderer->SetMaterial(sphereMaterial);

	bool inGame = false;

	while (g_subSystem->Update())
	{
		root->Update();

		if (!inGame && g_subSystem->GetInputDevice()->IsMouseButtonDown(eMOUSEBUTTON_LEFT))
		{
			inGame = true;
			g_subSystem->GetInputDevice()->SetMouseCurserLocked(true);
		}

		if (inGame && (g_subSystem->GetInputDevice()->IsKeyDown(eKEY_ESCAPE) || !g_subSystem->GetDisplay()->HasFocus()))
		{
			inGame = false;
			g_subSystem->GetInputDevice()->SetMouseCurserLocked(false);
		}

		if (inGame)
		{
			SVector2_i32 deltaPos = g_subSystem->GetInputDevice()->GetMouseMotion();
			
			camera->GetTransform()->Rotate(SQuaternion::CreateAxisRotation({ 0, 1, 0 }, DEG2RAD(-deltaPos.x * 0.1f)));
			camera->GetTransform()->Rotate(SQuaternion::CreateAxisRotation(camera->GetTransform()->GetRotation().GetRight(), DEG2RAD(-deltaPos.y * 0.1f)));
		}

		g_subSystem->GetRenderDevice()->BeginFrame();
		root->Render();
		g_subSystem->GetRenderDevice()->EndFrame();

		g_subSystem->GetRenderContext()->SwapBuffers();
	}

	delete skyboxClearMethod;
	delete skybox;
	delete root;
	delete camera;
	delete sphereMaterial;
	g_subSystem->GetRenderDevice()->ReleaseVertexArray(sphereMesh);
	g_subSystem->GetRenderDevice()->ReleaseTexture(cubeMap);
	g_subSystem->GetRenderDevice()->ReleaseTexture(diffuseTexture);
	g_subSystem->GetRenderDevice()->ReleaseShaderProgram(shader);

	g_subSystem->Release();
	delete g_subSystem;
    
    return 0;
}