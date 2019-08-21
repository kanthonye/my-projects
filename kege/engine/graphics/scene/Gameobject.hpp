/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/12/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Gameobject.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef Gameobject_hpp
#define Gameobject_hpp
#include "cgm.hpp"
#include "Message.hpp"
#include "dlist.hpp"
#include "../../graphics/scene/Object.hpp"
namespace kege{
    class Scene;
    class SceneFrame;
}
namespace kege{namespace gfx{
    class Component;
    class RenderingSystem;
    
    class Gameobject : public kege::Object
    {
    public:
        
        enum Type
        {
            GAMEOBJECT, ENTITY, NODEENTITY, CAMERA, LIGHT, TERRAIN, SKY
        };
        
        /*
         render this object components
         */
        virtual void Submit( gfx::RenderingSystem* renderer );
        
        /*
         send message to game components to handle
         */
        virtual void HandleMessage(const kege::Message& message);
        
        /*
         initialize this object components
         */
        virtual bool Init( kege::Scene* scene );
        
        /*
         update this objects components
         */
        virtual void Update(double delta);
        
        /*
         clear entities
         */
        virtual void UnInit();
        
        /*
         return enabled state
         */
        inline bool IsInit() const {return _init;}
        
        /*
         release scene object data */
        virtual void Destroy();
        
        
        const cg::quat& GetLocalRotation()const;
        const cg::quat& GetWorldRotation()const;
        
        const cg::vec3& GetLocalPosition()const;
        const cg::vec3& GetWorldPosition()const;
        
        const cg::vec3& GetLocalScale()const;
        const cg::vec3& GetWorldScale()const;
        
        const gfx::Transform& GetLocal()const;
        const gfx::Transform& GetWorld()const;
        
        cg::mat44 GetWorldMatrix()const;
        cg::mat44 GetLocalMatrix()const;
        
        cg::quat& GetLocalRotation();
        cg::quat& GetWorldRotation();
        
        cg::vec3& GetLocalPosition();
        cg::vec3& GetWorldPosition();
        
        cg::vec3& GetLocalScale();
        cg::vec3& GetWorldScale();
        
        gfx::Transform& GetLocal();
        gfx::Transform& GetWorld();
        
        void SetParent(Gameobject* parent);
        Gameobject* GetParent();
        
        const kege::Scene* GetScene()const;
        kege::Scene* GetScene();
        
        void SetName(const ds::string& val) {_name = val;}
        const ds::string& GetName()const {return _name;}
        
        Gameobject::Type GetType()const {return _type;}
        
        void SetRadius(float value) {_radius = value;}
        float GetRadius()const {return _radius;}
        
        void SetLoaded(bool val) {_loaded = val;}
        bool IsLoaded() const {return _loaded;}
        
        void SetActive(bool val) {_active = val;}
        bool IsActive() const {return _active;}
        
        void SetVisible(bool val) {_visible = val;}
        bool IsVisible() const {return _visible;}
        
        virtual ~ Gameobject();
        
    protected:
        
        Gameobject(Gameobject::Type type, const ds::string& name, gfx::Transform local);
        Gameobject(Gameobject::Type type, const ds::string& name);
        Gameobject(Gameobject::Type type);
        
    protected:
        
        gfx::Transform _world;
        gfx::Transform _local;
        ds::string _name;
        Gameobject* _parent;
        kege::Scene* _scene;
        
        Gameobject::Type _type;
        float _radius;
        bool _visible;
        bool _active;
        bool _loaded;
        bool _init;
    };
    
    typedef ds::dlist< gfx::Gameobject* > Gameobjects;
}}
#endif /* Gameobject_hpp */
