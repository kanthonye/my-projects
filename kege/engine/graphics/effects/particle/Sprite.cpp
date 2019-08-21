//
//  Sprite.cpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 2/16/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "Gameobject.hpp"
#include "Camera.hpp"
//#include "Sprite.hpp"
#include "Scene.hpp"
namespace kege{namespace gfx{
    
//    void Sprite::Render(kege::Scene& scene, const ds::array<gfx::Light*>& lights)
//    {
////        renderer->Draw(GetOwner()->GetWorld().translation, GetOwner()->GetRadius(),  GetOwner()->GetRadius(), colr, curr_frame, next_frame, animation.GetFrameTime());
//    }
//    void Sprite::Update(kege::Scene& scene, float dt)
//    {
////        cg::vec3 d = cg::abs3(scene.GetCamera()->GetWorld().translation - GetOwner()->GetWorld().translation);
////        distance = d.x + d.y + d.z;
//        
//        animation.Animate(dt);
//        if (texture != nullptr)
//        {
////            texture->CalcTileCoord(curr_frame, animation.GetCurrFrame());
////            texture->CalcTileCoord(next_frame, animation.GetNextFrame());
//        }
//    }
//    
//    Sprite::Sprite(/*gfx::TiledTexture2D* texture, */gfx::ParticleRenderer& renderer)
//    :   gfx::Component(kege::ENUM::_PARTICLE)
//    ,   renderer(&renderer)
//    ,   curr_frame(0.0)
//    ,   next_frame(0.0)
////    ,   texture(texture)
//    {
//        if (texture != nullptr) animation.SetTotalFrames(texture->GetCols() * texture->GetRows());
//        animation.SetAnimLength(40);
//        animation.SetRepeatable(false);
//    }
}}
