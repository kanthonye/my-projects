//
//  InfiniteTerrain.hpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 3/20/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef InfiniteTerrain_hpp
#define InfiniteTerrain_hpp
#include "queue.hpp"
#include "Texture2D.hpp"
#include "TerrainLoader.hpp"
#include "ConcurrentQueue.hpp"
namespace kege{namespace gfx{
    
    class InfiniteTerrain
    {
    public:
        
        virtual cg::vec2 GetVertexTexcoord(int x, int z) = 0;
        virtual cg::vec3 GetVertexPosition(int x, int z) = 0;
        virtual cg::vec3 GetVertexTangent(int x, int z) = 0;
        virtual cg::vec3 GetVertexNormal(int x, int z) = 0;
        virtual cg::vec3 GetVertexColor(int x, int z) = 0;
        virtual float GetVertexHeight(int x, int z) = 0;
        virtual gfx::SharedMesh GetTile(int x, int z) = 0;
        virtual ~ InfiniteTerrain(){}
        
        float  _normalmap_strength;
        double _frequency;
        double _steepness;
        double _terraces;
        float  _strength;
        float  _scale;
        int    _starting_octave;
        int    _octave;
        
        bool _running;
    };
}}
#endif /* InfiniteTerrain_hpp */
