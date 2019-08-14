/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       RenderList.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef RenderList_hpp
#define RenderList_hpp
#include <unordered_map>
#include "GUI.hpp"
#include "Frustum.hpp"
#include "MeshComponent.hpp"
#include "SkinMeshComponent.hpp"
#include "../../scene/core/Camera.hpp"
#include "../../scene/core/NodeEntity.hpp"
#include "../../scene/core/SceneLight.hpp"
namespace kege{
    
    /* is a data structure used to collect visible objects that is inside the view frustum, which is then used by the rendering system to render the objects */
    class SceneFrame
    {
    public:
        
        std::unordered_map<int, gfx::RenderComponents> renderables;
        std::unordered_map<int, gfx::Gameobjects> gameobjects;
        gfx::LightPartition lights;
        gfx::Frustum frustum;
    };
}
#endif /* RenderList_hpp */
