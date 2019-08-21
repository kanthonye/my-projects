/*
 *  version 4.0 of OpenGL GLSL - vertex shader
 *  @author     Kenneth Esdaile
 *  @date       created on 11/17/16
 *  @copyright  Copyright © 2016 Kenneth Anthony Esdaile. All rights reserved.
 */
#version 400
out vec4 fragment_color;

in VS_OUT
{
    vec3  position;
    vec3  camdir;
    vec2  texcoord;
    float visibility;
    float distant;
} fs_in;

layout (std140) uniform SKY
{
    vec4 color;
    vec4 sea_color;
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

uniform sampler2D mapVertNorm;
uniform sampler2D mapVertTang;

uniform sampler2D mapColrDiff;
uniform sampler2D mapColrADS;

/*! for blending base on terrain slope
 @param slope is the slope of the terrain at a particular coordinate
 @param smin is the min slope
 @param smax is the max slope
 @return a value between 0.0 and 1.0
 */
float terrain_slopefunc(float slope, float smin, float smax)
{
    return clamp(((slope - smax) + smin) / (smax - smin), 0.0, 1.0);
}

float unitize(float val, float minval, float maxval)
{
    float dist = maxval - minval;
    return clamp((dist - (maxval - val)) / dist, 0.0, 1.0);
}

/*! for blending base on displacment map
 @param height is the displacement map height value
 @param minheight is the min displacement map height value.
 anthong below minheight should return 0
 @param divisor is used to smooth or hard the blend value between edges
 @return a value between 0.0 and 1.0
 */
float TerrainDispmix(float l, float r, float mindist)
{
    return min(1.0, max(0.0, l-r) / min(1.0, max(0.0125, mindist)));
}


void main()
{
    vec3 N = texture(mapVertNorm, fs_in.texcoord).xzy * 2.0 - 1.0;
//    vec3 T = texture(mapVertTang, fs_in.texcoord).xyz * 2.0 - 1.0;
//    T = normalize(T - dot(T, N) * N);
//    vec3 B = normalize(cross(N, T));
//    mat3 TBN = mat3(T, B, N);
    
    
    vec3 fog_colr = fog.color.rgb;
    vec3 terrain_color = vec3(1.0);
//    const vec3 UP = vec3(0.0, 1.0, 0.0);
//    float slope = min(max(dot(N, UP), 0.0), 1.0);
//    slope = pow(slope, 5);
//
//    vec4 color = texture(TerrainSplatmap, fs_in.texcoord);
//    float dirt_visibility  = color.r;
//    float grass_visibility = color.g;
//    float road_visibility  = color.b;
//
//    vec3 dsa;
//    float blend_mix;
//    vec3 terrain_color;
//    vec3 terrain_normal;
//
//    vec2 rock_texcoord = fs_in.texcoord * matl_rock.textrscale;
//    vec3 rock_norm = texture(matl_rock.norm, rock_texcoord).rgb * 2.0 - 1.0;
//    vec3 rock_colr = texture(matl_rock.colr, rock_texcoord).rgb;
//    dsa  = texture(matl_rock.dsa, rock_texcoord).rgb;
//    float rock_disp = dsa.r;
//    float rock_spec = dsa.g;
//    float rock_ambi = dsa.b;
//
//    vec2 dirt_texcoord = fs_in.texcoord * matl_dirt.textrscale;
//    vec3 dirt_norm = texture(matl_dirt.norm, dirt_texcoord).rgb * 2.0 - 1.0;
//    vec3 dirt_colr = texture(matl_dirt.colr, dirt_texcoord).rgb;
//    dsa = texture(matl_dirt.dsa, dirt_texcoord).rgb;
//    float dirt_slope = unitize(slope, matl_dirt.minmaxslope.x, matl_dirt.minmaxslope.y);
//    float dirt_disp = dsa.r;
//    float dirt_spec = dsa.g;
//    float dirt_ambi = dsa.b;
//
//    vec2 grass_texcoord = fs_in.texcoord * matl_grass.textrscale;
//    vec3 grass_norm = texture(matl_grass.norm, grass_texcoord).rgb * 2.0 - 1.0;
//    vec3 grass_colr = texture(matl_grass.colr, grass_texcoord).rgb;
//    dsa  = texture(matl_grass.dsa, grass_texcoord).rgb;
//    float grass_slope =  unitize(slope, matl_grass.minmaxslope.x, matl_grass.minmaxslope.y);
//    float grass_disp = dsa.r;
//    float grass_spec = dsa.g;
//    float grass_ambi = dsa.b;
//
//    vec2 road_texcoord = fs_in.texcoord * matl_road.textrscale;
//    vec3 road_norm = texture(matl_road.norm, road_texcoord).rgb * 2.0 - 1.0;
//    vec3 road_colr = texture(matl_road.colr, road_texcoord).rgb;
//    dsa  = texture(matl_road.dsa, road_texcoord).rgb;
//    float road_slope =  1.0 - unitize(slope, 0.958, 1.0);
//    float road_disp = dsa.r;
//    float road_spec = dsa.g;
//    float road_ambi = dsa.b;
//
//    blend_mix = max(0.0, min(1.0, dirt_slope * (dirt_slope + dirt_visibility) - rock_disp));
//    blend_mix = 1.0 - clamp(pow(blend_mix, 1.0), 0.0, 1.0);
//    terrain_color  = mix(dirt_colr, rock_colr, blend_mix);
//    terrain_normal = mix(dirt_norm, rock_norm, blend_mix);
//
//    blend_mix = max(0.0, min(1.0, grass_slope * (grass_slope + grass_visibility) - blend_mix));
//    blend_mix = 1.0 - clamp(pow(blend_mix, 0.50), 0.0, 1.0);
//    terrain_color  = mix(grass_colr, terrain_color, blend_mix);
//    terrain_normal = mix(grass_norm, terrain_normal, blend_mix);
//
////    blend_mix = min(grass_slope + grass_visibility, 1.0) - blend_mix;
////    blend_mix = clamp(blend_mix, 0.0, 1.0);
////    blend_mix = 1.0 - pow(blend_mix, 2);
////    terrain_color  = mix(grass_colr, terrain_color, blend_mix);
////    terrain_normal = mix(grass_norm, terrain_normal, blend_mix);
//
////    blend_mix = (blend_mix + 0.25) - grass_slope * grass_visibility;
////    blend_mix = clamp(blend_mix / 0.25, 0.0, 1.0);
////    terrain_color  = mix(grass_colr, terrain_color, blend_mix);
////    terrain_normal = mix(grass_norm, terrain_normal, blend_mix);
////
////    blend_mix = (blend_mix + 0.125) - (road_disp * road_slope * road_visibility);
////    blend_mix = clamp(blend_mix / 0.125, 0.0, 1.0);
////    terrain_color  = mix(road_colr, terrain_color, blend_mix);
////    terrain_normal = mix(road_norm, terrain_normal, blend_mix);
//
//    vec3 bump_normal = normalize(TBN * terrain_normal);
//
//    terrain_color = terrain_color * max(dot(sun.dir.xyz, bump_normal), sun.ambience);
//    vec3 lighting = mix(fog.color.xyz, terrain_color, fs_in.visibility);
//
////    pow(sunAmount,8.0)
//    //vec3 lighting = applyFog(terrain_color, fs_in.distant, fs_in.camdir, sun.dir);
//
//
    
    vec3  ads   = texture(mapColrADS, fs_in.texcoord * 20).rgb;
    float shade = max(0.0, dot(sun.dir.xyz, N));
    
    float a = (shade + 1.0) * 0.5;
    vec3 ambi = vec3(1.0) * ads.x * a;
    
    vec3 diff = texture(mapColrDiff, fs_in.texcoord * 20).rgb * shade;
    
//    vec3 r = normalize( 2.0 * dot( sun.dir.xyz, N ) * N - sun.dir.xyz );
//    vec3 spec = pow(max(0.0, dot(fs_in.camdir, r)), 50) * vec3(1.0, 0, 0) * ads.x;
    
    fragment_color = vec4( mix(fog_colr, ambi + diff, fs_in.visibility), 1.0 );
}




