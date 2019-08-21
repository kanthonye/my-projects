/*
 *  version 4.0 of OpenGL GLSL - vertex shader
 *  @author     Kenneth Esdaile
 *  @date       created on 11/17/16
 *  @copyright  Copyright © 2016 Kenneth Anthony Esdaile. All rights reserved.
 */
#version 400
out vec4 fragment_color;

struct MATERIAL
{
    vec4  ambient;
    vec4  diffuse;
    vec4  specular;
    vec4  emission;
    
    float shininess;
    float density;
    float alpha;
    
    sampler2D ambimap;
    sampler2D diffmap;
    sampler2D specmap;
    sampler2D normmap;
};

struct LIGHT
{
    vec3  color;
    float intensity;
    vec3  position;
    float radius;
};

layout (std140) uniform LIGHTS
{
    LIGHT Lights[4];
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

in VS_OUT
{
    vec3  position;
    vec3  normal;
    vec2  uvcoord;
    vec3  viewdir;
    vec3  tangent;
    vec4  shadow;
    float visibility;
} fs_in;


uniform MATERIAL Material;
uniform int LightCount;

void main()
{
    vec3  material_color = Material.emission.rgb;
    float shininess = Material.shininess;
    float density = Material.density;
    float alpha = Material.alpha;
    
    float light_radius;
    float attenuation;
    float diffusor;
    float diffuse;
    float specular;
    float dist;
    vec3  L,V,R;
    vec3  diff_color;
    vec3  spec_color;
    vec3  ambi_color;
    
    for (int i=0; i<3; i++)
    {
        L = (Lights[i].position.xyz - fs_in.position);
        dist = length(L);
        L = L / dist;
        V = (fs_in.viewdir);
        R = normalize(2.0 * dot(L, fs_in.normal) * fs_in.normal - L);

        diffusor = max(0.0, dot(fs_in.normal, L));
        diffuse  = (diffusor + 1.0) * 0.5;
        specular = pow(max(0.0, dot(V, R)), density) * shininess;

        light_radius = max(1.0, Lights[i].radius);
        attenuation  = clamp(light_radius - dist, 0.0, light_radius) / light_radius;

        diff_color = Material.diffuse.rgb  * Lights[i].color.rgb * diffuse;
        spec_color = Material.specular.rgb * Lights[i].color.rgb * specular;
        ambi_color = Material.ambient.rgb  * Lights[i].color.rgb;

        material_color += (ambi_color + diff_color + spec_color) * attenuation * Lights[i].intensity;
    }
    
    material_color = mix(Fog.color.xyz, material_color, fs_in.visibility);
    fragment_color = vec4( material_color, 1.0 );
    //spec_color = (-diff_color * spec_color) + spec_color;
    //fragment_color = vec4(material_color, 1.0);
}




