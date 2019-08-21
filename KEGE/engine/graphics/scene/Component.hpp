/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Component.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef Component_hpp
#define Component_hpp
#include "cgm.hpp"
#include "XML.hpp"
#include "Message.hpp"
#include "enumtypes.hpp"
#include "../../graphics/scene/Object.hpp"
namespace kege{
    class SceneFrame;
    class Scene;
}
namespace kege{namespace gfx{
    class RenderingSystem;
    class Entity;
    
    class Component : public kege::Object
    {
    public:
        
        enum Type
        {
            MODEL, LIGHT, ROTATION, PHYSICS, JUMP, INPUT, CONTROL, ROTATION_CONTROL, MOTION_CONTROL, JUMP_CONTROL, SKELETAL_ANIMATOR
        };
        
        /*
         render this objects child objects and EntityComponents
         */
        virtual void Submit( gfx::RenderingSystem* renderer ){}
        
        /*
         queue messages for this object to handle
         */
        virtual void HandleMessage( const kege::Message& message );
        
        /*
         initialize this object EntityComponents and child objects
         */
        virtual bool Init(kege::Scene* scene);
        
        /*
         update this object EntityComponents and child objects
         */
        virtual void Update(double delta_ms){}
        
        /*
         uninitialize this object EntityComponents and child objects
         */
        virtual void UnInit();
        
        /*
         prepare Component for deletion
         */
        virtual void Destroy();
        
        /*
         set the parent node of this node
         get the parent node of this node
         */
        virtual void SetParent(Entity* value) {_parent = value;}
        virtual const Entity* GetParent() const {return _parent;}
        virtual Entity* GetParent() {return _parent;}
        
        /*
         get const Component by name
         */
        const gfx::Component* GetComponent(cg::uint type)const;
        gfx::Component* GetComponent(cg::uint type);
        
        const cg::quat& GetLocalRotation()const;
        const cg::quat& GetWorldRotation()const;
        
        const cg::vec3& GetLocalPosition()const;
        const cg::vec3& GetWorldPosition()const;
        
        const cg::vec3& GetLocalScale()const;
        const cg::vec3& GetWorldScale()const;
        
        cg::mat44 GetWorldMatrix()const;
        cg::mat44 GetLocalMatrix()const;
        
        cg::quat& GetLocalRotation();
        cg::quat& GetWorldRotation();
        
        cg::vec3& GetLocalPosition();
        cg::vec3& GetWorldPosition();
        
        cg::vec3& GetLocalScale();
        cg::vec3& GetWorldScale();
        
        /*
         give access to scene pointer when object is const
         */
        const kege::Scene* GetScene()const;
        kege::Scene* GetScene();
        
        /*
         get the _active state of this module
         */
        bool IsActive() const {return _parent != nullptr;}
        
        /*
         set the name of this module
         */
        void SetName(const ds::string& val) {_name = val;}
        const ds::string& GetName() const {return _name;}
        
        /*
         set the type of this module
         */
        void SetType(cg::ushort val) {_type = val;}
        cg::ushort GetType() const {return _type;}
        
        /*
         return enabled state
         */
        bool IsInit() const {return _init;}
        
        virtual void Save(kege::XML& xml){}
        
        virtual ~ Component();
        
    protected:
        
        Component(cg::uint type, const ds::string& name)
        :   _parent(nullptr)
        ,   _type(type)
        ,   _name(name)
        ,   _init( false )
        {}
        
        Component(cg::uint type)
        :   _parent(nullptr)
        ,   _type(type)
        ,   _init( false )
        {}
        
    protected:
        
        gfx::Entity* _parent;
        ds::string _name;
        cg::ushort _type;
        bool _init;
    };
    
    typedef ds::dlist< gfx::Component* > EntityComponents;
    
}}
#endif /* Component_hpp */
