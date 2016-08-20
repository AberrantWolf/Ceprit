//
//  Vec3.hpp
//  Culprit
//
//  Created by B. Scott Harper on 8/14/16.
//  Copyright © 2016 Harpers. All rights reserved.
//

#ifndef Vec3_hpp
#define Vec3_hpp

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include "Defines.h"

class Vec3 {
public:
    Vec3() {}
    Vec3(real e0, real e1, real e2) {
        e[0] = e0;
        e[1] = e1;
        e[2] = e2;
    }
    
    //
    // Accessors
    //
    inline real x() const { return e[0]; }
    inline real y() const { return e[1]; }
    inline real z() const { return e[2]; }
    inline real r() const { return e[0]; }
    inline real g() const { return e[0]; }
    inline real b() const { return e[0]; }
    
    //
    // Operators
    //
    inline const Vec3& operator+() const { return *this; }
    inline Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
    
    inline real operator[](int i) const { return e[i]; }
    inline real& operator[](int i) { return e[i]; }
    
    inline real length() const {
        return sqrt(squared_length());
    }
    inline real squared_length() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }
    inline void make_unit_vector();
    
    inline Vec3& operator+=(const Vec3 &v2);
    inline Vec3& operator-=(const Vec3 &v2);
    inline Vec3& operator*=(const Vec3 &v2);
    inline Vec3& operator/=(const Vec3 &v2);
    inline Vec3& operator*=(const real t);
    inline Vec3& operator/=(const real t);
    
    real e[3];
};

//
// I/O Stream support
//
inline std::istream& operator>>(std::istream& is, Vec3& v) {
    is >> v[0] >> v[1] >> v[2];
    return is;
}

inline std::ostream& operator<<(std::ostream& os, const Vec3& t) {
    os << t[0] << " " << t[1] << " " << t[2];
    return os;
}

//
// Creation functions
//
inline Vec3 operator+(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1[0]+v2[0], v1[1]+v2[1], v1[2]+v2[2]);
}

inline Vec3 operator-(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1[0]-v2[0], v1[1]-v2[1], v1[2]-v2[2]);
}

inline Vec3 operator*(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1[0]*v2[0], v1[1]*v2[1], v1[2]*v2[2]);
}

inline Vec3 operator/(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1[0]/v2[0], v1[1]/v2[1], v1[2]/v2[2]);
}

inline Vec3 operator*(const real t, const Vec3& v) {
    return Vec3(t*v[0], t*v[1], t*v[2]);
}

inline Vec3 operator*(const Vec3& v, const real t) {
    return Vec3(v[0]*t, v[1]*t, v[2]*t);
}

inline Vec3 operator/(const Vec3& v, const real t) {
    return Vec3(v[0]/t, v[1]/t, v[2]/t);
}

inline real dot(const Vec3& v1, const Vec3& v2) {
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

inline Vec3 cross(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1[1]*v2[2] - v1[2]*v2[1],
                -(v1[0]*v2[2] - v1[2]*v2[0]),
                v1[0]*v2[1] - v1[1]*v2[0]);
}

inline Vec3 unit_vector(const Vec3& v) {
    return v / v.length();
}

inline Vec3 reflect(const Vec3& v, const Vec3& n) {
    return v - 2*dot(v, n) * n;
}

bool refract(const Vec3& v, const Vec3& n, real ni_over_nt, Vec3& refracted);

//
// Implementing inner functionality
//
inline void Vec3::make_unit_vector() {
    real k = 1.0 / sqrt(squared_length());
    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
}

inline Vec3& Vec3::operator+=(const Vec3& v) {
    e[0] += v[0];
    e[1] += v[1];
    e[2] += v[2];
    return *this;
}

inline Vec3& Vec3::operator-=(const Vec3& v) {
    e[0] -= v[0];
    e[1] -= v[1];
    e[2] -= v[2];
    return *this;
}

inline Vec3& Vec3::operator*=(const Vec3& v) {
    e[0] *= v[0];
    e[1] *= v[1];
    e[2] *= v[2];
    return *this;
}

inline Vec3& Vec3::operator/=(const Vec3& v) {
    e[0] /= v[0];
    e[1] /= v[1];
    e[2] /= v[2];
    return *this;
}

inline Vec3& Vec3::operator*=(const real v) {
    e[0] *= v;
    e[1] *= v;
    e[2] *= v;
    return *this;
}

inline Vec3& Vec3::operator/=(const real v) {
    e[0] /= v;
    e[1] /= v;
    e[2] /= v;
    return *this;
}

#endif /* Vec3_hpp */
