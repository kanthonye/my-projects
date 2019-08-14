//
//  SceneLight.hpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/15/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef SceneLight_hpp
#define SceneLight_hpp
#include "dynarry.hpp"
#include "Light.hpp"
#include "Gameobject.hpp"
#include "octree.hpp"
namespace kege {namespace gfx{
    
    class SceneLight : public gfx::Gameobject
    {
    public:
        
        void GetRenderables( kege::SceneFrame& frame );
        void Update(double delta_ms);
        //void SaveComponent(kege::XML& xml);
        
        const gfx::Light* GetLight()const;
        gfx::Light* GetLight();
        
        SceneLight  // construct point light
        (   const ds::string& name
         ,  const cg::point3& position
         ,  const cg::point3 &color
         ,  float intensity
         ,  float radius );
        
        SceneLight(const ds::string& name, const gfx::Light& light, const gfx::Transform& transform);
        SceneLight(const ds::string& name);
        SceneLight();
        
    private:
        
        gfx::Light light;
    };
    
    typedef ds::dlist<SceneLight*> SceneLights;
    
    class LightPartition
    {
    private:
        typedef ds::octree<const gfx::Light*, ds::dlist<const gfx::Light*>> LightOctree;
        
        static void AddLight(ds::dlist< const gfx::Light* >& list, const gfx::Light* light)
        {
            list.push_back( light );
        }
    public:
        
        void ProcessLights(gfx::SceneLights& lights)
        {
            for (gfx::SceneLights::iterator l=lights.begin(); l!=nullptr; l++)
            {
                partition.put(l->GetWorld().translation, l->GetRadius(), l->GetLight(), AddLight);
            }
        }
        
        void AddLight(gfx::SceneLight* light)
        {
            partition.put(light->GetWorld().translation, light->GetRadius(), light->GetLight(), AddLight);
        }
        
        ds::dynarry< gfx::Light::Data >& GetLights(const cg::vec3& min, const cg::vec3& max)
        {
            lights.setcount(0);
            std::vector<LightOctree*> items;
            partition.get(items, min, max);
            for (std::vector<LightOctree*>::iterator i=items.begin(); i!=items.end(); i++)
            {
                LightOctree* octree = (*i);
                ds::dlist<const gfx::Light*>& items = octree->item();
                for (ds::dlist<const gfx::Light*>::iterator i=items.begin(); i!=nullptr; i++)
                {
                    lights.append( i.element()->data );
                }
            }
            return lights;
        }
        
        ds::dynarry< gfx::Light::Data >& GetLights(cg::vec3& pos)
        {
            lights.setcount(0);
            LightOctree* node = partition.get(pos);
            if (node != nullptr)
            {
                ds::dlist<const gfx::Light*>& items = node->item();
                for (ds::dlist<const gfx::Light*>::iterator i=items.begin(); i!=nullptr; i++)
                {
                    lights.append( i.element()->data );
                }
            }
            
            return lights;
        }
        
        void Set(float x,float y,float z,float size, short minsiz)
        {
            partition.set(x, y, z, size, minsiz);
        }
        
        void Clear()
        {
            partition.item().clear();
            partition.clear();
            lights.clear();
        }
    private:
        
        ds::dynarry< gfx::Light::Data > lights;
        LightOctree partition;
    };
    
    typedef ds::dynarry< gfx::Light::Data > ArrayLights;
}}
#endif /* SceneLight_hpp */
