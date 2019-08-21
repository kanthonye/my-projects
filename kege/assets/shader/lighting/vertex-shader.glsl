/*
 *  OpenGL GLSL 4.0
 *  @author     Kenneth Esdaile
 *  @date       created on 11/17/16
 *  @copyright  Copyright © 2016 Kenneth Anthony Esdaile. All rights reserved.
 */
#version 400
layout (location = 0) in vec4 vp;

layout (std140, column_major) uniform CAMERA
{
    mat4  proj;
    mat4  view;
}Camera;

out VS_OUT
{
    vec2  texcoord;
    vec3  viewdir;
} vs_out;

void main()
{
    vs_out.texcoord = vp.zw;
    vs_out.viewdir  = normalize(vec3(Camera.view[0][2], Camera.view[1][2], Camera.view[2][2]));
    gl_Position = vec4(vp.xy, 0.0, 1.0);
}


