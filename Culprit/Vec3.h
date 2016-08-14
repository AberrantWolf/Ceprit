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

class Vec3 {
public:
    Vec3() {}
    Vec3(double e0, double e1, double e2) {
        e[0] = e0;
        e[1] = e1;
        e[2] = e2;
    }
    
    //
    // Accessors
    //
    inline double x() const { return e[0]; }
    inline double y() const { return e[1]; }
    inline double z() const { return e[2]; }
    inline double r() const { return e[0]; }
    inline double g() const { return e[0]; }
    inline double b() const { return e[0]; }
    
    //
    // Operators
    //
    inline const Vec3& operator+() const { return *this; }
    inline Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
    
    inline double operator[](int i) const { return e[i]; }
    inline double& operator[](int i) { return e[i]; }
    
    inline double length() const {
        return sqrt(squared_length());
    }
    inline double squared_length() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }
    inline void make_unit_vector();
    
    inline Vec3& operator+=(const Vec3 &v2);
    inline Vec3& operator-=(const Vec3 &v2);
    inline Vec3& operator*=(const Vec3 &v2);
    inline Vec3& operator/=(const Vec3 &v2);
    inline Vec3& operator*=(const double t);
    inline Vec3& operator/=(const double t);
    
    double e[3];
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

inline Vec3 operator*(const double t, const Vec3& v) {
    return Vec3(t*v[0], t*v[1], t*v[2]);
}

inline Vec3 operator*(const Vec3& v, const double t) {
    return Vec3(v[0]*t, v[1]*t, v[2]*t);
}

inline Vec3 operator/(const Vec3& v, const double t) {
    return Vec3(v[0]/t, v[1]/t, v[2]/t);
}

inline double dot(const Vec3& v1, const Vec3& v2) {
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

inline Vec3 cross(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1[1]*v2[2] - v1[2]*v2[1],
                -v1[0]*v2[2] - v1[2]*v2[0],
                v1[0]*v2[1] - v1[1]*v2[0]);
}

inline Vec3 unit_vector(const Vec3& v) {
    return v / v.length();
}


Vec3 random_point_in_unit_sphere() {
    Vec3 p;
    
    do {
        p = 2.0 * Vec3(drand48(), drand48(), drand48()) - Vec3(1, 1, 1);
    } while (p.squared_length() >= 1.0);
    
    return p;
}

inline Vec3 reflect(const Vec3& v, const Vec3& n) {
    return v - 2*dot(v, n) * n;
}

bool refract(const Vec3& v, const Vec3& n, double ni_over_nt, Vec3& refracted) {
    Vec3 uv = unit_vector(v);
    double dt = dot(uv, n);
    double discriminant = 1.0 - ni_over_nt * ni_over_nt * (1.0 - dt * dt);
    
    if (discriminant > 0) {
        refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
        return true;
    }
    
    return false;
}

//
// Implementing inner functionality
//
inline void Vec3::make_unit_vector() {
    double k = 1.0 / sqrt(squared_length());
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

inline Vec3& Vec3::operator*=(const double v) {
    e[0] *= v;
    e[1] *= v;
    e[2] *= v;
    return *this;
}

inline Vec3& Vec3::operator/=(const double v) {
    e[0] /= v;
    e[1] /= v;
    e[2] /= v;
    return *this;
}

#endif /* Vec3_hpp */
