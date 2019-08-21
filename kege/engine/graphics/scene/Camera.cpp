//
//  Camera.cpp
//  KEGE-Proj0
//
//  Created by Kenneth A Esdaile on 12/9/18.
//  Copyright © 2018 Kenneth A Esdaile. All rights reserved.
//

#include "../../graphics/scene/Camera.hpp"
namespace kege {namespace gfx{
    
    void gfx::Camera::SetViewMatrix(const cg::point3& p, const cg::vec3& r, const cg::vec3& u, const cg::vec3& f)
    {
        cg::view_matrix(view, p, r,u,f);
    }
    
    void gfx::Camera::SetViewMatrix(const cg::point3& position, const cg::quat& rotation)
    {
        cg::view_matrix(view, rotation, position);
    }
    
    void gfx::Camera::LookAt(const cg::point3& eye, const cg::point3& up, const cg::point3& target)
    {
        cg::vec3 f = cg::normalize3(target - eye);
        cg::vec3 r = cg::cross3(f, up);
        cg::vec3 u = cg::cross3(r, f);
        cg::view_matrix(view, eye, r,u,f);
    }
    
    void  gfx::Camera::SetProjection(const cg::mat44 & matrix)
    {
        projection = matrix;
    }
    
    const cg::mat44 & gfx::Camera::GetProjection(void)const
    {
        return projection;
    }
    
    void gfx::Camera::SetViewMatrix(const cg::mat44& matrix)
    {
        view = matrix;
    }
    const cg::mat44 & gfx::Camera::GetViewMatrix(void)const
    {
        return view;
    }
    
    void  gfx::Camera::SetFieldOfView(float value)
    {
        fov = value;
    }
    float gfx::Camera::GetFieldOfView()const
    {
        return fov;
    }
    
    void  gfx::Camera::SetAspectRatio(float value)
    {
        aspect = value;
    }
    float gfx::Camera::GetAspectRatio()const
    {
        return aspect;
    }
    
    void  gfx::Camera::SetNearView(float value)
    {
        near = value;
    }
    float gfx::Camera::GetNearView()const
    {
        return near;
    }
    
    void  gfx::Camera::SetFarView(float value)
    {
        far = value;
    }
    float gfx::Camera::GetFarView()const
    {
        return far;
    }
    
    void Camera::Update( double delta )
    {
        Entity::Update( delta );
        SetViewMatrix( _world.translation, _world.rotation );
    }
    
    cg::vec3 Camera::MakeRay(int width, int height, double mx, double my)const
    {
        cg::vec3 ray;
        
        ray.x = (2.0f * mx) / width - 1.0f;
        ray.y = 1.0f - (2.0f * my) / height;
        
        cg::vec4 eyeray(ray.x,ray.y, -1.0, 1.0);
        
        // optimize inverse calculation for perspect projectio matrix
        cg::mat44 invproj = GetProjection();
        invproj.data[0] = 1.0 / invproj.data[0];
        invproj.data[5] = 1.0 / invproj.data[5];
        invproj.data[11] = 1.0 / invproj.data[14];
        invproj.data[14] = 1.0 / invproj.data[11];
        invproj.data[15] = -invproj.data[10] / (invproj.data[14] * invproj.data[11]);
        
        /* Eye (Camera) Coordinates: ray to eye */
        eyeray = invproj * eyeray;
        eyeray.z = -1.0;
        eyeray.w =  0.0;
        
        //cg::mat44 invview = cg::inverse(view);
        //eyeray = invview * eyeray;
        /* World Coordinates: ray to world */
        eyeray = view * eyeray;
        
        ray.x = eyeray.x;
        ray.y = eyeray.y;
        ray.z = eyeray.z;
        ray = cg::normalize3(ray);
        return ray;
    }
    
