/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/25/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       SubSystem.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef SubSystem_hpp
#define SubSystem_hpp
#include "System.hpp"
namespace kege{
    class Scene;
    
    class SubSystem : public kege::System
    {
    public:
        
        virtual void Update(double time_delta) = 0;
        virtual void Render() {}
        
        kege::Scene* GetScene() {return _scene;}
        virtual ~ SubSystem(){}
        
    protected:
        
        SubSystem(const ds::string& systyp)
        :   kege::System( systyp )
        ,   _scene( nullptr )
        {}
        
    private:
        
        kege::Scene* _scene;
        friend Scene;
        friend kege::Scene;
    };
}
#endif /* SubSystem_hpp */
