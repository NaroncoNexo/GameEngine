#version 330

layout (location = 0) in vec4 a_Position;
layout (location = 1) in vec2 a_TexCoord;
layout (location = 2) in vec3 a_Normal;

out vec2 v_TexCoord;
out vec3 v_Normal;

uniform mat4 u_WorldMatrix;
uniform mat4 u_WorldViewProjectionMatrix;
uniform mat4 u_TextureMatrix;

void main()
{
    vec4 worldPos = u_WorldMatrix * a_Position;
    
    v_TexCoord = (u_TextureMatrix * vec4(a_TexCoord, 0, 1)).xy;
    v_Normal = normalize(worldPos.xyz);//(u_WorldMatrix * vec4(a_Normal, 0)).xyz;
    
    gl_Position = u_WorldViewProjectionMatrix * a_Position;
}