//
//  Math3D.h
//  3DGameEngine
//
//  Created by Johannes Roth on 22.12.14.
//  Copyright (c) 2014 Johannes Roth. All rights reserved.
//

#ifndef __3DGameEngine__Math3D__
#define __3DGameEngine__Math3D__

#include <math.h>
#include <chrono>
#include <iostream>

typedef float f32;
typedef double f64;

#define DEG2RAD(deg) ((deg)*3.14159/180.0)
#define RAD2DEG(rad) ((rad)*180.0/3.14159)

inline uint32_t RAND_NextUInt32()
{
    static uint32_t x = (uint32_t)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return x;
}

inline float RAND_NextFloat()
{
    return (RAND_NextUInt32() / (float)UINT32_MAX);
}

template <typename T> struct SVector2_tpl;
template <typename T> struct SVector3_tpl;
template <typename T> struct SColor_tpl;
template <typename T> struct SMatrix4_tpl;
template <typename T> struct SQuaternion_tpl;

typedef SVector2_tpl<f32> SVector2;
typedef SVector2_tpl<f64> SVector2_f64;
typedef SVector2_tpl<int> SVector2_i32;

template <typename T> struct SVector2_tpl
{
    union
    {
        struct { T x, y; }; T xy[2];
        struct { T u, v; }; T uv[2];
        struct { T s, t; }; T st[2];
    };
};

template <typename T> inline SVector2_tpl<T> operator - (const SVector2_tpl<T> &a, const SVector2_tpl<T> &b)
{
    return { a.x - b.x, a.y - b.y };
}

typedef SVector3_tpl<f32> SVector3;
typedef SVector3_tpl<f64> SVector3_f64;

template <typename T>
struct SVector3_tpl
{
    union
    {
        struct { T x, y, z; };
        T xyz[3];
    };

    inline T GetSquaredLength() const { return (x*x)+(y*y)+(z*z); }
    inline T GetLength() const { return (T)sqrt(GetSquaredLength()); }

    inline void Normalize() { T ilen=(T)(1.0/GetLength()); x*=ilen; y*=ilen; z*=ilen; }
};

template <typename T> inline SVector3_tpl<T> operator * (const SVector3_tpl<T> a, T b)
{
    return { a.x * b, a.y * b, a.z * b };
}

template <typename T> inline SVector3_tpl<T> operator - (const SVector3_tpl<T> a)
{
    return { -a.x, -a.y, -a.z };
}

typedef SColor_tpl<f32> SColor;
typedef SColor_tpl<f64> SColor_f64;

template <typename T> struct SColor_tpl
{
    union
    {
        struct { T r, g, b, a; };
        T rgba[4];
    };
};

typedef SMatrix4_tpl<f32> SMatrix4;
typedef SMatrix4_tpl<f64> SMatrix4_f64;

template <typename T>
struct SMatrix4_tpl
{
    union
    {
        struct
        {
            T m00, m01, m02, m03;
            T m10, m11, m12, m13;
            T m20, m21, m22, m23;
            T m30, m31, m32, m33;
        };
        T m[4][4];
    };
    
    inline void SetIdentity()
    {
        m00 = 1; m01 = 0; m02 = 0; m03 = 0;
        m10 = 0; m11 = 1; m12 = 0; m13 = 0;
        m20 = 0; m21 = 0; m22 = 1; m23 = 0;
        m30 = 0; m31 = 0; m32 = 0; m33 = 1;
    }
    
    inline static SMatrix4_tpl<T> CreateIdentity() { SMatrix4_tpl<T> mat; mat.SetIdentity(); return mat; }
    
    inline void SetTranslation(T x, T y, T z)
    {
        m00 = 1; m01 = 0; m02 = 0; m03 = x;
        m10 = 0; m11 = 1; m12 = 0; m13 = y;
        m20 = 0; m21 = 0; m22 = 1; m23 = z;
        m30 = 0; m31 = 0; m32 = 0; m33 = 1;
    }
    
    inline void SetTranslation(const SVector3_tpl<T> &translation)
    {
        SetTranslation(translation.x, translation.y, translation.z);
    }
    
    inline static SMatrix4_tpl<T> CreateTranslation(T x, T y, T z) { SMatrix4_tpl<T> mat; mat.SetTranslation(x, y, z); return mat; }
    inline static SMatrix4_tpl<T> CreateTranslation(const SVector3_tpl<T> &translation) { SMatrix4_tpl<T> mat; mat.SetTranslation(translation); return mat; }
    
    inline void SetPerspective(T fov, T aspectRatio, T zNear, T zFar)
    {
        T tanHalfFov = (T)(tan(fov * 0.5));
        
        m00 = (T)(1.0 / (aspectRatio * tanHalfFov)); m01 = 0; m02 = 0; m03 = 0;
        m10 = 0; m11 = (T)(1.0 / tanHalfFov); m12 = 0; m13 = 0;
        m20 = 0; m21 = 0; m22 = (T)((-zNear - zFar) / (zNear - zFar)); m23 = (T)((2 * zFar * zNear) / (zNear - zFar));
        m30 = 0; m31 = 0; m32 = 1; m33 = 0;
    }
    
