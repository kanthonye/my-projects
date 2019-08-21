/*
 *  version 4.0 of OpenGL GLSL - vertex shader
 *  @author     Kenneth Esdaile
 *  @date       created on 11/17/16
 *  @copyright  Copyright © 2016 Kenneth Anthony Esdaile. All rights reserved.
 */
#version 400

layout (location = 0) in vec3  vp; // vp: vertex position

layout (std140, column_major) uniform CAMERA
{
    mat4  proj;
    mat4  view;
}camera;

layout (std140, column_major) uniform SHADOW
{
    mat4  proj;
    mat4  view;
}shadow;

layout (std140) uniform FOG
{
    vec4 color;
    vec4 info;
}fog;

out VS_OUT
{
    vec3  position;
    vec3  camdir;
    vec2  texcoord;
    float visibility;
    float distant;
} vs_out;

uniform vec2 TxtrOffset;
uniform float MAX_HEIGHT;
uniform float MIN_HEIGHT;
uniform float TILE_SIZE;
uniform float MAP_SIZE;
uniform float SCALE;

uniform mat4 ModelMatrix;

void main()
{
    double width = (1.0 / 32.0);
    vec2 texcoord = vec2(vp.x * width, vp.z * width);
    vs_out.texcoord = texcoord;

    vec4 position = ModelMatrix * vec4(vp, 1.0f);
    vs_out.position = position.xyz;
    position = camera.view * position;
    
    vs_out.distant    = length(position.xyz);
    vs_out.visibility = exp(-pow(vs_out.distant * fog.info.x, fog.info.y) );
    vs_out.visibility = clamp(vs_out.visibility, 0.0f, 1.0f);
    vs_out.camdir = vec3(camera.view[2][0], camera.view[2][1], camera.view[2][2]);
    gl_Position = camera.proj * position;
}






