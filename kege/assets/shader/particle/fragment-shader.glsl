/* Particle Instance Rendering Fragment Shader */
#version 400
out vec4 fs_out;

uniform sampler2D txtr;

layout (std140) uniform FOG
{
    vec4 color;
    vec4 info;
}Fog;

in VS_OUT
{
    vec2  tex0;
    vec2  tex1;
    vec4  colr;
    float tmix;
    float fogvis;
}  fs_in;

//vec4 GetColorRGBA()
//{
//    int texID = int(fs_in.texID);
//    vec4 frame1 = texture(txtrs[texID], fs_in.texframe.xy);
//    vec4 frame2 = texture(txtrs[texID], fs_in.texframe.zw);
//    return mix(frame1, frame2, fs_in.blend);
//}
//
//subroutine vec4 FragMode();
//subroutine uniform FragMode GetColorOutput;
//
//// option 1
//subroutine (FragMode) vec4 NoTxtrMode()
//{
//    return fs_in.color;
//}
//
//// option 2
//subroutine (FragMode) vec4 AnimTxtrMode()
//{
//    vec4 curr_frame = GetColorRGBA();
//    curr_frame.a = dot(curr_frame,curr_frame) * fs_in.color.a;
//    return curr_frame;
//}
//
//// option 3
//subroutine (FragMode) vec4 TxtrRGB_AlphaRGBSum()
//{
//    vec4 curr_frame = GetColorRGBA();
//    curr_frame.a = (curr_frame.x + curr_frame.y + curr_frame.z) * fs_in.color.a * 0.33333;
//    return curr_frame;
//}
//
//// option 3
//subroutine (FragMode) vec4 TxtrRGBA()
//{
//    return GetColorRGBA();
//}


void main()
{
    vec4 tex0 = texture(txtr, fs_in.tex0);
    vec4 tex1 = texture(txtr, fs_in.tex1);
    vec4 colr = mix(tex0, tex1, fs_in.tmix);
    
    colr.a = (colr.r * colr.r + colr.y * colr.y + colr.b * colr.b);
//    colr.a = (colr.a + colr.a) * 0.5;
    
    fs_out = colr;
}


