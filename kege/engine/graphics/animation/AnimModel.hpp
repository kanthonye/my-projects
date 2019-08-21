/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/13/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       AnimModel.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef AnimModel_hpp
#define AnimModel_hpp
#include "Model.hpp"
#include "Skeleton.hpp"
namespace kege{namespace gfx{
    
    class AnimModel : public gfx::Model
    {
    public:
        
        AnimModel( const ds::string& name, const shared::Mesh& me, const shared::Skeleton& sk );
        AnimModel( const shared::Mesh& me, const shared::Skeleton& sk );
        
        void BindMaterial( gfx::RenderingSystem* renderer );
        void Draw( gfx::RenderingSystem* renderer );
        
        void SetSkeleton(const gfx::Bones& bones)const;
        const shared::Skeleton& GetSkeleton() const;
        shared::Skeleton& GetSkeleton();
        
        AnimModel();
        
    private:
        
        shared::Skeleton _skeleton;
    };
    
    typedef mem::shared< gfx::Model > SharedModel;
}}
#endif /* AnimModel_hpp */
