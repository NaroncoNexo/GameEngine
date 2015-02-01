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

struct test_vertex
{
    float x, y, z;
    float u, v;
    float nx, ny, nz;
};

ITexture *LoadTexture(IRenderDevice *renderDevice, const std::string &name)
{
    STextureData2D hg_tex_data = STextureData2D::LoadFromFile(CFileSystem::GetInstance()->GetPathToResourceFile(name));
    return renderDevice->CreateTexture2D(&hg_tex_data, eTEXTUREFILTER_NEAREST, eTEXTUREWRAP_REPEAT);
}

IShaderProgram *CreateShaderProgram(IRenderDevice *renderDevice, IShader *v, IShader *f)
{
    IShaderProgram *sp = renderDevice->CreateEmptyShaderProgram();
    sp->AddShader(v);
    sp->AddShader(f);
    sp->Build();
    return sp;
}

int main(int argc, char * argv[])
{
    ISubSystem *subSystem = new CSDL2SubSystem;
    IDisplay *display = subSystem->CreateDisplay(1280, 720, "Hello, World!");
    //ITimer *timer = subSystem->GetTimer();
    //IInputDevice *inputDevice = subSystem->GetInputDevice();
    IRenderContext *renderContext = subSystem->GetRenderContext();
    IRenderDevice *renderDevice = subSystem->GetRenderDevice();
    
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
    "uniform sampler2D u_DiffuseTexture;\n"
    "\n"
    "void main()\n"
    "{\n"
    "   vec4 diffuseColor = texture(u_DiffuseTexture, v_TextureCoordinate);\n"
    "   \n"
    "   if (diffuseColor.a < 0.5)\n"
    "       discard;\n"
    "   \n"
    "   float nDotL = max(0.0, dot(v_Normal, normalize(vec3(-0.3, 1.0, -0.5))));\n"
    "   \n"
    "   v_FragColor = vec4(diffuseColor.rgb * nDotL, 1.0);\n"
    "}"
    "";
    
    IShaderProgram *shader = renderDevice->CreateShaderProgram(vertexShaderSourceCode, fragmentShaderSourceCode);
    
    //IShader *terrainGrassVs = renderDevice->CreateShader(eSHADERTYPE_VERTEX, g_FileSys->GetContentsOfFile(g_FileSys->GetPathToResourceFile("res/shader/terrain_grass.vsh")));
    //IShader *terrainGrassFs = renderDevice->CreateShader(eSHADERTYPE_FRAGMENT, g_FileSys->GetContentsOfFile(g_FileSys->GetPathToResourceFile("res/shader/terrain_grass.fsh")));
    
    //IShaderProgram *terrainGrassPass1 = CreateShaderProgram(renderDevice, terrainGrassVs, terrainGrassFs);
    //IShaderProgram *terrainGrassPass2 = CreateShaderProgram(renderDevice, terrainGrassVs, terrainGrassFs);
    //terrainGrassPass2->SetInt(eSHADERPROPERTY_CULLFACE, eCULLFACE_FRONT);
    
    //renderDevice->ReleaseShader(terrainGrassFs);
    //renderDevice->ReleaseShader(terrainGrassVs);
    
    /*std::string vertexShaderSourceCode_skybox = ""
    "#version 330\n"
    "\n"
    "layout (location = 0) in vec4 a_Position;"
    ""
    "out vec3 v_Position;"
    ""
    "uniform mat4 u_RotationMatrix;"
    ""
    "void main()"
    "{"
    "   v_Position = a_Position.xyz;"
    "   "
    "   gl_Position = u_RotationMatrix * a_Position;"
    "}"
    "";
    
    std::string fragmentShaderSourceCode_skybox = ""
    "#version 330\n"
    "\n"
    "in vec3 v_Position;\n"
    "\n"
    "out vec4 v_FragColor;\n"
    "\n"
    "uniform samplerCube u_SkyboxTexture;\n"
    "\n"
    "void main()\n"
    "{\n"
    "   vec3 textureDirection = normalize(v_Position);\n"
    "\n"
    "   v_FragColor = vec4(texture(u_SkyboxTexture, textureDirection).rgb, 1.0);\n"
    "}\n"
    "";*/

    //IVertexArray *skyboxModel = renderDevice->CreateVertexArray(&CIndexedModel::LoadFromFile(CFileSystem::GetInstance()->GetPathToResourceFile("res/skybox.obj"))[0]);
    
    //IShaderProgram *skyboxShader = renderDevice->CreateShaderProgram(vertexShaderSourceCode_skybox, fragmentShaderSourceCode_skybox);
    //skyboxShader->SetBool(eSHADERPROPERTY_DEPTHMASKENABLED, false);

    STextureData2D diff_tex_data = STextureData2D::LoadFromFile(CFileSystem::GetInstance()->GetPathToResourceFile("res/tex/grass_diff.png"));
    ITexture *diffuseTexture = renderDevice->CreateTexture2D(&diff_tex_data, eTEXTUREFILTER_NEAREST, eTEXTUREWRAP_REPEAT);
    
    //STextureData2D hg_tex_data = STextureData2D::LoadFromFile(CFileSystem::GetInstance()->GetPathToResourceFile("res/tex/highgrass_diff.png"));
    //ITexture *highgrassTexture = renderDevice->CreateTexture2D(&hg_tex_data, eTEXTUREFILTER_NEAREST, eTEXTUREWRAP_REPEAT);
    
    STextureDataCubeMap cb_dat = STextureDataCubeMap::LoadFromFile(CFileSystem::GetInstance()->GetPathToResourceFile("res/oceanSkybox.png"), true);
    ITexture *cubeMap = renderDevice->CreateTextureCubeMap(&cb_dat, eTEXTUREFILTER_NEAREST);
    
    //ITexture *rock_diffTexture = LoadTexture(renderDevice, "res/tex/rock_diff.png");
    
    SVector3 cameraPosition = { 0, 0, -10 };
    
    CEntityRoot *root = new CEntityRoot(subSystem);
    
    /*CMaterial *skyboxMaterial = new CMaterial;
    skyboxMaterial->SetShader(skyboxShader);
    skyboxMaterial->SetTexture(eMATERIALTEXTURE_SKYBOX, cubeMap);

    CEntity *skybox = root->AddChild(g_SkyboxConfigurator, 2, skyboxModel, skyboxMaterial);*/
/*
    CEntity *meshEntity = srcEntity->AddChild();
    meshEntity->GetTransform()->GetTranslation() = { 0, 0, 0 };
    
    CMeshFilterExtension *meshFilter = meshEntity->AddExtension<CMeshFilterExtension>();
    CMeshRendererExtension *meshRenderer = meshEntity->AddExtension<CMeshRendererExtension>();
    
    meshFilter->SetModel(sphereModel);
    
    SMaterial mat;
    mat.shader = shader;
    mat.textureScale = { 8, 8 };
    mat.SetTexture(eMATERIALTEXTURE_DIFFUSE, diffuseTexture);
    mat.SetTexture(eMATERIALTEXTURE_SKYBOX, cubeMap);

    meshRenderer->GetMaterials()[0] = mat;
    */
/*
    CEntity *meshEntity2 = meshEntity->AddChild();
    meshEntity2->GetTransform()->GetTranslation() = { 2, 0, 0 };
    
    CMeshFilterExtension *meshFilter2 = meshEntity2->AddExtension<CMeshFilterExtension>();
    CMeshRendererExtension *meshRenderer2 = meshEntity2->AddExtension<CMeshRendererExtension>();
    
    meshFilter2->SetModel(sphereModel);
    
    meshRenderer2->GetMaterials()[0] = mat;*/

    /*CEntity *planet = root->AddChild();
    planet->GetTransform()->GetTranslation() = { 0, 0, 0 };
    
    CPlanetExtension *planetExtension = planet->AddExtension<CPlanetExtension>(1, 5.0f);
    
    CMaterial grassMaterial;
    grassMaterial.SetShader(shader);
    grassMaterial.SetTextureScale({ 8, 8 });
    grassMaterial.SetTexture(eMATERIALTEXTURE_DIFFUSE, diffuseTexture);
    
    planetExtension->AddLayer(grassMaterial);
    
    CMaterial highgrassMaterial;
    highgrassMaterial.AddShaderPass(terrainGrassPass1);
    highgrassMaterial.AddShaderPass(terrainGrassPass2);
    highgrassMaterial.SetTexture(eMATERIALTEXTURE_DIFFUSE, highgrassTexture);
    
    CIndexedModel highgrassModel = CIndexedModel::LoadFromFile(CFileSystem::GetInstance()->GetPathToResourceFile("res/model/highgrass.obj"))[0];
    CPlanetDetailMap *highgrassDetailMap = CPlanetDetailMap::CreateFromIndexedModel(highgrassModel, highgrassMaterial, planetExtension);
    
    planetExtension->AddDetailMap(highgrassDetailMap);*/
    
    /*SMaterial rockMaterial;
    rockMaterial.SetShader(shader);
    rockMaterial.SetTexture(eMATERIALTEXTURE_DIFFUSE, rock_diffTexture);
    
    CIndexedModel rockModel = CIndexedModel::LoadFromFile(CFileSystem::GetInstance()->GetPathToResourceFile("res/model/rock.obj"))[0];
    CPlanetDetailMap *rockDetailMap = CPlanetDetailMap::CreateFromIndexedModel(rockModel, rockMaterial, planetExtension);
    
    planetExtension->AddDetailMap(rockDetailMap);*/
    
    CCamera *camera = new CCamera(DEG2RAD(70.0f), 1280.0f / 720.0f, 0.01f, 100.0f);
    camera->GetTransform()->SetTranslation(cameraPosition);
    camera->GetTransform()->SetRotation(SQuaternion::CreateEuler(0, 0, 0));
    
    CSkybox *skybox = new CSkybox(subSystem->GetRenderDevice(), cubeMap);
    CSkyboxClearMethod *skyboxClearMethod = new CSkyboxClearMethod(skybox);
    
    camera->SetClearMethod(skyboxClearMethod);
    
    root->AddCamera(camera);
    
 /*   srand(SDL_GetTicks());
    test_vertex *vertexBuffer = (test_vertex *)sphereModel->MapBuffer(eBUFFERTYPE_VERTEXBUFFER);
    for(int i=0; i<1; ++i) {
        int r = (rand()%rawSphereModel.GetVertexCount());
        vertexBuffer[r].x*=2.0f;
        vertexBuffer[r].y*=2.0f;
        vertexBuffer[r].z*=2.0f;
    }
    sphereModel->UnmapBuffer(eBUFFERTYPE_VERTEXBUFFER);*/

    while (subSystem->Update())
    {
        //camera->GetTransform()->SetRotation(SQuaternion::CreateEuler(SDL_GetTicks() * 0.001f, 0, 0));
        
        root->Update();
        
        static SVector2_i32 lastMousePos = subSystem->GetInputDevice()->GetMousePosition();
        
        SVector2_i32 mousePos = subSystem->GetInputDevice()->GetMousePosition();
        SVector2_i32 deltaPos = mousePos - lastMousePos;
        lastMousePos = mousePos;
        
        auto v = camera->GetTransform()->GetRotation().GetRight();
        printf("%f, %f, %f\n", v.x, v.y, v.z);
        
        camera->GetTransform()->Rotate(SQuaternion::CreateAxisRotation({ 0, 1, 0 }, DEG2RAD(-deltaPos.x * 0.1f)));
        camera->GetTransform()->Rotate(SQuaternion::CreateAxisRotation(camera->GetTransform()->GetRotation().GetRight(), DEG2RAD(-deltaPos.y * 0.1f)));
        
        renderDevice->BeginFrame();
        
        root->Render();
        
        renderDevice->EndFrame();
        renderContext->SwapBuffers();
    }
    
    //CPlanetDetailMap::ReleasePlanetDetailMap(rockDetailMap);
    //CPlanetDetailMap::ReleasePlanetDetailMap(highgrassDetailMap);
    delete skyboxClearMethod;
    delete skybox;
    delete root;
    //delete skyboxMaterial;
    //renderDevice->ReleaseTexture(rock_diffTexture);
    renderDevice->ReleaseTexture(cubeMap);
    //renderDevice->ReleaseVertexArray(sphereModel);
    renderDevice->ReleaseTexture(diffuseTexture);
    //renderDevice->ReleaseShaderProgram(skyboxShader);
    //renderDevice->ReleaseVertexArray(skyboxModel);
    //renderDevice->ReleaseShaderProgram(terrainGrassPass2);
    //renderDevice->ReleaseShaderProgram(terrainGrassPass1);
    renderDevice->ReleaseShaderProgram(shader);
    
    subSystem->Release();
    delete subSystem;

    /*SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    
    SDL_Quit();*/
    
    return 0;
}