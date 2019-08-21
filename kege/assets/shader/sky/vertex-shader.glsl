// SKY BOX  VERTEX SHADER
#version 400 core
layout (location = 0) in vec3 vp;
layout (location = 1) in vec2 vt;

layout (std140, column_major) uniform CAMERA
{
    mat4  proj;
    mat4  view;
}Camera;

out VS_OUT
{
    vec3 position;
    vec2 texcoord;
} vs_out;

uniform mat4 ModelMatrix;

void main ()
{
    vec4 position = ModelMatrix * vec4(vp, 1.0f);
    vs_out.position = position.xyz;
    vs_out.texcoord = vt*10;
    
    mat4 view = Camera.view;
    view[3][0] = 0.0;
    view[3][1] = 0.0;
    view[3][2] = 0.0;
    
    gl_Position = Camera.proj * view * position;
}