    inline static SMatrix4_tpl<T> CreatePerspective(T fov, T aspectRatio, T zNear, T zFar) { SMatrix4_tpl<T> mat; mat.SetPerspective(fov, aspectRatio, zNear, zFar); return mat; }
    
    inline void SetRotationY(T angle)
    {
        T s = (T)sin(angle);
        T c = (T)cos(angle);
        
        m00 = c; m01 = 0; m02 = s; m03 = 0;
        m10 = 0; m11 = 1; m12 = 0; m13 = 0;
        m20 = -s; m21 = 0; m22 = c; m23 = 0;
        m30 = 0; m31 = 0; m32 = 0; m33 = 1;
    }
    
    inline static SMatrix4_tpl<T> CreateRotationY(T angle) { SMatrix4_tpl<T> mat; mat.SetRotationY(angle); return mat; }

    inline void SetScale(T x, T y, T z)
    {
        m00 = x; m01 = 0; m02 = 0; m03 = 0;
        m10 = 0; m11 = y; m12 = 0; m13 = 0;
        m20 = 0; m21 = 0; m22 = z; m23 = 0;
        m30 = 0; m31 = 0; m32 = 0; m33 = 1;
    }
    
    inline void SetScale(const SVector3_tpl<T> &scale)
    {
        SetScale(scale.x, scale.y, scale.z);
    }
    
    inline static SMatrix4_tpl<T> CreateScale(T x, T y, T z) { SMatrix4_tpl<T> mat; mat.SetScale(x, y, z); return mat; }
    inline static SMatrix4_tpl<T> CreateScale(const SVector3_tpl<T> &scale) { SMatrix4_tpl<T> mat; mat.SetScale(scale); return mat; }
};

template <typename T>
inline SMatrix4_tpl<T> operator * (const SMatrix4_tpl<T> &b, const SMatrix4_tpl<T> &a)
{
    SMatrix4_tpl<T> c;
    
    c.m00 = (a.m00 * b.m00) + (a.m10 * b.m01) + (a.m20 * b.m02) + (a.m30 * b.m03);
    c.m01 = (a.m01 * b.m00) + (a.m11 * b.m01) + (a.m21 * b.m02) + (a.m31 * b.m03);
    c.m02 = (a.m02 * b.m00) + (a.m12 * b.m01) + (a.m22 * b.m02) + (a.m32 * b.m03);
    c.m03 = (a.m03 * b.m00) + (a.m13 * b.m01) + (a.m23 * b.m02) + (a.m33 * b.m03);
    
    c.m10 = (a.m00 * b.m10) + (a.m10 * b.m11) + (a.m20 * b.m12) + (a.m30 * b.m13);
    c.m11 = (a.m01 * b.m10) + (a.m11 * b.m11) + (a.m21 * b.m12) + (a.m31 * b.m13);
    c.m12 = (a.m02 * b.m10) + (a.m12 * b.m11) + (a.m22 * b.m12) + (a.m32 * b.m13);
    c.m13 = (a.m03 * b.m10) + (a.m13 * b.m11) + (a.m23 * b.m12) + (a.m33 * b.m13);
    
    c.m20 = (a.m00 * b.m20) + (a.m10 * b.m21) + (a.m20 * b.m22) + (a.m30 * b.m23);
    c.m21 = (a.m01 * b.m20) + (a.m11 * b.m21) + (a.m21 * b.m22) + (a.m31 * b.m23);
    c.m22 = (a.m02 * b.m20) + (a.m12 * b.m21) + (a.m22 * b.m22) + (a.m32 * b.m23);
    c.m23 = (a.m03 * b.m20) + (a.m13 * b.m21) + (a.m23 * b.m22) + (a.m33 * b.m23);
    
    c.m30 = (a.m00 * b.m30) + (a.m10 * b.m31) + (a.m20 * b.m32) + (a.m30 * b.m33);
    c.m31 = (a.m01 * b.m30) + (a.m11 * b.m31) + (a.m21 * b.m32) + (a.m31 * b.m33);
    c.m32 = (a.m02 * b.m30) + (a.m12 * b.m31) + (a.m22 * b.m32) + (a.m32 * b.m33);
    c.m33 = (a.m03 * b.m30) + (a.m13 * b.m31) + (a.m23 * b.m32) + (a.m33 * b.m33);
    
    return c;
}

typedef SQuaternion_tpl<f32> SQuaternion;
typedef SQuaternion_tpl<f64> SQuaternion_f64;

