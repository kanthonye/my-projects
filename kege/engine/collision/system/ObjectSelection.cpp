/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 6/8/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       ObjectSelection.cpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#include "Singleton.hpp"
#include "Window.hpp"
#include "Camera.hpp"
#include "GameEngine.hpp"
#include "Scene.hpp"
#include "DebugRenderer.hpp"
#include "Scene.hpp"
#include "CollisionSystem.hpp"
#include "ObjectSelection.hpp"

#define NUMDIM  3
#define RIGHT   0
#define LEFT    1
#define MIDDLE  2
namespace kege{namespace cg{
    
//    void ObjectSelection::Input::OnScrollWheelMove(const kege::Cursor& cursor)
//    {
//        zoom = cursor.y;
//    }
//    void ObjectSelection::Input::OnMouseCursorMove(const kege::Cursor& cursor)
//    {
//        pointer.x = cursor.GetX();
//        pointer.y = cursor.GetY();
//    }
//    void ObjectSelection::Input::OnMouseButtonPress(const kege::Key& key)
//    {
//        if (key.key == BUTTON_LEFT && key.action)
//        {
//            castray = true;
//        }
//        else if (key.action == 0)
//        {
//            castray = false;
//        }
//    }
//    
//    void ObjectSelection::Input::OnKeyboardPress(const kege::Key& key)
//    {
//        if (key.key == KEY_RIGHT_SHIFT)
//        {
//            move = key.action;
//        }
//    }
    
    void ObjectSelection::ResolveCollisions(double delta)
    {
        
    }
    void ObjectSelection::DetectCollisions(double delta)
    {
        hitlist.clear();
//        kege::CoreScenes* scene_manager = (kege::CoreScenes*) system->GetEngine()->GetSystem("CoreScenes");
//        if (scene_manager == nullptr) return;
//        
//        gfx::Camera* camera = scene_manager->GetScene()->GetCamera();
//        if (camera == nullptr) return;
//        
//        if (selection != nullptr && castray)
//        {
//            //selection->GetParent()->GetLocal().translation.x = ray_pos.x + ray_dir.x * dist;
//            //selection->GetParent()->GetLocal().translation.y = ray_pos.y + ray_dir.y * dist;
//            //selection->GetParent()->GetLocal().translation.z = ray_pos.z + ray_dir.z * dist;
//        }
    }
    
    void ObjectSelection::TestCollisions(double delta)
    {
    }
    
    void ObjectSelection::UnInit()
    {
        
    }
    short ObjectSelection::Init()
    {
        return true;
    }
//    void ObjectSelection::ProcessCollisions(kege::Scene& scene, cg::CollisionSystem& system)
//    {
//        gfx::Camera* camera = scene.GetCamera();
//        if (camera == nullptr)
//        {
//            hitlist.clear();
//            return;
//        }
//
//        if (selection != nullptr && castray)
//        {
//            selection->GetParent()->GetLocal().translation.x = ray_pos.x + ray_dir.x * dist;
//            selection->GetParent()->GetLocal().translation.y = ray_pos.y + ray_dir.y * dist;
//            selection->GetParent()->GetLocal().translation.z = ray_pos.z + ray_dir.z * dist;
//        }
//
//        if (input.castray)
//        {
//            int height = gfx::Window::GetCurrentWindow()->GetHeight();
//            int width  = gfx::Window::GetCurrentWindow()->GetWidth();
//            ray_dir = camera->MakeRay(width, height, input.pointer.x, input.pointer.y);
//            ray_pos = camera->GetWorld().translation;
//
//            if (!castray)
//            {
//                castray = true;
//                ds::dlist<cmp::CollisionComponent*>::iterator collider;
//                phx::Colliders& immovable = system.GetImmovableObjects();
//                phx::Colliders& movables = system.GetMovablesObjects();
//                for (collider=movables.begin(); collider!=nullptr; collider++)
//                {
//                    if (collider->OnCollisionRay(ray_pos, ray_dir))
//                    {
//                        hitlist.push_back(collider.element());
//                    }
//                }
//
//                for (collider=immovable.begin(); collider!=nullptr; collider++)
//                {
//                    if (collider->OnCollisionRay(ray_pos, ray_dir))
//                    {
//                        hitlist.push_back(collider.element());
//                    }
//                }
//
//                double min_z = 65535.0f;
//                double value = 0;
//                // sort hitlist from colsest to farthes, and select the colsect one
//                for (collider=hitlist.begin(); collider!=nullptr; collider++)
//                {
//                    value = cg::sq(camera->GetWorld().translation.z - collider.element()->GetParent()->GetWorld().translation.z);
//                    if (value < min_z)
//                    {
//                        min_z = value;
//                        selection = collider.element();
//                    }
//                }
//                if (selection != nullptr)
//                {
//                    dist = cg::distant(camera->GetWorld().translation, selection->GetParent()->GetWorld().translation);
//                    printf("selection %s\n", selection->GetParent()->GetName().c_str());
//                }
//                hitlist.clear();
//            }
//        }
//        else if (!input.castray && castray)
//        {
//            selection = nullptr;
//            castray = false;
//        }
//    }
    
    
    ObjectSelection::ObjectSelection()
    :   selection(nullptr)
    ,   dist(0.0)
    {
//        if (Singleton::Get<kege::InputContextManager>() == nullptr) {
//            return;
//        }
//        Singleton::Get<kege::SystemInputManager>()->AddInputContext(&input);
    }
}}
