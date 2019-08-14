//
//  Skeleton.cpp
//  dev-kege
//
//  Created by Kenneth A Esdaile on 4/19/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#include "../../scene/core/Skeleton.hpp"
namespace kege{namespace gfx{
    
    void Skeleton::UpdateTransformation()
    {
        ds::queue<gfx::Joint*> queue(joints);
        gfx::Joint* j;
        while (!queue.empty())
        {
            j = queue.pop();
            if (j != joints)
            {
                j->world = j->local * j->parent->world;
            }
            else
            {
                j->world = j->local;
            }
            for (ds::slist<gfx::Joint*>::iterator n=j->children.begin(); n!=nullptr; n++)
                queue.push(n.element());
        }
    }
    
    gfx::Joint* Skeleton::GetJoint(const ds::string& name)
    {
        JointMap::iterator m = jointmap.find(name.hash());
        if (m == jointmap.end()) return nullptr;
        return m->second;
    }
    const Bones& Skeleton::GetBones()const
    {
        return bones;
    }
    JointMap& Skeleton::GetJointMap()
    {
        return jointmap;
    }
    Bones& Skeleton::GetBones()
    {
        return bones;
    }
    
    Skeleton::~ Skeleton()
    {
        if (joints != nullptr)
        {
            delete joints;
            joints = nullptr;
        }
    }
    
    Skeleton::Skeleton()
    //:   gfx::NodeEntity(gfx::Gameobject::SKELETON)
    {}
    
    
    
    void Joint::AddChild(gfx::Joint* joint)
    {
        children.push_back(joint);
        joint->parent = this;
    }
    Joint::Joint(const ds::string& name)
    :   name(name)
    ,   parent(nullptr)
    {}
}}
