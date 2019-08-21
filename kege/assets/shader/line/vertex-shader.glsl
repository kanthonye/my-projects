// Gui Vertex Shader
#version 400 core
layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 vc;

layout (std140, column_major) uniform CAMERA
{
    mat4  proj;
    mat4  view;
}camera;

out vec3 color;

void main()
{
    color = vc;
    gl_Position = camera.proj * camera.view * vec4( vp, 1.0f );
}