template <typename T> struct SQuaternion_tpl
{
    union
    {
        struct
        {
            struct { T x, y, z, s; };
            //SVector3 xyz;
        };
        T xyzs[4];
    };

    inline void SetEuler(T theta_x, T theta_y, T theta_z)
    {
        T cos_z_2 = (T)cosf(0.5*theta_z);
        T cos_y_2 = (T)cosf(0.5*theta_y);
        T cos_x_2 = (T)cosf(0.5*theta_x);

        T sin_z_2 = (T)sinf(0.5*theta_z);
        T sin_y_2 = (T)sinf(0.5*theta_y);
        T sin_x_2 = (T)sinf(0.5*theta_x);

        s = cos_z_2*cos_y_2*cos_x_2 + sin_z_2*sin_y_2*sin_x_2;
        x = cos_z_2*cos_y_2*sin_x_2 - sin_z_2*sin_y_2*cos_x_2;
        y = cos_z_2*sin_y_2*cos_x_2 + sin_z_2*cos_y_2*sin_x_2;
        z = sin_z_2*cos_y_2*cos_x_2 - cos_z_2*sin_y_2*sin_x_2;
    }

    inline static SQuaternion_tpl<T> CreateEuler(T theta_x, T theta_y, T theta_z) { SQuaternion_tpl<T> q; q.SetEuler(theta_x, theta_y, theta_z); return q; }
    
    inline void SetAxisRotation(const SVector3 &axis, T angle)
    {
        x = axis.x * (T)sin(angle * 0.5);
        y = axis.y * (T)sin(angle * 0.5);
        z = axis.z * (T)sin(angle * 0.5);
        s = (T)cos(angle * 0.5);
    }
    
    inline static SQuaternion_tpl<T> CreateAxisRotation(const SVector3 &axis, T angle) { SQuaternion_tpl<T> q; q.SetAxisRotation(axis, angle); return q; }

    inline SMatrix4_tpl<T> GetMatrix4() const
    {
        SMatrix4_tpl<T> m;
        m.m00 = 1-2*(y*y+z*z); m.m01 = 2*(x*y-s*z);   m.m02 = 2*(x*z+s*y);   m.m03 = 0;
        m.m10 = 2*(x*y+s*z);   m.m11 = 1-2*(x*x+z*z); m.m12 = 2*(y*z-s*x);   m.m13 = 0;
        m.m20 = 2*(x*z-s*y);   m.m21 = 2*(y*z+s*x);   m.m22 = 1-2*(x*x+y*y); m.m23 = 0;
        m.m30 = 0;             m.m31 = 0;             m.m32 = 0;             m.m33 = 1;
        return m;
    }

    inline operator SMatrix4_tpl<T> () const
    {
        return GetMatrix4();
    }
    
    inline SQuaternion_tpl<T> Conjugate() const
    {
        return { -x, -y, -z, s };
    }
    
    inline T GetLength() const
    {
        return (T)sqrt(x * x + y * y + z * z + s * s);
    }
    
    inline void Normalize()
    {
        T ilen = (T)(1.0 / GetLength());
        x *= ilen;
        y *= ilen;
        z *= ilen;
        s *= ilen;
    }
    
    inline SQuaternion_tpl<T> GetNormalized() const
    {
        SQuaternion_tpl<T> cpy = { x, y, z, s };
        cpy.Normalize();
        return cpy;
    }
    
    inline SVector3_tpl<T> GetRight() const
    {
        return (*this) * SVector3_tpl<T>({ 1, 0, 0 });
    }
    
    inline SVector3_tpl<T> GetUp() const
    {
        return (*this) * SVector3_tpl<T>({ 0, 1, 0 });
    }
    
    inline SVector3_tpl<T> GetForward() const
    {
        return (*this) * SVector3_tpl<T>({ 0, 0, 1 });
    }
    
    inline SQuaternion_tpl<T> mul(const SVector3_tpl<T> r) const
    {
        float w_ = -x * r.x - y * r.y - z * r.z;
        float x_ =  s * r.x + y * r.z - z * r.y;
        float y_ =  s * r.y + z * r.x - x * r.z;
        float z_ =  s * r.z + x * r.y - y * r.x;
        return { x_, y_, z_, w_ };
    }
    
    inline SQuaternion_tpl<T> mul(const SQuaternion_tpl<T> r) const
    {
        T w_ = s * r.s - x * r.x - y * r.y - z * r.z;
        T x_ = x * r.s + s * r.x + y * r.z - z * r.y;
        T y_ = y * r.s + s * r.y + z * r.x - x * r.z;
        T z_ = z * r.s + s * r.z + x * r.y - y * r.x;
        return { x_, y_, z_, w_ };
    }
};

template <typename T> inline SVector3_tpl<T> operator * (const SQuaternion_tpl<T> a, const SVector3_tpl<T> b)
{
    SQuaternion_tpl<T> c = a.Conjugate();
    SQuaternion_tpl<T> w = a.mul(b).mul(c);
    return { w.x, w.y, w.z };
}

template <typename T> inline SVector3_tpl<T> operator * (const SVector3_tpl<T> b, const SQuaternion_tpl<T> a)
{
    SQuaternion_tpl<T> c = a.Conjugate();
    SQuaternion_tpl<T> w = a.mul(b).mul(c);
    return { w.x, w.y, w.z };
}

template <typename T> inline SQuaternion_tpl<T> operator * (const SQuaternion_tpl<T> a, const SQuaternion_tpl<T> b)
{
    return a.mul(b);
}

#endif
