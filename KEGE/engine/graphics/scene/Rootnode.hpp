/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Rootnode.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef Rootnode_hpp
#define Rootnode_hpp
#include "../../graphics/scene/Object.hpp"
namespace kege{namespace gfx{
    class Scene;
    class NodeEntity;
    class RenderingSystem;
    
    class Rootnode : public kege::Object
    {
    public:
        
        /*
         send message to game components to handle
         */
        virtual void HandleMessage(const kege::Message& message);
        
        /*
         render this object components
         */
        virtual void Submit( gfx::RenderingSystem* renderer );
        
        /*
         initialize this object components
         */
        virtual short Init(kege::Scene* scene);
        
        /*
         update this objects components
         */
        virtual void Update(double delta);
        
        /*
         clear entities
         */
        virtual void UnInit();
        
        /*
         release scene object data */
        virtual void Destroy();
        
        /*
         get child from this NodeEntity
         */
        const Gameobject* FindChild(const ds::string& name)const;
        
        /*
         get child from this NodeEntity
         */
        Gameobject* FindChild(const ds::string& name);
        
        /*
         get child from this NodeEntity
         */
        const Gameobject* GetChild(const ds::string& name)const;
        
        /*
         get child from this NodeEntity
         */
        Gameobject* GetChild(const ds::string& name);
        
        /*
         remove child from this NodeEntity
         */
        Gameobject* RemChild(const ds::string& name);
        
        /*
         add child to this NodeEntity
         */
        Gameobject* AddChild(Gameobject* object);
        
        /*
         add child to this NodeEntity
         */
        void AddChildren(Gameobjects& object);
        
        /*
         remove child from this NodeEntity
         */
        bool RemChild(Gameobject* object);
        
        /*
         get the list of childrens
         */
        const Gameobjects& GetChildren()const;
        Gameobjects& GetChildren();
        
        /*
         return true of node has children false otherwise
         */
        bool IsEmpty()const;
        
        virtual ~ Rootnode();
        Rootnode();
        
    protected:
        
        Gameobjects _objects;
    };
}}
#endif /* Rootnode_hpp */
