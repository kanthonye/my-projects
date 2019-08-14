/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/20/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       CubeSystem.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef CubeSystem_hpp
#define CubeSystem_hpp
#include "cgm.hpp"
#include "Scene.hpp"
#include "Message.hpp"
#include "EntityComponent.hpp"
namespace kege{namespace cmp{
    
    class CubePager : public gfx::EntityComponent
    {
    public:
        
        bool Init(kege::Scene* scene);
        void Update(double delta_ms);
        
        void Update(const cg::vec3& position);
        void PageOut(int x, int y, int z);
        void PageIn(int x, int y, int z);
        void SendPageMsg(int y);
        void SendPageMsg();
        
        CubePager(int radius, int tilesize, int scale);
        
    private:
        
        cg::var3i last;
        cg::var3i pmax;
        cg::var3i pmin;
        cg::var3i cmax;
        cg::var3i cmin;
        
        short tilesize;
        short radius;
        short scale;
        int count;
    };
    
    typedef kege::MsgT<cg::var3i> CubeMsg;
}}
#endif /* CubeSystem_hpp */
