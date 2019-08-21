// Fragment SpriteShader
#version 400
#define DEFERRED_RENDERING

layout (location = 0) out vec3 VP_OUT;
layout (location = 1) out vec3 VN_OUT;
layout (location = 2) out vec3 VC_OUT;
layout (location = 3) out vec3 VS_OUT;

struct MATERIAL
{
    vec3  ambient;
    vec3  diffuse;
    vec3  specular;
    vec3  emission;
    float shininess;
    float density;
    float alpha;
    
    sampler2D diffmap;
    sampler2D normmap;
    sampler2D dso;
};


layout (std140, column_major) uniform CAMERA
{
    mat4  proj;
    mat4  view;
}Camera;

layout (std140) uniform SKY
{
    vec4 color;
    vec4 colr_hemis; /* lower hemisphere horizon glow color. when the sun is close or at the horizon, this color appears */
}Sky;

layout (std140) uniform FOG
{
    vec4 color;
    vec4 info;
}Fog;

layout (std140) uniform SUN
{
    vec3  color;
    float glow_size;
    vec3  dir;
    float glow_intensity;
    vec3  glow_color;
    float ambience;
}Sun;

layout (std140) uniform GROUND
{
    vec4  color;
}Ground;

layout (std140) uniform LIGHTS
{
    LIGHT Lights[4];
};

in VS_OUT
{
    vec3  position;
    vec3  normal;
    vec2  uvcoord;
    vec3  viewdir;
    vec3  tangent;
    vec4  shadow;
    float visiblity;
} fs_in;


uniform MATERIAL Material;
uniform int LightCount;








// the signature
subroutine void MaterialMode();
subroutine uniform MaterialMode OUTPUT_FRAGMENT;

// option object with material that has no textures
subroutine (MaterialMode) void ColorMaterialMode()
{
    VC_OUT = Material.diffuse;
    VP_OUT = fs_in.position;
    VN_OUT = fs_in.normal;
    
    VS_OUT.x = Material.shininess;
    VS_OUT.y = Material.density;
}

// option object with material that has textures but no normalmap
subroutine (MaterialMode) void TextureMaterialMode()
{
    VC_OUT = texture(Material.diffmap, fs_in.texcoord).rgb;
    VP_OUT = fs_in.position;
    VN_OUT = fs_in.normal;
    
    VS_OUT.x = Material.shininess;
    VS_OUT.y = Material.density;
}

// option object with material that has normal map textures
subroutine (MaterialMode) void NormalmapMaterialMode()
{
    VC_OUT = texture(Material.diffmap, fs_in.texcoord).rgb;
    VN_OUT = texture(Material.normmap, fs_in.texcoord).rgb * 2.0 - 1.0;
    VN_OUT = normalize(fs_in.TBN * vn_out);
    VP_OUT = fs_in.position;
    
    VS_OUT.x = Material.shininess;
    VS_OUT.y = Material.density;
}

// option object that has no material
subroutine (MaterialMode) void NoMaterialMode()
{
    VP_OUT = fs_in.position;
    VN_OUT = fs_in.normal;
    VC_OUT = vec3(0.9, 0.0, 0.8);
    VS_OUT.x = 1.0;
    VS_OUT.y = 50.0;
}

void main()
{
    OUTPUT_FRAGMENT();
}


