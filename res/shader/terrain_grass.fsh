#version 330

in vec2 v_TexCoord;
in vec3 v_Normal;

out vec4 v_FragColor;

uniform sampler2D u_DiffuseTexture;

void main()
{
    vec4 diffuseColor = texture(u_DiffuseTexture, v_TexCoord);
    
    if (diffuseColor.a < 0.5)
        discard;
    
    float nDotL = max(0.0, dot(v_Normal, normalize(vec3(-0.3, 1.0, -0.5))));
    
    v_FragColor = vec4(diffuseColor.rgb * nDotL, 1.0);
}