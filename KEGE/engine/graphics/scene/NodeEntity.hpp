/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 7/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       NodeEntity.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef NodeEntity_hpp
#define NodeEntity_hpp
#include "../../graphics/scene/Entity.hpp"
namespace kege{namespace gfx{
    
    class NodeEntity : public gfx::Entity
    {
    public:
        
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
        virtual bool Init(kege::Scene* scene);
        
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
         remove child from this NodeEntity
         */
        bool RemChild(Gameobject* object);
        
        /*
         get the list of childrens
         */
        const Gameobjects& GetChildren()const;
        Gameobjects& GetChildren();
        
        /*
         remove all child attached to this node
         */
        void RemoveChildren();
        
        /*
         return true of node has children false otherwise
         */
        bool IsEmpty()const;
        
        NodeEntity(Gameobject::Type type, const ds::string& name);
        NodeEntity(const ds::string& name);
        virtual ~ NodeEntity();
        NodeEntity();
        
    protected:
        
        Gameobjects objects;
    };
}}
#endif /* Scenenode_hpp */
