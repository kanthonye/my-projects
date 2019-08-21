#version 400
out vec4 frag_color;
uniform sampler2D theme_texr;
uniform sampler2D font_texr;

in VS_OUT
{
    vec4  base_colr;
    vec4  outer_olr;
    vec4  sdf;
    vec2  texcoord;
    float isfont;
} fs_in;

uniform vec4 SineDistOffset;
uniform vec4 SineDistColor;
uniform vec2 SineDistShadow;

void main()
{
    vec4 color = fs_in.base_colr;
    vec3 colr[2];
    float sdf_width[2];
    float sdf_edge[2];
    float alpha[3];
    sdf_width[0] = 0.15;
    sdf_width[1] = 0.25;
    sdf_edge[0]  = 0.05;
    sdf_edge[1]  = 0.05;

    
    float dist = texture(font_texr, fs_in.texcoord).r;
    
    alpha[0] = 1.0 - smoothstep(sdf_width[0] - sdf_edge[0], sdf_width[0] + sdf_edge[0], 1.0 - dist);
    alpha[1] = 1.0 - smoothstep(sdf_width[1] - sdf_edge[1], sdf_width[1] + sdf_edge[1], 1.0 - dist);
    alpha[2] = alpha[0] + (1.0 - alpha[0]) * alpha[1];
    colr[0]  = mix(vec3(1,0,1), color.rgb, alpha[0] / alpha[2]);
    vec4 font = vec4(colr[0], alpha[2]) * fs_in.isfont;
    
    //vec4 txtr_colr = texture(theme_texr, fs_in.texcoord) * fs_in.base_colr.rgba;
    vec4 button = color * (1.0 - fs_in.isfont);
    
    frag_color = button + font;
}
