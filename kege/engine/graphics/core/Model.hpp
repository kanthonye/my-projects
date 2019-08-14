/*!
 *  @author     Kenneth A Esdaile
 *  @date       created on 8/3/19
 *  @copyright  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
 *  @file       Model.hpp
 *  @project    KEGE (Kenneth Esdaile Game Engine)
 */
#ifndef Model_hpp
#define Model_hpp
#include "Mesh.hpp"
#include "array.hpp"
#include "Material.hpp"
namespace kege{namespace gfx{
    
    class Model
    {
    public:
        
        Model(const gfx::SharedMesh& mesh, const gfx::SharedMaterial& material)
        :   material(material)
        ,   mesh(mesh)
        {}
        
        const gfx::SharedMaterial& GetMaterial() const;
        const gfx::SharedMesh& GetMesh() const;
        
        gfx::SharedMaterial& GetMaterial();
        gfx::SharedMesh& GetMesh();
        
        Model(){}
        
    private:
        
        gfx::SharedMaterial material;
        gfx::SharedMesh mesh;
    };
    
    typedef kege::shared< gfx::Model > SharedModel;
}}
#endif /* Model_hpp */
