// Directional Lighting Vertex Shader
#version 400 core

layout (location = 0) in vec3  vp; // vp: vertex position

layout (std140, column_major) uniform CAMERA
{
    mat4  proj;
    mat4  view;
}camera;

uniform sampler2D TerrainNormalmap;
uniform mat4      ModelMatrix;
out     vec4      normal;

void main()
{
    double width    = (1.0 / 32.0);
    vec2   texcoord = vec2(vp.x * width, vp.z * width);
    vec3   N        = texture(TerrainNormalmap, texcoord).xzy * 2.0 - 1.0;
    mat4   mvp      = camera.proj * camera.view * ModelMatrix;
    
    normal = ( mvp * vec4(N, 0.0f) ).xyz;
    gl_Position = mvp * vec4(vp, 1.0f);
}
