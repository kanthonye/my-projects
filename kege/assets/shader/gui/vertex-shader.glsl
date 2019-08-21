// Gui Vertex Shader
#version 400
layout (location = 0) in vec4 posi;
layout (location = 1) in vec4 rect;
layout (location = 2) in vec4 colr;
layout (location = 3) in vec4 imgcoord;
layout (location = 4) in vec4 sdf; // signed distance fields
layout (location = 5) in vec4 sdf_colr;


uniform mat4 Projection;

out VS_OUT
{
    vec4  base_colr;
    vec4  outer_olr;
    vec4  sdf;
    vec2  texcoord;
    float isfont;
} vs_out;

void main()
{
    vec2 quad[] = vec2[4]
    (   vec2( 1.0, 0.0)
     ,  vec2( 0.0, 0.0)
     ,  vec2( 1.0,-1.0)
     ,  vec2( 0.0,-1.0) );
    
    vec2 vp = quad[gl_VertexID];
    vec2 vt = vec2(vp.x, vp.y + 1.0f);
    
    mat4 transform = mat4
    (  rect.x, 0.0   , 0.0   , 0.0
     , 0.0   , rect.y, 0.0   , 0.0
     , 0.0   , 0.0   , 1.0   , 0.0
     , posi.x,-posi.y, posi.z, 1.0  );
    
    vs_out.sdf = sdf;
    vs_out.outer_olr = colr;
    vs_out.base_colr = colr;
    vs_out.isfont = posi.w;
    vs_out.texcoord.x = imgcoord.x + imgcoord.z * vt.x;
    vs_out.texcoord.y = imgcoord.y + imgcoord.w * vt.y;
    gl_Position = Projection * transform * vec4(vp.x, vp.y, 0.0f, 1.0f);
}


