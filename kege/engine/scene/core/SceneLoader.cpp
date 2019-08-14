//
//  SceneLoader.cpp
//  KEGE-Proj1
//
//  Created by Kenneth A Esdaile on 2/18/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "Mesh.hpp"
#include "../../scene/core/Scene.hpp"
#include "../../scene/core/SceneLoader.hpp"
namespace kege{namespace gfx{
    
//    void SetVector(cg::vec4& position, char* str, int n)
//    {
//        int i = 0;
//        for (const char* tok = kege::str_tok(str, " "); tok!=nullptr; tok = kege::str_tok(nullptr, " "))
//        {
//            if (i < n) position.data[i++] = atof(tok);
//            else break;
//        }
//    }
//    
//    void AttachMeshComponent(kege::Scene* scene, kege::XML& pxml, gfx::Gameobject* obj)
//    {
////        kege::XML::attrib* a;
//        for (kege::XML::list::iterator n=pxml.Elements().begin(); n!=nullptr; n++)
//        {
////            if (n->GetName() == "box")
////            {
////                float w,h,d;
////                a = n->GetAttr("width");
////                if (a == nullptr) continue;
////                w = a->ToFloat();
////                a = n->GetAttr("height");
////                if (a == nullptr) continue;
////                h = a->ToFloat();
////                a = n->GetAttr("depth");
////                if (a == nullptr) continue;
////                d = a->ToFloat();
////                
////                gfx::Mesh* mesh = new gfx::Mesh;
////                gfx::GenPolyMeshBox(*mesh, w, h, d);
////                ((gfx::Entity*)obj)->SetMesh(mesh);
////                
////                scene->GetResourceManager().GetResource<gfx::Mesh>()->Add(" ", mesh);
////            }
////            else if (n->GetName() == "cone")
////            {
////                float min_h,max_h,radius;
////                int cols;
////                a = n->GetAttr("radius");
////                if (a == nullptr) continue;
////                radius = a->ToFloat();
////                a = n->GetAttr("min_height");
////                if (a == nullptr) continue;
////                min_h = a->ToFloat();
////                a = n->GetAttr("max_height");
////                if (a == nullptr) continue;
////                max_h = a->ToFloat();
////                a = n->GetAttr("columns");
////                if (a == nullptr) continue;
////                cols = a->ToFloat();
////                
////                gfx::Mesh* mesh = new gfx::Mesh;
////                gfx::GenPolyMeshCone(*mesh, radius, min_h, max_h, cols);
////                ((gfx::Entity*)obj)->SetMesh(mesh);
////            }
////            else if (n->GetName() == "cylinder")
////            {
////                float r,h,c;
////                a = n->GetAttr("radius");
////                if (a == nullptr) continue;
////                r = a->ToFloat();
////                a = n->GetAttr("height");
////                if (a == nullptr) continue;
////                h = a->ToFloat();
////                a = n->GetAttr("columns");
////                if (a == nullptr) continue;
////                c = a->ToFloat();
////            }
////            else if (n->GetName() == "ellipsoid")
////            {
////                float x_radius;
////                float y_radius;
////                int cols = 16;
////                int rows = 8;
////                
////                a = n->GetAttr("x_radius");
////                if (a == nullptr) continue;
////                x_radius = a->ToFloat();
////                
////                a = n->GetAttr("y_radius");
////                if (a == nullptr) continue;
////                y_radius = a->ToFloat();
////                
////                gfx::Mesh* mesh = new gfx::Mesh;
////                gfx::GenPolyMeshEllipsoid(*mesh, x_radius, y_radius, cols, rows);
////                ((gfx::Entity*)obj)->SetMesh(mesh);
////            }
////            else if (n->GetName() == "plane")
////            {
////                float height;
////                float width;
////                float depth;
////                
////                a = n->GetAttr("width");
////                if (a == nullptr) continue;
////                width = a->ToFloat();
////                
////                a = n->GetAttr("y_radius");
////                if (a == nullptr) continue;
////                height = a->ToFloat();
////                
////                a = n->GetAttr("depth");
////                if (a == nullptr) continue;
////                depth = a->ToFloat();
////                
////                height = cg::max(height, depth);
////                width  = cg::max(width, depth);
////                
////                gfx::Mesh* mesh = new gfx::Mesh;
////                gfx::GenPolyMeshPlane(*mesh, width, height);
////                ((gfx::Entity*)obj)->SetMesh(mesh);
////            }
////            else if (n->GetName() == "geometry")
////            {
////                //kege::XML* geometry = elem->AddChild(new kege::XML("geometry"));
////            }
//        }
//    }
//    
//    bool GetFloatValue(float& value, kege::XML& pxml, const ds::string& name)
//    {
//        kege::XML* n = nullptr;
//        kege::XML::attrib* a = nullptr;
//        n = pxml.GetChild(name);
//        if (n == nullptr) return 0.0 ;
//        a = n->GetAttr("value");
//        if (a == nullptr) return 0.0;
//        value = a->ToFloat();
//        return true;
//    }
//    
//    void AttachCameraComponent(kege::XML& pxml, gfx::Gameobject* obj)
//    {
////        if (obj->GetType() == kege::ENUM::_SCENE_CAMERA)
////        {
////            gfx::Camera* cam = (gfx::Camera*)obj;
////            float value;
////
////            if ( !GetFloatValue(value, pxml, "fov") ) return;
////            cam->SetFieldOfView(value);
////
////            if ( !GetFloatValue(value, pxml, "zfar") ) return;
////            cam->SetFarView(value);
////
////            if ( !GetFloatValue(value, pxml, "znear") ) return;
////            cam->SetNearView(value);
////
////            if ( !GetFloatValue(value, pxml, "aspect_ratio") ) return;
////            cam->SetAspectRatio(value);
////        }
//    }
//    void AttachLightComponent(kege::XML& pxml, gfx::Gameobject* obj)
//    {
////        if (obj->GetType() == kege::ENUM::_SCENE_LIGHT)
////        {
////            gfx::SceneLight* light = (gfx::SceneLight*)obj;
////            float value;
////            
////            if ( !GetFloatValue(value, pxml, "intensity") ) return;
////            light->GetLight()->SetIntensity(value);
////            
////            if ( !GetFloatValue(value, pxml, "radius") ) return;
////            light->GetLight()->SetRadius(value);
////            light->SetRadius(value);
////            
////            cg::vec4 colr;
////            kege::XML* c = pxml.GetChild("color");
////            if (c == nullptr) return;
////            SetVector(colr, c->GetText().getdata(), 3);
////            light->GetLight()->SetColor(colr.xyz);
////        }
//    }
//    void AttachColliderComponent(kege::XML& pxml, gfx::Gameobject* obj)
//    {}
//    
//    void AttachPhysicsComponent(kege::XML& pxml, gfx::Gameobject* obj)
//    {}
//    
//    void AttachComponents(kege::Scene* scene, kege::XML& pxml, gfx::Gameobject* obj)
//    {
//        for (kege::XML::list::iterator n=pxml.Elements().begin(); n!=nullptr; n++)
//        {
//            if (n->GetName() == "mesh")
//            {
//                AttachMeshComponent(scene, *n.element(), obj);
//            }
//            else if (n->GetName() == "camera")
//            {
//                AttachCameraComponent(*n.element(), obj);
//            }
//            else if (n->GetName() == "light")
//            {
//                AttachLightComponent(*n.element(), obj);
//            }
//            else if (n->GetName() == "collider")
//            {
//                AttachColliderComponent(*n.element(), obj);
//            }
//            else if (n->GetName() == "physics")
//            {
//                AttachPhysicsComponent(*n.element(), obj);
//            }
//        }
//    }
//    
////    gfx::Transf LoadTransform(kege::XML& pxml)
////    {
////        gfx::Transf transf;
////        for (kege::XML::list::iterator n=pxml.Elements().begin(); n!=nullptr; n++)
////        {
////            if (n->GetName() == "translate")
////            {
////                
////            }
////            else if (n->GetName() == "translate")
////            {
////                
////            }
////            else if (n->GetName() == "translate")
////            {
////                
////            }
////        }
////    }
//    
//    gfx::Gameobject* LoadSceneObject(kege::Scene* scene, kege::XML& pxml)
//    {
//        kege::XML* transform = pxml.GetChild("transform");
//        kege::XML* t = transform->GetChild("translate");
//        kege::XML* r = transform->GetChild("rotation");
//        kege::XML* s = transform->GetChild("scale");
//        
//        cg::vec4 position, scale, rotation;
//        SetVector(rotation, r->GetText().getdata(), 4);
//        SetVector(position, t->GetText().getdata(), 3);
//        SetVector(scale   , s->GetText().getdata(), 3);
//        
//        gfx::NodeEntity* scenenode = nullptr;
//        
//        kege::XML::attrib* type = pxml.GetAttr("type");
//        //kege::XML* components = pxml.GetChild("components");;
//        if (type->value == "CAMERA")
//        {
////            gfx::Camera* obj = new gfx::Camera( pxml.GetAttr("name")->value );
////            obj->GetLocal().rotation = cg::quat(rotation.w, rotation.xyz);
////            obj->GetLocal().translation = position.xyz;
////            obj->GetLocal().scale = scale.xyz;
////            if (components != nullptr) AttachComponents(scene, *components, obj);
////            scenenode = obj;
//        }
//        else if (type->value == "LIGHT")
//        {
////            gfx::SceneLight* obj = new gfx::SceneLight( pxml.GetAttr("name")->value );
////            obj->GetLocal().rotation = cg::quat(rotation.w, rotation.xyz);
////            obj->GetLocal().translation = position.xyz;
////            obj->GetLocal().scale = scale.xyz;
////            if (components != nullptr) AttachComponents(scene, *components, obj);
////            scenenode = obj;
//        }
////        else if (type->value == "ENTITY")
////        {
////            gfx::Entity* obj = new gfx::Entity( pxml.GetAttr("name")->value );
////            obj->GetLocal().rotation = cg::quat(rotation.x, rotation.y, rotation.z, rotation.w);
////            obj->GetLocal().translation = position.xyz;
////            obj->GetLocal().scale = scale.xyz;
////            if (components != nullptr) AttachComponents(scene, *components, obj);
////            scenenode = obj;
////        }
//        else if (type->value == "GAMEOBJECT")
//        {
////            gfx::Gameobject* obj = new gfx::Gameobject( pxml.GetAttr("name")->value );
////            obj->GetLocal().rotation = cg::quat(rotation.w, rotation.xyz);
////            obj->GetLocal().translation = position.xyz;
////            obj->GetLocal().scale = scale.xyz;
////            if (components != nullptr) AttachComponents(scene, *components, obj);
////            scenenode = obj;
//        }
//        else if (type->value == "NODE")
//        {
//            scenenode = new gfx::NodeEntity( pxml.GetAttr("name")->value );
//            scenenode->GetLocal().translation = position.xyz;
//            scenenode->GetLocal().rotation = cg::quat(rotation.w, rotation.xyz);
//            scenenode->GetLocal().scale = scale.xyz;
//        }
//        for (kege::XML::list::iterator n=pxml.Elements().begin(); n!=nullptr; n++)
//        {
//            if (s->GetName() == "scenenode")
//            {
//                scenenode->AddChild( LoadSceneObject(scene, *n.element()) );
//            }
//        }
//        return scenenode;
//    }
//    
//    
//    
//    gfx::NodeEntity* LoaderXmlScene::Load(kege::ResourceManager* manager, const ds::string& filename)
//    {
//        kege::XML xml;
//        if (!xml.Load(filename))
//            return nullptr;
//        gfx::NodeEntity* sn = nullptr;
//        for (kege::XML::list::iterator n=xml.Elements().begin(); n!=nullptr; n++)
//        {
//            //sn = LoadSceneObject( *n.element() );
//            //resource->Add(sn->GetName(), sn);
//        }
//        return sn;
//    }
//    
//    bool LoaderXmlScene::Load(kege::Scene* scene, const ds::string& filename)
//    {
//        kege::XML xml;
//        if (!xml.Load(filename))
//            return false;
//        
//        kege::XML* scn = xml.GetChild("scene");
//        if (!scn) return false;
//        
//        kege::XML::attrib* a = scn->GetAttr("name");
//        if (!a) return false;
//        
//        scene->SetName(a->value);
//        //gfx::NodeEntity* sn = nullptr;
//        for (kege::XML::list::iterator n=scn->Elements().begin(); n!=nullptr; n++)
//        {
//            //sn = LoadSceneObject(scene, *n.element() );
//            //scene->Add(sn->GetName(), sn);
//        }
//        return true;
//    }
    
}}
