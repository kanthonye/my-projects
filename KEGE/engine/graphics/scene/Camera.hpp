//
//  Camera.hpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/9/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#ifndef kege_Camera_hpp
#define kege_Camera_hpp
#include "../../graphics/scene/Entity.hpp"
namespace kege {namespace gfx{
    
    class Camera : public gfx::Entity
    {
    public:
        
        void  SetViewMatrix(const cg::point3& position, const cg::vec3& right, const cg::vec3& up, const cg::vec3& forward);
        void  SetViewMatrix(const cg::point3& position, const cg::quat& rotation);
        
        void  LookAt(const cg::point3& eye, const cg::point3& up, const cg::point3& target);
        
        cg::vec3 MakeRay(int width, int height, double mx, double my)const;
        
        void  SetProjection(const cg::mat44 & matrix);
        const cg::mat44 & GetProjection(void)const;
        
        void  SetViewMatrix(const cg::mat44 & matrix);
        const cg::mat44 & GetViewMatrix(void)const;
        
        void  SetFieldOfView(float value);
        float GetFieldOfView()const;
        
        void  SetAspectRatio(float value);
        float GetAspectRatio()const;
        
        void  SetNearView(float value);
        float GetNearView()const;
        
        void  SetFarView(float value);
        float GetFarView()const;
        
        void Update( double delta );
        
        /* constructor to create perspective camera */
        Camera(const ds::string& name, const cg::mat44& projection, const Transform& trandform);
        
        /* constructor to create perspective camera */
        Camera(const ds::string& name, float l, float r, float t, float b, float n, float f);
        
        /* constructor to create perspective camera */
        Camera(const ds::string& name, float aspect, float fov, float near, float far);
        
        /* constructor to create orthographic camera */
        Camera(float l, float r, float t, float b, float n, float f);
        
        /* constructor to create perspective camera */
        Camera(float aspect, float fov, float near, float far);
        
        Camera();
        
    private:
        
        cg::mat44 projection;
        cg::mat44 view;
        
        float aspect;
        float near;
        float far;
        float fov;
    };
}}
#endif /* SceneCamera_hpp */