    /* constructor to create perspective camera */
    gfx::Camera::Camera(const ds::string& name, const cg::mat44& proj, const Transform& transform)
    :   gfx::Entity(Gameobject::CAMERA, name, transform)
    ,   projection( proj )
    ,   view(1.0)
    {}
    
    /* constructor to create perspective camera */
    gfx::Camera::Camera(const ds::string& name, float l, float r, float t, float b, float n, float f)
    :   gfx::Entity( Gameobject::CAMERA, "" )
    ,   view(1.0)
    {
        SetProjection( cg::orthoproj(l, r, t, b, n, f) );
        SetAspectRatio(1);
        SetFieldOfView(1);
        SetNearView(n);
        SetFarView(f);
    }
    
    /* constructor to create perspective camera */
    gfx::Camera::Camera(const ds::string& name, float aspect, float fov, float near, float far)
    :   gfx::Entity( Gameobject::CAMERA, name )
    ,   view(1.0)
    {
        SetProjection( cg::persp_proj(fov, aspect, near, far) );
        SetAspectRatio(aspect);
        SetFieldOfView(fov);
        SetNearView(near);
        SetFarView(far);
    }
    
    /* constructor to create orthographic camera */
    gfx::Camera::Camera(float l, float r, float t, float b, float n, float f)
    :   gfx::Entity( Gameobject::CAMERA, "" )
    ,   view(1.0)
    {
        SetProjection( cg::orthoproj(l, r, t, b, n, f) );
        SetAspectRatio(1);
        SetFieldOfView(1);
        SetNearView(n);
        SetFarView(f);
    }
    gfx::Camera::Camera(float aspect, float fov, float near, float far)
    :   gfx::Entity( Gameobject::CAMERA, "" )
    ,   view(1.0)
    {
        SetProjection( cg::persp_proj(fov, aspect, near, far) );
        SetAspectRatio(aspect);
        SetFieldOfView(fov);
        SetNearView(near);
        SetFarView(far);
    }
    
    gfx::Camera::Camera()
    :   gfx::Entity( Gameobject::CAMERA, "" )
    ,   projection(1.0)
    ,   view(1.0)
    {
        
    }
}}






namespace kege {namespace gfx{
    
//    void gfx::Camera::UpdateTransformation()
//    {
//        cg::vec3 forward;
//        cg::vec3 right;
//        cg::vec3 up;
//        gfx::Gameobject::UpdateTransformation();
//        cg::quat_to_basis(right, up, forward, _world.rotation);
//        _camera.SetViewMatrix(GetLocal().translation, right, up, forward);
//
//        GetFrustum()->SetFrustum
//        (   _camera.GetAspectRatio()
//         ,  _camera.GetFieldOfView()
//         ,  _camera.GetNearView()
//         ,  _camera.GetFarView()
//         ,  _world.translation
//         ,  forward
//         ,  right
//         ,  up  );
//    }
    
//    void gfx::Camera::SaveComponent(kege::XML& xml)
//    {
//        gfx::Gameobject::SaveComponent(xml);
//
//        kege::XML* cam = xml.AddChild(new kege::XML);
//        cam->SetName("camera");
//
//        kege::XML* fov = cam->AddChild(new kege::XML("fov"));
//        fov->AddAttr(new XML::attrib("value", ds::string::strprint("%f", _camera.GetFieldOfView())));
//
//        kege::XML* aspect = cam->AddChild(new kege::XML("aspect_ratio"));
//        aspect->AddAttr(new XML::attrib("value", ds::string::strprint("%f", _camera.GetAspectRatio())));
//
//        kege::XML* zfar = cam->AddChild(new kege::XML("zfar"));
//        zfar->AddAttr(new XML::attrib("value", ds::string::strprint("%f", _camera.GetFarView())));
//
//        kege::XML* znear = cam->AddChild(new kege::XML("znear"));
//        znear->AddAttr(new XML::attrib("value", ds::string::strprint("%f", _camera.GetNearView())));
//    }
}}
