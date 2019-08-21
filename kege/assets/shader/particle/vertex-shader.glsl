/* Particle Instance Rendering Vertex Shader */
#version 400 core
layout (location = 0) in vec4 posi;
layout (location = 1) in vec4 colr;
layout (location = 2) in vec4 img0;
layout (location = 3) in vec4 img1;
layout (location = 4) in vec4 rect;

layout (std140) uniform FOG
{
    vec4 color;
    vec4 info;
}Fog;

layout (std140, column_major) uniform CAMERA
{
    mat4  proj;
    mat4  view;
}Camera;

out VS_OUT
{
    vec2  tex0;
    vec2  tex1;
    vec4  colr;
    float tmix;
    float fogvis;
} vs_out;

void main()
{
    mat3 tpose = transpose(mat3(Camera.view));
    mat4 transform = mat4
    (  rect.x, 0.0   , 0.0   , 0.0
     , 0.0   , rect.y, 0.0   , 0.0
     , 0.0   , 0.0   , 1.0   , 0.0
     , posi.x, posi.y, posi.z, 1.0  );
    
    vec2 quad[] = vec2[4]
    (   vec2( 0.5, 0.5)
     ,  vec2(-0.5, 0.5)
     ,  vec2( 0.5,-0.5)
     ,  vec2(-0.5,-0.5) );
    
    vec2 vp = quad[gl_VertexID];
    vec2 vt = vec2(vp.x + 0.5, vp.y + 0.5);
    vec4 eyepos = Camera.view * transform * vec4(tpose * vec3(vp.x, vp.y, 0.0f), 1.0f);
    
    float distant = length(eyepos.xyz);
    vs_out.fogvis  = exp(-pow(distant * Fog.info.x, Fog.info.y) );
    vs_out.fogvis  = clamp(vs_out.fogvis, 0.0f, 1.0f);
    
    vs_out.tex0.x = img0.x + img0.z * vt.x;
    vs_out.tex0.y = img0.y + img0.w * vt.y;
    vs_out.tex1.x = img1.x + img1.z * vt.x;
    vs_out.tex1.y = img1.y + img1.w * vt.y;

//    vs_out.tex0.x = vt.x;
//    vs_out.tex0.y = vt.y;
//    vs_out.tex1.x = vt.x;
//    vs_out.tex1.y = vt.y;

    vs_out.colr = vec4(Camera.view[3][3], 1.0f, 1.0f, 1.0f);
    vs_out.tmix = posi.w;
    
    
//    gl_Position = transform * vec4(vp.x, vp.y, 0.0f, 1.0f);
    gl_Position = Camera.proj * eyepos;
}



