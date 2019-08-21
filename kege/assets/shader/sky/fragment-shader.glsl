//  SKY BOX FRAGMENT SHADER
#version 400 core

out vec4 Frag_Color;

layout (std140) uniform SKY
{
    vec4 color;
    vec4 sea_color; /* lower hemisphere horizon glow color. when the sun is close or at the horizon, this color appears */
}sky;

layout (std140) uniform FOG
{
    vec4 color;
    vec4 info;
}fog;

layout (std140) uniform SUN
{
    vec4 color;
    vec4 glow;
    vec4 dir;
}sun;

in VS_OUT
{
    vec3 position;
    vec2 texcoord;
} fs_in;

uniform sampler2D nightstars;

float SunDisk(float nds, float size, float intensity)
{
    size = max(100 - size, 0.0);
    size = clamp(size, 10, 100);
    nds  = max(nds, 0.0);
    nds  = pow(nds, size);
    nds  = pow(nds, size);
    return clamp(nds * intensity, 0.0, 1.0);
}

float SunGlow(float nds, float size, float intensity, float power)
{
    size = max(100 - size, 0.0);
    size = clamp(size, 10, 100);
    nds  = max(nds, 0.0);
    nds  = pow(nds, power);
    return clamp(nds * intensity, 0.0, 1.0);
}

void main()
{
    float blend;
    vec3 sky_color;
    vec3 final_color;
    vec3 sundir = normalize(sun.dir.rgb);
    vec3 normal = normalize(fs_in.position);
    float nds = max(dot(normal, sun.dir.rgb), 0.0);
    
    /* THE SKY AND STAR TEXTURE MIXTURE */
    vec3 stars = texture(nightstars, fs_in.texcoord).rgb;
    blend = clamp(pow(sun.dir.y + 0.7, 2), 0.0, 1.0);
    sky_color  = mix(stars, sky.color.rgb, blend);
    
    /* THE SKY & FOG MIXTURE */
    float sky_level = 1.0;//0.8;
    blend = min(sky_level, normal.y) / sky_level;
    blend = clamp(blend, 0.0, 1.0);
    sky_color = mix(fog.color.rgb, sky_color, blend);
    
    /* THE SEA & SKY COLOR MIXTURE */
    float b = abs(min(normal.y/0.25, 0.0));
    sky_color = mix(sky_color, sky.sea_color.rgb, clamp(b, 0.0, 1.0));
    
    final_color = sky_color;
    
    /* THE HEMISPHERE GLOW & COLOR COMPUTATION */
    float intensity = pow(1.0 - abs(normal.y), 12.0);
    float glow_cutoff = pow(nds, 2.0) * intensity; // this will make it so that the glow don't go all the way around the dome
    vec3 horizont_color = (sun.glow.rgb - final_color) * glow_cutoff;
    sky_color = final_color + horizont_color;
    
    final_color = sky_color;
    
    /* THE SUN-GLOW & SKY MIXTURE */
    float sun_glow = SunGlow(nds, 60, 0.9, 20);
    vec3 glowcolor = (sun.glow.rgb - final_color) * sun_glow;
    final_color = final_color + glowcolor;

    /* THE SUN & SKY MIXTURE */
    float sun_disk = SunDisk(nds, sun.color.a, 30);
    vec3 suncolor = (sun.color.rgb - final_color) * sun_disk;
    final_color = final_color + suncolor;

    /* SEA LEVEL - clip the parts of the sun that is under sea level */
    float edge_soften = 0.00125;
    float sea_level_cutoff = 0.0;
    blend = max(sea_level_cutoff, normal.y) / edge_soften;
    blend = clamp(blend, 0.0, 1.0);
    final_color = mix(sky_color, final_color, blend);
    
    
    Frag_Color = vec4(final_color, 1.0);
}

