// Fragment SpriteShader
#version 400
const vec3 material_specular = vec3(1.0, 1.0, 1.0);
const int NR_LIGHTS = 32;
layout (location = 0) out vec4 fragm_color;

struct LIGHT
{
    vec3  color;
    float intensity;
    vec3  position;
    float radius;
};

layout (std140) uniform LIGHTS
{
    Light lights[NR_LIGHTS];
};

in VS_OUT
{
    vec2  texcoord;
    vec3  viewdir;
} fs_in;

uniform int LightCount;

uniform sampler2D vp_txtr;
uniform sampler2D vn_txtr;
uniform sampler2D vc_txtr;
uniform sampler2D vm_txtr;

void main()
{
    vec3 vp = texture(vp_txtr, fs_in.texcoord).xyz; // vertex position
    vec3 vn = texture(vn_txtr, fs_in.texcoord).xyz; // vertex normal
    vec3 vc = texture(vc_txtr, fs_in.texcoord).xyz; // vertex color
    vec3 vm = texture(vm_txtr, fs_in.texcoord).xyz;
    
    float diffusor, diffuse, specular, light_radius, dist, attenuation;
    vec3  L,V,R, diff_color, spec_color, ambi_color, material_color = vec3(0.0);
    
    for (int i=0; i<LightCount; i++)
    {
        L = (Lights[i].position.xyz - vp);
        dist = length(L);
        L = L / dist;
        V = (fs_in.viewdir);
        R = normalize(2.0 * dot(L, vn) * vn - L);
        
        diffusor = max(0.0, dot(vn, L));
        diffuse  = (diffusor + 1.0) * 0.5;
        specular = pow(max(0.0, dot(V, R)), Material.density) * Material.shininess;
        
        light_radius = max(1.0, Lights[i].radius);
        attenuation  = clamp(light_radius - dist, 0.0, light_radius) / light_radius;
        
        material_color += material_diffuse  * Lights[i].color.rgb * diffuse;
        material_color += material_specular * Lights[i].color.rgb * specular;
        material_color += material_ambient  * Lights[i].color.rgb;
        material_color *= attenuation * Lights[i].intensity;
    }
    
    fragm_color = vec4(Material.emission + material_color, 1.0);
}

