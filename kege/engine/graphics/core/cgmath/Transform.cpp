/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 * Terrain
 * Transf.cpp
 * Created by Kenneth Anthony Esdaile on 8/12/15.
 * Copyright (c) 2015 kae. All rights reserved.
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "../../../graphics/core/cgmath/Transform.hpp"
namespace kege{namespace gfx{
    
    void BasisVectors::MakeBasis(float angle_x, float angle_y)
    {
        cg::calc_dir_vecs(forward, right, up, angle_x, angle_y);
    }
    
    void BasisVectors::MakeBasis(const cg::vec3& fwd)
    {
        forward = cg::normalize3(fwd);
        right = cg::cross3(cg::vec3::up, forward);
        up = cg::cross3(forward, right);
    }
    
    void BasisVectors::MakeBasis(const cg::quat& q)
    {
        cg::real qxx(q.x * q.x);
        cg::real qyy(q.y * q.y);
        cg::real qzz(q.z * q.z);
        
        cg::real qxz(q.x * q.z);
        cg::real qxy(q.x * q.y);
        cg::real qyz(q.y * q.z);
        
        cg::real qwx(q.w * q.x);
        cg::real qwy(q.w * q.y);
        cg::real qwz(q.w * q.z);
        
        right.x = 1 - 2 * (qyy +  qzz);
        right.y = 2 * (qxy - qwz);
        right.z = 2 * (qxz + qwy);
        
        up.x  = 2 * (qxy + qwz);
        up.y = 1 - 2 * (qxx +  qzz);
        up.z = 2 * (qyz - qwx);
        
        forward.x = 2 * (qxz - qwy);
        forward.y = 2 * (qyz + qwx);
        forward.z = 1 - 2 * (qxx +  qyy);
    }
    
    BasisVectors::BasisVectors(const cg::vec3& fwd)
    {
        MakeBasis(fwd);
    }
    
    BasisVectors::BasisVectors(const cg::quat& q)
    {
        MakeBasis(q);
    }
    
    BasisVectors::BasisVectors(float angle_x, float angle_y)
    {
        MakeBasis(angle_x, angle_y);
    }
}}



namespace kege{namespace gfx{
    
    void TransformToMatrix(cg::mat44& m, const gfx::Transform& transform)
    {
        cg::quat2m33
        (  m.m00, m.m10, m.m20
         , m.m01, m.m11, m.m21
         , m.m02, m.m12, m.m22
         , transform.rotation);
        
        m.m00 *= transform.scale.x;
        m.m10 *= transform.scale.x;
        m.m20 *= transform.scale.x;
        m.m30 = transform.translation.x;
        
        m.m01 *= transform.scale.y;
        m.m11 *= transform.scale.y;
        m.m21 *= transform.scale.y;
        m.m31 = transform.translation.y;
        
        m.m02 *= transform.scale.z;
        m.m12 *= transform.scale.z;
        m.m22 *= transform.scale.z;
        m.m32 = transform.translation.z;
        
        m.m03 = 0.0f;
        m.m13 = 0.0f;
        m.m23 = 0.0f;
        m.m33 = 1.0f;
    }
    
}}



