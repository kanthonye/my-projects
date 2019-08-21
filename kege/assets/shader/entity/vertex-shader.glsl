/*
 *  version 4.0 of OpenGL GLSL - vertex shader
 *  @author     Kenneth Esdaile
 *  @date       created on 11/17/16
 *  @copyright  Copyright © 2016 Kenneth Anthony Esdaile. All rights reserved.
 */
#version 400
 
layout (location = 0) in vec3 vp; // vp: vertex position
layout (location = 1) in vec2 vt; // vt: vertex texcoord
layout (location = 2) in vec3 vn; // vn: vertex normal
layout (location = 3) in vec3 vg; // vg: vertex tangent
layout (location = 4) in vec4 vw; // vn: vertex weights
layout (location = 5) in vec4 vj; // vn: vertex joints

layout (std140, column_major) uniform CAMERA
{
    mat4  proj;
    mat4  view;
}Camera;

layout (std140) uniform FOG
{
    vec4 color;
    vec4 info;
}Fog;

layout (std140) uniform SKELETON
{
    mat4 joint[126];
}skeleton;

out VS_OUT
{
    vec3  position;
    vec3  normal;
    vec2  uvcoord;
    vec3  viewdir;
    vec3  tangent;
    vec4  shadow;
    float visibility;
} vs_out;

uniform mat4 ShadowMatrix;
uniform mat4 ModelMatrix;

vec4  position;
vec4  eyepos;
vec4  normal;
float distant;


vec4 SkinVertex(vec4 a)
{
    vec4 v;
    v  = (skeleton.joint[int(vj.x)] * vw.x) * a;
    v += (skeleton.joint[int(vj.y)] * vw.y) * a;
    v += (skeleton.joint[int(vj.z)] * vw.z) * a;
    v += (skeleton.joint[int(vj.w)] * vw.w) * a;
    v.w = a.w;
    return v;
}

subroutine void ProcessVertex();
subroutine uniform ProcessVertex MeshMode;

// option 1
subroutine (ProcessVertex) void StaticMeshMode()
{
    position = ModelMatrix * vec4(vp, 1.0f);
    normal   = ModelMatrix * vec4(vn, 0.0f);
    eyepos   = Camera.view * position;
    distant  = length(eyepos.xyz);
}

// option 2
subroutine (ProcessVertex) void SkinMeshMode()
{
    position = ModelMatrix * SkinVertex(vec4(vp, 1.0f));
    normal   = ModelMatrix * SkinVertex(vec4(vn, 0.0f));
    eyepos   = Camera.view * position;
    distant  = length(eyepos.xyz);
}

void OutputVertex()
{
    vs_out.viewdir   = normalize(vec3(Camera.view[0][2], Camera.view[1][2], Camera.view[2][2]));
    vs_out.visibility = exp(-pow(distant * Fog.info.x, Fog.info.y) );
    vs_out.visibility = clamp(vs_out.visibility, 0.0f, 1.0f);
    vs_out.normal    = normalize(normal).xyz;
    vs_out.shadow    = ShadowMatrix * position;
    vs_out.position  = position.xyz;
    vs_out.uvcoord   = vt;
    gl_Position      = Camera.proj * eyepos;
}

void main()
{
    MeshMode();
    OutputVertex();
}

