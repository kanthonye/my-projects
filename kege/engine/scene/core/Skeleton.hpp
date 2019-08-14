//
//  Skeleton.hpp
//  dev-kege
//
//  Created by Kenneth A Esdaile on 4/19/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef Skeleton_hpp
#define Skeleton_hpp
#include <map>
#include "queue.hpp"
#include "array.hpp"
#include "slist.hpp"
#include "../../scene/core/NodeEntity.hpp"
namespace kege{namespace gfx{
    
    
    class Joint
    {
    public:
        
        void AddChild(gfx::Joint* joint);
        Joint(const ds::string& name);
        
        ds::slist<gfx::Joint*> children;
        cg::mat44 world;
        cg::mat44 local;
        ds::string name;
        gfx::Joint* parent;
    };
    
    
    
    struct Bone
    {
        cg::mat44 inv_bind;
        gfx::Joint* joint;
    };
    typedef ds::array<gfx::Bone> Bones;
    typedef std::map<long, gfx::Joint*> JointMap;
    
    
    
    class Skeleton : public gfx::NodeEntity
    {
    public:
        
        void UpdateTransformation();
        
        gfx::Joint* GetJoint(const ds::string& name);
        JointMap& GetJointMap();
        
        const Bones& GetBones()const;
        Bones& GetBones();
        
        ~ Skeleton();
        Skeleton();
        
        gfx::Joint* joints;
    private:
        
        JointMap jointmap;
        Bones bones;
    };
    
    typedef kege::shared< gfx::Skeleton > SharedSkeleton;
}}
#endif /* Skeleton_hpp */
