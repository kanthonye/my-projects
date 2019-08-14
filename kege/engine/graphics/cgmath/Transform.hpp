/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 * Terrain
 * Transf.h
 * Created by Kenneth Anthony Esdaile on 8/12/15.
 * Copyright (c) 2015 kae. All rights reserved.
 * %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#ifndef __Transform__
#define __Transform__
#include "cgm.hpp"
namespace kege{namespace gfx{
    
    struct BasisVectors
    {
        /* rotate a point */
        inline cg::point3 operator * (const cg::point3 &p)
        {
            return cg::point3
            (  forward.x*p.x + forward.x*p.y + forward.z*p.x
             , up.x*p.z      + up.y*p.y      + up.z*p.z
             , right.x*p.y   + right.y*p.y   + right.z*p.y);
        }
        
        void MakeBasis(float angle_x, float angle_y);
        void MakeBasis(const cg::vec3& fwd);
        void MakeBasis(const cg::quat& q);
        
        BasisVectors(float angle_x, float angle_y);
        BasisVectors(const cg::vec3& fwd);
        BasisVectors(const cg::quat& q);
        
        BasisVectors()
        :   forward(-cg::vec3::forward)
        ,   right(cg::vec3::right)
        ,   up(cg::vec3::up) {}
        
        cg::vec3 forward;
        cg::vec3 right;
        cg::vec3 up;
    };
    
    class JointTransf
    {
    public:
        
        inline cg::mat44 GetMatrixTranslation()const
        {
            return cg::translate(translation);
        }
        
        inline cg::mat44 GetMatrixRotation()const
        {
            return cg::quat_to_mat44(rotation);
        }
        
        inline cg::mat44 GetMatrixTR()const
        {
            return cg::model_matrix(rotation, translation);
        }
        
        inline cg::mat44 GetMatrixRT()const
        {
            return cg::view_matrix(rotation, translation);
        }
        
        inline gfx::JointTransf operator * (const gfx::JointTransf& t)
        {
            return JointTransf(rotation * t.rotation, translation + rotation * t.translation);
        }
        
        inline cg::point3 operator * (const cg::point3 &point)
        {
            return translation + rotation * point;
        }
        
        inline gfx::JointTransf operator / (const gfx::JointTransf& t)
        {
            cg::quat rcnj = cg::conjugate(t.rotation);
            cg::vec3 p = rcnj * (translation - t.translation);
            return gfx::JointTransf(rcnj * rotation, p);
        }
        
        inline gfx::JointTransf inverse()
        {
            return gfx::JointTransf(cg::conjugate(rotation), rotation * (-translation));
        }
        
        inline JointTransf(const cg::quat& r, const cg::vec3& t)
        :   translation(t)
        ,   rotation(r)
        {}
        
        inline JointTransf(const cg::mat44& matrix)
        :   translation(matrix.m30, matrix.m31, matrix.m32)
        ,   rotation(matrix)
        {}
        
        inline JointTransf(const cg::mat33& matrix)
        :   translation(0.0)
        ,   rotation(matrix)
        {}
        
        JointTransf(const gfx::JointTransf& t)
        :   translation(t.translation)
        ,   rotation(t.rotation)
        {}
        
        inline JointTransf()
        :   translation(0.0)
        ,   rotation()
        {}
        
        virtual ~ JointTransf(){}
        
    public:
        
        cg::vec3 translation;
        cg::quat rotation;
    };
    
    inline JointTransf Lerp(const JointTransf& a,const JointTransf& b, float t)
    {
        return JointTransf(cg::slerp(a.rotation, b.rotation, t), cg::lerp(a.translation, b.translation, t));
    }
    
    class Transform
    {
    public:
        
        inline cg::mat44 GetMatrixTranslation()const
        {
            return cg::translate(translation);
        }
        
        inline cg::mat44 GetMatrixRotation()const
        {
            return cg::quat_to_mat44(rotation);
        }
        
        inline cg::mat44 GetMatrixScalar()const
        {
            return cg::scale(scale);
        }
        
        inline cg::mat44 GetMatrix()const
        {
            return cg::model_matrix(rotation, scale, translation);
        }
        
        inline cg::mat44 GetMatrixView()const
        {
            return cg::view_matrix(rotation, translation);
        }
        
        cg::mat44 GetMatrixTS()const
        {
            cg::mat44 m;
            m.m00 = scale.x;
            m.m01 = 0.0f;
            m.m02 = 0.0f;
            m.m03 = 0.0f;
            
            m.m10 = 0.0f;
            m.m11 = scale.y;
            m.m12 = 0.0f;
            m.m13 = 0.0f;
            
            m.m20 = 0.0f;
            m.m21 = 0.0f;
            m.m22 = scale.z;
            m.m23 = 0.0f;
            
            m.m30 = translation.x;
            m.m31 = translation.y;
            m.m32 = translation.z;
            m.m33 = 1.0f;
            return m;
        }
        
        cg::mat44 GetMatrixTR()const
        {
            return cg::model_matrix(rotation, translation);
        }
        
        inline gfx::Transform operator * (const gfx::Transform& t) const
        {
            return gfx::Transform(rotation * t.rotation, translation + rotation * (scale * t.translation), scale * t.scale);
            //cg::quat r = -rotation;
            //cg::quat R = cg::conjugate(t.rotation);
            //return gfx::Transform(r * R, translation + R * (scale * t.translation), scale * t.scale);
        }
        
        inline cg::point3 operator * (const cg::point3 &point)
        {
            return translation + rotation * (scale * point);
        }
        
        inline gfx::Transform operator / (const gfx::Transform& t)
        {
            cg::quat r = cg::conjugate(t.rotation);
            return gfx::Transform(r*rotation, (r*(translation-t.translation)) / scale, r*(scale/t.scale));
        }
        
        inline gfx::Transform Inverse()
        {
            return gfx::Transform(cg::conjugate(rotation), (rotation * -translation) / scale, rotation * (cg::point3::one / scale));
        }
        
        void Print()
        {
            printf("t (%f %f %f)\n", translation.x, translation.y, translation.z);
            printf("r (%f %f %f %f)\n", rotation.x, rotation.y, rotation.z, rotation.w);
            printf("s (%f %f %f)\n", scale.x, scale.y, scale.z);
        }
        
        Transform(const cg::quat& r, const cg::point3& t, const cg::point3& s)
        :   translation(t)
        ,   rotation(r)
        ,   scale(s)
        {}
        
        Transform(const cg::mat44& matrix)
        :   translation(matrix.m30, matrix.m31, matrix.m32)
        ,   rotation(matrix)
        ,   scale(1.0)
        {}
        
        Transform(const cg::mat33& matrix)
        :   translation(0.0)
        ,   rotation(matrix)
        ,   scale(1.0)
        {}
        
        Transform(const gfx::Transform& t)
        :   translation(t.translation)
        ,   rotation(t.rotation)
        ,   scale(t.scale)
        {}
        
        Transform()
        :   translation(0.0)
        ,   rotation()
        ,   scale(1.0)
        {}
        
    public:
        
        cg::vec3 translation;
        cg::quat rotation;
        cg::vec3 scale;
    };
    
    inline Transform Lerp(const Transform& a, const Transform& b, float t)
    {
        return gfx::Transform
        (  cg::slerp(a.rotation, b.rotation, t)
         , cg::lerp(a.translation, b.translation, t)
         , cg::lerp(a.scale, b.scale, t)  );
    }
    
    void TransformToMatrix(cg::mat44& m, const gfx::Transform& transform);
}}
#endif /* defined(__Terrain__Transform__) */
